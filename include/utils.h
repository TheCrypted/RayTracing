//
// Created by Aman's Laptop on 28-07-2024.
//

#ifndef UTILS_H
#define UTILS_H

#include <memory>
#include "qbLinAlg/qbVector.h"
#include "qbLinAlg/qbVector2.hpp"
#include "qbLinAlg/qbVector3.hpp"


namespace qbRT
{
    class Object;

    namespace Data
    {
        struct HitData {
            qbVector3<double> intPoint;
            qbVector3<double> localNormal;
            qbVector3<double> localColor;
            qbVector3<double> localIntPoint;
            qbVector2<double> uvCoords;
            std::shared_ptr<Object> hitObject;
        };
    }

    namespace Utils
    {
        void PrintVector(const qbVector3<double>& vec);
    }
}


#endif //UTILS_H
