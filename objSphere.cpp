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

    bool ObjSphere::TestIntersections(const Ray &rayOrig, qbVector<double> &intPoint, qbVector<double> &normal, qbVector<double> &color)
    {
        Ray ray = m_transform.Apply(rayOrig, BCKTFORM);
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
        if (t1 < 0 || t2 < 0) {return false;}
        double t = (t1 < t2) ? t1 : t2;
        qbVector<double> intTemp = ray.m_point1 + (vhat * t);
        intPoint = m_transform.Apply(intTemp, FWDTFORM);

        qbVector<double> objOrigin = qbVector{std::vector{0.0, 0.0, 0.0}};
        qbVector<double> newObjOrigin = m_transform.Apply(objOrigin, FWDTFORM);

        normal = intPoint - newObjOrigin;
        normal.Normalize();

        color = baseColor;
        return true;
    }

}