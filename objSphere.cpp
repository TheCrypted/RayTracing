//
// Created by Aman's Laptop on 06-07-2024.
//

#include "include/objSphere.h"

namespace qbRT
{
    ObjSphere::ObjSphere()
    = default;

    ObjSphere::~ObjSphere()
    = default;

    bool ObjSphere::TestIntersections(const Ray &ray, qbVector<double> &intPoint, qbVector<double> &normal, qbVector<double> color)
    {
        qbVector<double> vhat = ray.m_lab;
        vhat.Normalize();

        const double a = 1.0f;
        const double b = 2.0 * qbVector<double>::dot(ray.m_point1, vhat);
        const double c = qbVector<double>::dot(ray.m_point1, ray.m_point1) - 1.0;

        double intTest = (b*b) - (4.0 * a * c);
        if(intTest <= 0.0)
        {
            return false;
        }
        double numRT = sqrtf(intTest);
        double t1 = (-b + numRT) / (2.0 * a);
        double t2 = (-b - numRT) / (2.0 * a);
        if (t1 < 0 || t2 < 0) return false;
        double t = (t1 < t2) ? t1 : t2;
        intPoint = ray.m_point1 + (vhat * t);
        return true;
    }

}