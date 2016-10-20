#include <iostream>
#include <boost/filesystem.hpp>
#include <fstream>

#include <cmath>
#include "distance_formation.hh"
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/Geometry>
#include <unsupported/Eigen/KroneckerProduct>

DistanceFormation::DistanceFormation(int m, int l, Eigen::VectorXf d,
        Eigen::VectorXf mu, Eigen::VectorXf tilde_mu,
        Eigen::MatrixXf B,
        float c_shape, float c_vel, float k_v_hat, float k_mu_hat):
    _m(m),
    _l(l),
    _B(B),
    _d(d),
    _mu(mu),
    _tilde_mu(tilde_mu),
    _c_shape(c_shape),
    _c_vel(c_vel),
    _k_v_hat(k_v_hat),
    _k_mu_hat(k_mu_hat)
{
    _agents = B.rows();
    _edges = B.cols();
    _Bd = _B;
    _Bd.row(0).setZero();

    _v_hat = Eigen::VectorXf::Zero(_agents*_m);
    _mu_hat = Eigen::VectorXf::Zero(_edges);
    _X = Eigen::VectorXf::Zero(_agents*_m);
    _Z = Eigen::VectorXf::Zero(_edges*_m);
    _E = Eigen::VectorXf::Zero(_edges);
    _V = Eigen::VectorXf::Zero(_agents*_m);
    _U = Eigen::VectorXf::Zero(_agents*_m);

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

    dir_path.append("/log_dis_for.txt");

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
    _X = X;
    _Z = _Bb.transpose()*_X;

    if (_l == 1){
        Eigen::MatrixXf Dzh = _make_Dzh(_Z);
        Eigen::VectorXf Zh = _make_Zh(_Z);
        _E = _make_E(_Z);
        _U = -_c_shape*_Bb*Dzh*_E + _Avb*Zh;

    }
    else{
        Eigen::MatrixXf Dz = _make_Dz(_Z);
        Eigen::MatrixXf Dzt = _make_Dzt(_Z);
        Eigen::MatrixXf Im(Eigen::MatrixXf::Identity(_m, _m));
        Eigen::MatrixXf Dztb = Eigen::kroneckerProduct(Dzt, Im);
        Eigen::VectorXf _E = _make_E(_Z);
        _U = -_c_shape*_Bb*Dz*Dzt*_E + _Avb*Dztb*_Z;
    }

    return _U;
}

Eigen::VectorXf DistanceFormation::get_u_acc(Eigen::VectorXf X, 
        Eigen::VectorXf V)
{
    _X = X;
    _V = V;
    _Z = _Bb.transpose()*_X;

    if (_l == 1){
        Eigen::MatrixXf Dzh = _make_Dzh(_Z);
        Eigen::VectorXf Zh = _make_Zh(_Z);
        _E = _make_E(_Z);
    //    _U = -_c_shape*_Bb*Dzh*_E + _c_vel*_Avb*Zh + _Aab*Zh - _c_vel*_V;
        _U = -_c_shape*_Bb*Dzh*_E +_S1b*Dzh*(_mu-_mu_hat) - _c_vel*_V;
    }
    else{
        Eigen::MatrixXf Dz = _make_Dz(_Z);
        Eigen::MatrixXf Dzt = _make_Dzt(_Z);
        Eigen::MatrixXf Im(Eigen::MatrixXf::Identity(_m, _m));
        Eigen::MatrixXf Dztb = Eigen::kroneckerProduct(Dzt, Im);
        _E = _make_E(_Z);
 //       U = -_c_shape*_Bb*Dz*Dzt*E + _c_vel*_Avb*Dztb*Z + _Aab*Dztb*Z - _c_vel*V;
        _U = -_c_shape*_Bb*Dz*_E + _c_vel*_Avb*_Z + _Aab*_Z - _c_vel*_V;
    }

    return _U;
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
        if(!std::isnan(Zi(0)))
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
        if(!std::isnan(Zi(0)))
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

void DistanceFormation::set_c_shape(float c)
{
    _c_shape = c;
}

void DistanceFormation::set_c_vel(float c)
{
    _c_vel = c;
}

void DistanceFormation::set_k_v_hat(float k)
{
    _k_v_hat = k;
}

void DistanceFormation::update_v_hat(Eigen::VectorXf X, float dt)
{
    Eigen::VectorXf Z = _Bb.transpose()*X;
    Eigen::MatrixXf Dzh = _make_Dzh(Z);
    Eigen::VectorXf E = _make_E(Z);

    _v_hat -= _k_v_hat*_Bdb*Dzh*E*dt;
}

void DistanceFormation::update_mu_hat(Eigen::VectorXf X, float dt)
{
    Eigen::VectorXf Z = _Bb.transpose()*X;
    Eigen::VectorXf E = _make_E(Z);

    _mu_hat += _k_mu_hat*(E + _mu - _mu_hat)*dt;
}

Eigen::VectorXf DistanceFormation::get_v_hat()
{
    return _v_hat;
}

Eigen::VectorXf DistanceFormation::get_mu_hat()
{
    return _mu_hat;
}

Eigen::VectorXf DistanceFormation::get_X()
{
    return _X;
}

Eigen::VectorXf DistanceFormation::get_Z()
{
    return _Z;
}

Eigen::VectorXf DistanceFormation::get_E()
{
    return _E;
}

Eigen::VectorXf DistanceFormation::get_V()
{
    return _V;
}

Eigen::VectorXf DistanceFormation::get_U()
{
    return _U;
}

void DistanceFormation::log(float t)
{
   _log << t << " " << get_X().transpose() << " " << get_Z().transpose()
       << " " << get_E().transpose() << " " << get_v_hat().transpose()
       << " " << get_U().transpose() << " " << w2.norm()
       << " " << 2*w3.norm() << " " << w4.norm()
       << " " << get_V().transpose() << " " << get_mu_hat().transpose() 
       << std::endl;
}
