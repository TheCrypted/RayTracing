//
// Created by Aman's Laptop on 26-07-2024.
//

#ifndef CONSTANTNORM_H
#define CONSTANTNORM_H
#include "normal.h"


namespace qbRT::Normal
{
    class Constant : public NormalBase {
        public:
            Constant() = default;
            ~Constant() override;

            qbVector<double> CompPerturbation(const qbVector<double>& normal, const qbVector<double>& uvCoords) override;

        public:
            qbVector<double> displacement{3};
    };
}



#endif //CONSTANTNORM_H
