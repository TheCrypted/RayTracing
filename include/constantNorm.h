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

            qbVector3<double> CompPerturbation(const qbVector3<double>& normal, const qbVector2<double>& uvCoords) override;

        public:
            qbVector3<double> displacement;
    };
}



#endif //CONSTANTNORM_H
