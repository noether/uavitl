#include "math_util.hh"
#include "Eigen/Core"
#include <math.h>

Eigen::Matrix3f get_R_rpy(float phi, float theta, float psi)
{
    float cph = cosf(phi);
    float sph = sinf(phi);
    float cte = cosf(theta);
    float ste = sinf(theta);
    float cps = cosf(psi);
    float sps = sinf(psi);

    Eigen::Matrix3f R;
    R << cte*cps              ,  cte*sps              ,    -ste,
        -cph*sps + sph*ste*sps,  cph*cps + sph*ste*sps, sph*cte,
         sph*sps + cph*ste*cps, -sph*cps + cph*ste*sps, cph*cte;

    return R;
}
