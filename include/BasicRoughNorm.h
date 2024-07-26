//
// Created by Aman's Laptop on 26-07-2024.
//

#ifndef BASICROUGHNORM_H
#define BASICROUGHNORM_H

#include <random>
#include "normal.h"


namespace qbRT::Normal
{
    class BasicRough : public NormalBase{
        public:
            BasicRough();
            ~BasicRough() override;

            qbVector<double> CompPerturbation(const qbVector<double>& normal, const qbVector<double>& uvCoords) override;

        public:
            std::shared_ptr<std::mt19937> randGen;
    };
}



#endif //BASICROUGHNORM_H
