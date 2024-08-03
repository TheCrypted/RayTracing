//
// Created by Aman's Laptop on 30-06-2024.
//

#ifndef RAY_H
#define RAY_H

#include "./qbLinAlg/qbVector.h"
#include "./qbLinAlg/qbVector3.hpp"

namespace qbRT
{
    class Ray {
        public:
            Ray();
            Ray(const qbVector3<double> &point1, const qbVector3<double> &point2);

            [[nodiscard]] qbVector3<double> GetPoint1() const;
            [[nodiscard]] qbVector3<double> GetPoint2() const;
        public:
            qbVector3<double> m_point1;
            qbVector3<double> m_point2;
            qbVector3<double> m_lab;

    };
}



#endif //RAY_H
