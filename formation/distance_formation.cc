#include <iostream>
#include <boost/filesystem.hpp>
#include <fstream>

#include <math.h>
#include "distance_formation.hh"
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/Geometry>
#include <unsupported/Eigen/KroneckerProduct>

DistanceFormation::DistanceFormation(int m, int l, Eigen::VectorXf d,
        Eigen::VectorXf mu, Eigen::VectorXf tilde_mu,
        Eigen::MatrixXf B,
        float c_shape, float c_vel):
    _m(m),
    _l(l),
    _B(B),
    _d(d),
    _mu(mu),
    _tilde_mu(tilde_mu),
    _c_shape(c_shape),
    _c_vel(c_vel)
{
    _agents = B.rows();
    _edges = B.cols();
    _Bd = _B;
    _Bd.row(0).setZero();

    _v_hat = Eigen::VectorXf::Zero(_agents*_m);
    _v_hat(1) = -1;

    _S1 = Eigen::MatrixXf::Zero(_agents, _edges);
    _S2 = Eigen::MatrixXf::Zero(_agents, _edges);
    _Av = Eigen::MatrixXf::Zero(_agents, _edges);
    _Aa = Eigen::MatrixXf::Zero(_agents, _edges);
    _make_S1_S2();
    _make_Av_Aa();

    Eigen::MatrixXf Im(Eigen::MatrixXf::Identity(_m, _m));
    _Bb = Eigen::kroneckerProduct(_B, Im);
    _Bdb = Eigen::kroneckerProduct(_Bd, Im);
    _S1b = Eigen::kroneckerProduct(_S1, Im);
    _S2b = Eigen::kroneckerProduct(_S2, Im);
    _Avb = Eigen::kroneckerProduct(_Av, Im);
    _Aab = Eigen::kroneckerProduct(_Aa, Im);

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer, 80, "%F-%H%M", timeinfo);
    std::string dir_path("./log/");
    dir_path.append(buffer);

    boost::filesystem::path dir(dir_path.c_str());
    if(!boost::filesystem::is_directory(dir))
        boost::filesystem::create_directory(dir);

    dir_path.append("/log_formation.txt");

    _log.open(dir_path);
}

DistanceFormation::DistanceFormation()
{
}

DistanceFormation::~DistanceFormation()
{
}

Eigen::VectorXf DistanceFormation::get_u_vel(Eigen::VectorXf X)
{
    Eigen::VectorXf U(Eigen::VectorXf::Zero(X.rows()));
    Eigen::VectorXf Z = _Bb.transpose()*X;

    if (_l == 1){
        Eigen::MatrixXf Dzh = _make_Dzh(Z);
        Eigen::VectorXf Zh = _make_Zh(Z);
        Eigen::VectorXf E = _make_E(Z);
        U = -_c_shape*_Bb*Dzh*E + _Avb*Zh;

        std::cout << "E: " << E.transpose() << std::endl;
        if(E.norm() < 100)
            _c_shape = 8e-2;
    }
    else{
        Eigen::MatrixXf Dz = _make_Dz(Z);
        Eigen::MatrixXf Dzt = _make_Dzt(Z);
        Eigen::MatrixXf Im(Eigen::MatrixXf::Identity(_m, _m));
        Eigen::MatrixXf Dztb = Eigen::kroneckerProduct(Dzt, Im);
        Eigen::VectorXf E = _make_E(Z);
        U = -_c_shape*_Bb*Dz*Dzt*E + _Avb*Dztb*Z;
    }

    return U;
}

Eigen::VectorXf DistanceFormation::get_u_acc(Eigen::VectorXf X, 
        Eigen::VectorXf V)
{
    Eigen::VectorXf U(Eigen::VectorXf::Zero(X.rows()));
    Eigen::VectorXf Z = _Bb.transpose()*X;
    if (_l == 1){
        Eigen::MatrixXf Dzh = _make_Dzh(Z);
        Eigen::VectorXf Zh = _make_Zh(Z);
        Eigen::VectorXf E = _make_E(Z);
        U = -_c_shape*_Bb*Dzh*E + _c_vel*_Avb*Zh + _Aab*Zh - _c_vel*V;
    }
    else{
        Eigen::MatrixXf Dz = _make_Dz(Z);
        Eigen::MatrixXf Dzt = _make_Dzt(Z);
        Eigen::MatrixXf Im(Eigen::MatrixXf::Identity(_m, _m));
        Eigen::MatrixXf Dztb = Eigen::kroneckerProduct(Dzt, Im);
        Eigen::VectorXf E = _make_E(Z);
 //       U = -_c_shape*_Bb*Dz*Dzt*E + _c_vel*_Avb*Dztb*Z + _Aab*Dztb*Z - _c_vel*V;
        U = -_c_shape*_Bb*Dz*E + _c_vel*_Avb*Z + _Aab*Z - _c_vel*V;
    }

    return U;
}

void DistanceFormation::_make_S1_S2()
{
    int i, j;
    for(i = 0; i < _agents; i++)
        for(j = 0; j < _edges; j++){
            if(_B(i, j) == 1)
                _S1(i, j) =  1;
            else if(_B(i, j) == -1)
                _S2(i, j) =  1;
        }
}

void DistanceFormation::_make_Av_Aa()
{
    int i, j;
    for(i = 0; i < _agents; i++)
        for(j = 0; j < _edges; j++){
            if(_B(i, j) == 1)
                _Av(i, j) =  _mu(j);
            else if(_B(i, j) == -1)
                _Av(i, j) =  _tilde_mu(j);
        }

   _Aa = _Av*_B.transpose()*_Av;
}

