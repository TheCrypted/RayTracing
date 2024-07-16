//
// Created by Aman's Laptop on 16-07-2024.
//

#include "../include/distFunc.h"

namespace qbRT::RM::SDF
{
    double Sphere(const qbVector3<double>& p, const qbVector3<double> center, const qbVector3<double> params)
    {
        return (p - center).norm() - params.GetElement(0);
    }

    double Torus(const qbVector3<double>& p, const qbVector3<double> center, const qbVector3<double> params)
    {
        double x = p.GetElement(0) - center.GetElement(0);
        double y = p.GetElement(1) - center.GetElement(1);
        double z = p.GetElement(2) - center.GetElement(2);

        double t1 = sqrtf(x * x + y * y) - params.GetElement(0);

        return sqrtf(t1 * t1 + z * z) - params.GetElement(1);
    }

    double Cube(const qbVector3<double>& p, const qbVector3<double> center, const qbVector3<double> params)
    {
        qbVector3<double> location = p - center;
        double ax = fabs(location.GetElement(0)) - params.GetElement(0);
        double ay = fabs(location.GetElement(1)) - params.GetElement(1);
        double az = fabs(location.GetElement(2)) - params.GetElement(2);

        double bx = std::max(ax, 0.0);
        double by = std::max(ay, 0.0);
        double bz = std::max(az, 0.0);

        double intDist = std::min(std::max(ax, std::max(ay, az)), 0.0);
        double extDist = sqrt(bx * bx + by * by + bz * bz);

        return intDist + extDist;
    }



}