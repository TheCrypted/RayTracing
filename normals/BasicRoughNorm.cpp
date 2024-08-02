//
// Created by Aman's Laptop on 26-07-2024.
//

#include "../include/BasicRoughNorm.h"

namespace qbRT::Normal
{
    BasicRough::BasicRough()
    {
        std::random_device rd;
        std::seed_seq seed{rd(), rd(), rd(), rd()};

        randGen = std::make_shared<std::mt19937>(seed);
    }

    BasicRough::~BasicRough()
    = default;

    qbVector3<double> BasicRough::CompPerturbation(const qbVector3<double>& normal, const qbVector2<double>& uvCoords)
    {
        std::uniform_real_distribution randDist{-amplitude, amplitude};
        qbVector3 perturbation = std::vector{randDist(*randGen), randDist(*randGen), randDist(*randGen)};

        return PerturbNormal(normal, perturbation);
    }



}