Eigen::MatrixXf DistanceFormation::_make_Dz(Eigen::VectorXf Z)
{
    Eigen::MatrixXf Dz(Eigen::MatrixXf::Zero(Z.rows(), _edges));
    int i;

    for(i = 0; i < _edges; i++)
        Dz.block(i*_m, i, _m, 1) = Z.segment(i*_m, _m);

    return Dz;
}

Eigen::MatrixXf DistanceFormation::_make_Dzt(Eigen::VectorXf Z)
{
    if(_l == 2)
        return Eigen::MatrixXf::Identity(_edges, _edges);

    Eigen::VectorXf Zt = Eigen::VectorXf::Zero(_edges);
    int i;

    for(i = 0; i < _edges; i++)
        Zt(i) = pow(Z.segment(i*_m, _m).norm(), _l-2);

    return Zt.asDiagonal();
}

Eigen::MatrixXf DistanceFormation::_make_Dzh(Eigen::VectorXf Z)
{
    Eigen::MatrixXf Dzh(Eigen::MatrixXf::Zero(Z.rows(), _edges));
    int i;

    for(i = 0; i < _edges; i++){
        Eigen::VectorXf Zi = Z.segment(i*_m, _m);
        Zi.normalize();
        if(!isnan(Zi(0)))
            Dzh.block(i*_m, i, _m, 1) = Zi.segment(0, _m);
    }

    return Dzh;
}

Eigen::VectorXf DistanceFormation::_make_Zh(Eigen::VectorXf Z)
{
    Eigen::VectorXf Zh(Eigen::VectorXf::Zero(Z.rows(), Z.cols()));
    int i;

    for(i = 0; i < _edges; i++){
        Eigen::VectorXf Zi = Z.segment(i*_m, _m);
        Zi.normalize();
        if(!isnan(Zi(0)))
            Zh.segment(i*_m, _m) = Zi.segment(0, _m);
    }

    return Zh;
}

Eigen::VectorXf DistanceFormation::_make_E(Eigen::VectorXf Z)
{
    Eigen::VectorXf E(Eigen::VectorXf::Zero(_edges));
    int i;

    if( _l == 1)
        for(i = 0; i < _edges; i++)
            E(i) = Z.segment(i*_m, _m).norm() - _d(i);
    else
        for(i = 0; i < _edges; i++)
            E(i) = pow(Z.segment(i*_m, _m).norm(), _l) - pow(_d(i), _l);


    return E;
}

void DistanceFormation::set_mus(Eigen::VectorXf mu, Eigen::VectorXf tilde_mu)
{
    _mu = mu;
    _tilde_mu = tilde_mu;
}

Eigen::VectorXf DistanceFormation::get_v_hat(Eigen::VectorXf X, float dt)
{
    Eigen::VectorXf Z = _Bb.transpose()*X;
    Eigen::MatrixXf Dzh = _make_Dzh(Z);
    Eigen::VectorXf E = _make_E(Z);

    float k;
    if(E.norm() < 50)
        k = 5e-3;
    else
        k = 5e-5;

    _v_hat -= k*_Bdb*Dzh*E*dt;
    
    std::cout << "Vhat: " << _v_hat.transpose() << std::endl;

    return _v_hat;
}

void DistanceFormation::log_1st(float t, Eigen::VectorXf X)
{
    Eigen::VectorXf Z = _Bb.transpose()*X;
    Eigen::MatrixXf Dzh = _make_Dzh(Z);
    Eigen::VectorXf E = _make_E(Z);
    Eigen::VectorXf Zh = _make_Zh(Z);
    Eigen::VectorXf U = -_c_shape*_Bb*Dzh*E + _Avb*Zh + _v_hat;

    Eigen::Vector3f z1 = Eigen::Vector3f::Zero(3);
    z1.segment(0, 2) = Z.segment(0*_m, 2);
    Eigen::Vector3f u2 = Eigen::Vector3f::Zero(3);
    u2.segment(0, 2) = U.segment(1*_m, 2);
    Eigen::Vector3f w2 = z1.cross(u2);

    Eigen::Vector3f z3 = Eigen::Vector3f::Zero(3);
    z3.segment(0, 2) = Z.segment(2*_m, 2);
    Eigen::Vector3f u3 = Eigen::Vector3f::Zero(3);
    u3.segment(0, 2) = U.segment(2*_m, 2);
    Eigen::Vector3f w3 = z3.cross(u3);

    Eigen::Vector3f z4 = Eigen::Vector3f::Zero(3);
    z4.segment(0, 2) = Z.segment(3*_m, 2);
    Eigen::Vector3f u4 = Eigen::Vector3f::Zero(3);
    u4.segment(0, 2) = U.segment(3*_m, 2);
    Eigen::Vector3f w4 = z4.cross(u4);

    std::cout << "w: " << 2*w2.norm()*1e-4 << std::endl;

   _log << t << " " << X.transpose() << " " << Z.transpose() << " " << 
       E.transpose() << " " << _v_hat.transpose() << " " << 
       U.transpose() << " " << w2.norm() << " " << 2*w3.norm() << " " 
       << " " << w4.norm() << std::endl;
}

void DistanceFormation::log_2nd(float t, Eigen::VectorXf X, Eigen::VectorXf V)
{
    Eigen::VectorXf Z = _Bb.transpose()*X;
    Eigen::MatrixXf Dzh = _make_Dzh(Z);
    Eigen::VectorXf E = _make_E(Z);
    Eigen::VectorXf Zh = _make_Zh(Z);
    Eigen::VectorXf U = -_c_shape*_Bb*Dzh*E + _c_vel*_Avb*Zh + _Aab*Zh
        - _c_vel*V;

   _log << t << " " << X.transpose() << " " << Z.transpose() << " " <<
       E.transpose() << " " << _v_hat.transpose() << " " << 
       U.transpose() << " " << std::endl;
}
