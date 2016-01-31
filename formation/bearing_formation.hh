#ifndef BEARING_FORMATION_HH
#define BEARING_FORMATION_HH 1

#include <Eigen/Dense>
#include <Eigen/Sparse>

class BearingFormation
{
    private:
        int _m;

        Eigen::MatrixXf _B;
        Eigen::MatrixXf _Bb;
        Eigen::VectorXf _zhd;
        int _agents, _edges;

        float _c_shape, _c_vel;

        Eigen::MatrixXf _compute_Dzt(Eigen::VectorXf);
        Eigen::MatrixXf _compute_DPzh(Eigen::VectorXf);

    public:
        BearingFormation(int, Eigen::VectorXf, Eigen::MatrixXf,
                float, float);
        BearingFormation();
        ~BearingFormation();

        Eigen::VectorXf get_u_acc(Eigen::VectorXf, Eigen::VectorXf);
        Eigen::VectorXf get_u_vel(Eigen::VectorXf);
};

#endif // BEARING_FORMATION_HH
