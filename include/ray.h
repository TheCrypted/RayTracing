//
// Created by Aman's Laptop on 30-06-2024.
//

#ifndef RAY_H
#define RAY_H

#include "./qbLinAlg/qbVector.h"

namespace qbRT
{
    class Ray {
        public:
            Ray();
            Ray(const qbVector<double> &point1, const qbVector<double> &point2);

            [[nodiscard]] qbVector<double> GetPoint1() const;
            [[nodiscard]] qbVector<double> GetPoint2() const;
        public:
            qbVector<double> m_point1 {3};
            qbVector<double> m_point2 {3};
            qbVector<double> m_lab {3};

    };
}



#endif //RAY_H
