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

    qbVector<double> BasicRough::CompPerturbation(const qbVector<double>& normal, const qbVector<double>& uvCoords)
    {
        std::uniform_real_distribution randDist{-amplitude, amplitude};
        qbVector perturbation = std::vector{randDist(*randGen), randDist(*randGen), randDist(*randGen)};

        return PerturbNormal(normal, perturbation);
    }



}