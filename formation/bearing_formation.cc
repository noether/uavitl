#include <iostream>

#include <math.h>
#include "bearing_formation.hh"
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/KroneckerProduct>

BearingFormation::BearingFormation(int m, Eigen::VectorXf zhd,
        Eigen::MatrixXf B, float c_shape, float c_vel):
    _m(m),
    _B(B),
    _zhd(zhd),
    _c_shape(c_shape),
    _c_vel(c_vel)
{
    _agents = B.rows();
    _edges = B.cols();

    Eigen::MatrixXf Im(Eigen::MatrixXf::Identity(_m, _m));
    _Bb = Eigen::kroneckerProduct(_B, Im);
}

BearingFormation::BearingFormation()
{
}

BearingFormation::~BearingFormation()
{
}

Eigen::VectorXf BearingFormation::get_u_acc(Eigen::VectorXf X,
        Eigen::VectorXf V)
{
    Eigen::VectorXf U(X.rows());
    U.setZero();

    Eigen::VectorXf Z = _Bb.transpose() * X;
    Eigen::MatrixXf DPzh = _compute_DPzh(Z);
    Eigen::MatrixXf Dzt = _compute_Dzt(Z);
    Eigen::MatrixXf Im(Eigen::MatrixXf::Identity(_m, _m));
    Eigen::MatrixXf Dztbar = Eigen::kroneckerProduct(Dzt, Im);

    U = _c_shape * _Bb*DPzh*Dztbar*_zhd - _c_vel*V;

    std::cout << "E bearing: " << (Dztbar*Z - _zhd).transpose() << std::endl;

    return U;
}

Eigen::VectorXf BearingFormation::get_u_vel(Eigen::VectorXf X)
{
    Eigen::VectorXf U(X.rows());
    U.setZero();

    Eigen::VectorXf Z = _Bb.transpose() * X;
    Eigen::MatrixXf DPzh = _compute_DPzh(Z);
    Eigen::MatrixXf Dzt = _compute_Dzt(Z);
    Eigen::MatrixXf Im(Eigen::MatrixXf::Identity(_m, _m));
    Eigen::MatrixXf Dztbar = Eigen::kroneckerProduct(Dzt, Im);

    U = _c_shape * _Bb*DPzh*Dztbar*_zhd;

    return U;
}

Eigen::MatrixXf BearingFormation::_compute_Dzt(Eigen::VectorXf z)
{
    Eigen::MatrixXf Dzt(Eigen::MatrixXf::Zero(z.rows()/_m, z.rows()/_m));

    int i;

    for(i = 0; i < z.rows()/_m; i++){
        float normz = z.segment(_m*i, _m).norm();
        std::cout << "||Z" << i << "|| :" << normz << std::endl;
        Dzt(i, i) = 1/normz;
    }

    return Dzt;
}

Eigen::MatrixXf BearingFormation::_compute_DPzh(Eigen::VectorXf z)
{
    Eigen::MatrixXf DPzh(Eigen::MatrixXf::Zero(z.rows(), z.rows()));
    Eigen::MatrixXf Dzt = _compute_Dzt(z);
    Eigen::MatrixXf Im(Eigen::MatrixXf::Identity(_m, _m));
    Eigen::MatrixXf Dztbar = Eigen::kroneckerProduct(Dzt, Im);
    Eigen::VectorXf z_hat = Dztbar * z;
    Eigen::Vector2f z_hat_i(_m);
    int i;
    for(i = 0; i < z.rows()/_m; i++)
    {
        z_hat_i = z_hat.segment(_m*i, _m);

        Eigen::Matrix2f P = z_hat_i * z_hat_i.transpose();
        Eigen::MatrixXf DPzh_i = Im - P;
        
        DPzh.block(_m*i, _m*i, _m, _m) = DPzh_i;
    }

    return DPzh;
}
