#ifndef POSITION_FORMATION_HH
#define POSITION_FORMATION_HH 1

#include <Eigen/Dense>
#include <Eigen/Sparse>

class PositionFormation{
    private:
        int _m;

        Eigen::MatrixXf _B;
        Eigen::MatrixXf _Bb;
        Eigen::VectorXf _zd;
        int _agents, _edges;

        float _c_shape, _c_vel;

    public:
        PositionFormation(int, Eigen::VectorXf, Eigen::MatrixXf,
                float, float);
        PositionFormation();
        ~PositionFormation();

        Eigen::VectorXf get_u_acc(Eigen::VectorXf, Eigen::VectorXf);
        Eigen::VectorXf get_u_vel(Eigen::VectorXf);
};

#endif // POSITION_FORMATION_HH
