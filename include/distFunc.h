//
// Created by Aman's Laptop on 16-07-2024.
//

#ifndef DISTFUNC_H
#define DISTFUNC_H

#include "qbLinAlg/qbVector.h"
#include "qbLinAlg/qbVector2.hpp"
#include "qbLinAlg/qbVector3.hpp"
#include "qbLinAlg/qbVector4.hpp"

namespace qbRT::RM::SDF
{
    double Sphere(const qbVector3<double> &p, const qbVector3<double> center, const qbVector3<double> params);
    double Torus(const qbVector3<double> &p, const qbVector3<double> center, const qbVector3<double> params);
    double Cube(const qbVector3<double> &p, const qbVector3<double> center, const qbVector3<double> params);
}


#endif //DISTFUNC_H
