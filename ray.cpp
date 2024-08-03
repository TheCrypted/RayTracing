//
// Created by Aman's Laptop on 30-06-2024.
//

#include "include/ray.h"

namespace qbRT
{
    Ray::Ray()
    {
        m_point1 = qbVector3{std::vector{0.0, 0.0, 0.0}};
        m_point2 = qbVector3{std::vector{0.0, 0.0, 1.0}};
        m_lab = m_point2 - m_point1;
    }

    Ray::Ray(const qbVector3<double> &point1, const qbVector3<double> &point2)
    {
        m_point1 = point1;
        m_point2 = point2;
        m_lab = m_point2 - m_point1;
    }

    qbVector3<double> Ray::GetPoint1() const
    {
        return m_point1;
    }

    qbVector3<double> Ray::GetPoint2() const
    {
        return m_point2;
    }
}