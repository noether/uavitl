#include <iostream>

#include <math.h>
#include "position_formation.hh"
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/KroneckerProduct>

PositionFormation::PositionFormation(int m, Eigen::VectorXf zd,
        Eigen::MatrixXf B, float c_shape, float c_vel):
    _m(m),
    _B(B),
    _zd(zd),
    _c_shape(c_shape),
    _c_vel(c_vel)
{
    _agents = B.rows();
    _edges = B.cols();

    Eigen::MatrixXf Im(Eigen::MatrixXf::Identity(_m, _m));
    _Bb = Eigen::kroneckerProduct(_B, Im);
}

PositionFormation::PositionFormation()
{
}

PositionFormation::~PositionFormation()
{
}

Eigen::VectorXf PositionFormation::get_u_acc(Eigen::VectorXf X,
        Eigen::VectorXf V)
{
    Eigen::VectorXf U(Eigen::VectorXf::Zero(X.rows()));
    Eigen::MatrixXf Z = _Bb.transpose()*X;
    
    Eigen::MatrixXf E = Z - _zd;
    U = -_c_shape*_Bb*E -_c_vel*V;

    std::cout << "Error position: " << E.transpose() << std::endl;

    return U;
}

Eigen::VectorXf PositionFormation::get_u_vel(Eigen::VectorXf X)
{
    Eigen::VectorXf U(Eigen::VectorXf::Zero(X.rows()));
    Eigen::MatrixXf Z = _Bb.transpose()*X;
    
    Eigen::MatrixXf E = Z - _zd;
    U = -_c_shape*_Bb*E;

    return U;
}

