//
// Created by Aman's Laptop on 28-07-2024.
//

#ifndef UTILS_H
#define UTILS_H

#include <memory>
#include "qbLinAlg/qbVector.h"


namespace qbRT
{
    class Object;

    namespace Data
    {
        struct HitData {
            qbVector<double> intPoint{3};
            qbVector<double> localNormal{3};
            qbVector<double> localColor{3};
            qbVector<double> localIntPoint{3};
            qbVector<double> uvCoords{2};
            std::shared_ptr<Object> hitObject;
        };
    }

    namespace Utils
    {
        void PrintVector(const qbVector<double>& vec);
    }
}


#endif //UTILS_H
