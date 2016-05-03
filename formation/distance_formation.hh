#ifndef DISTANCE_FORMATION_HH
#define DISTANCE_FORMATION_HH 1

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>
#include <fstream>

class DistanceFormation
{
    private:
        // Rigid formation
        int _m;
        float _l;

        Eigen::MatrixXf _B;
        Eigen::MatrixXf _Bd;
        Eigen::MatrixXf _S1;
        Eigen::MatrixXf _S2;
        Eigen::MatrixXf _Av;
        Eigen::MatrixXf _Aa;
        Eigen::MatrixXf _Bb;
        Eigen::MatrixXf _Bdb;
        Eigen::MatrixXf _S1b;
        Eigen::MatrixXf _S2b;
        Eigen::MatrixXf _Avb;
        Eigen::MatrixXf _Aab;

        Eigen::VectorXf _d;
        int _agents, _edges;
        Eigen::VectorXf _mu;
        Eigen::VectorXf _tilde_mu;

        Eigen::VectorXf _X, _Z, _E, _V, _U, _v_hat, _mu_hat;

        float _c_shape, _c_vel, _k_v_hat, _k_mu_hat;

        void _make_S1_S2();
        void _make_Av_Aa();
        Eigen::MatrixXf _make_Dz(Eigen::VectorXf);
        Eigen::MatrixXf _make_Dzt(Eigen::VectorXf);
        Eigen::MatrixXf _make_Dzh(Eigen::VectorXf);
        Eigen::VectorXf _make_Zh(Eigen::VectorXf);
        Eigen::VectorXf _make_E(Eigen::VectorXf);

        std::ofstream _log;

    public:
        DistanceFormation(int, int, Eigen::VectorXf, Eigen::VectorXf,
                Eigen::VectorXf, Eigen::MatrixXf, float, float, float, float);
        DistanceFormation();
        ~DistanceFormation();

        void set_mus(Eigen::VectorXf, Eigen::VectorXf);
        void set_c_shape(float);
        void set_c_vel(float);
        void set_k_v_hat(float);
        Eigen::VectorXf get_u_acc(Eigen::VectorXf, Eigen::VectorXf);
        Eigen::VectorXf get_u_vel(Eigen::VectorXf);
        void update_v_hat(Eigen::VectorXf, float);
        void update_mu_hat(Eigen::VectorXf, float);

        Eigen::VectorXf get_v_hat();
        Eigen::VectorXf get_mu_hat();
        Eigen::VectorXf get_X();
        Eigen::VectorXf get_Z();
        Eigen::VectorXf get_E();
        Eigen::VectorXf get_V();
        Eigen::VectorXf get_U();

        void log(float);
};

#endif // DISTANCE_FORMATION_HH

