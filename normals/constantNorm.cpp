//
// Created by Aman's Laptop on 26-07-2024.
//

#include "../include/constantNorm.h"


namespace qbRT::Normal
{
    Constant::~Constant()
    = default;

    qbVector3<double> Constant::CompPerturbation(const qbVector3<double>& normal, const qbVector2<double>& uvCoords)
    {
        return PerturbNormal(normal, displacement);
    }

}