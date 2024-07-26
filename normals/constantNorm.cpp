//
// Created by Aman's Laptop on 26-07-2024.
//

#include "../include/constantNorm.h"


namespace qbRT::Normal
{
    Constant::~Constant()
    = default;

    qbVector<double> Constant::CompPerturbation(const qbVector<double>& normal, const qbVector<double>& uvCoords)
    {
        return PerturbNormal(normal, displacement);
    }

}