//
// Created by Aman's Laptop on 06-07-2024.
//

#include "../include/objSphere.h"

namespace qbRT
{
    ObjSphere::ObjSphere()
    {
        uvMapType = uvSphere;
        boxTransform.SetTransform(qbVector3{0.0, 0.0, 0.0},
            qbVector3{0.0, 0.0, 0.0},
            qbVector3{1.0, 1.0, 1.0});
    }

    ObjSphere::~ObjSphere()
    = default;

    bool ObjSphere::TestIntersections(const Ray &rayOrig, Data::HitData& hitData)
    {
        Ray ray = m_transform.Apply(rayOrig, BCKTFORM);
        qbVector3 vhat = ray.m_lab;

        const double a = qbVector3<double>::dot(vhat, vhat);
        const double b = 2.0 * qbVector3<double>::dot(ray.m_point1, vhat);
        const double c = qbVector3<double>::dot(ray.m_point1, ray.m_point1) - 1.0;

        double intTest = (b*b) - (4.0 * a * c);
        if(intTest <= 0.0)
        {
            return false;
        }
        double numRT = sqrt(intTest);
        double t1 = (-b + numRT) / (2.0 * a);
        double t2 = (-b - numRT) / (2.0 * a);
        if (t1 < 0.0 && t2 < 0.0)
        {
            return false;
        }

        double t;

        if(t1 < t2)
        {
            if(t1 > 0.0) t = t1;
            else if(t2 > 0.0) t = t2;
            else return false;
        } else
        {
            if(t2 > 0.0) t = t2;
            else if(t1 > 0.0) t = t1;
            else return false;
        }

        qbVector3<double> intTemp = ray.m_point1 + (vhat * t);
        hitData.intPoint = m_transform.Apply(intTemp, FWDTFORM);

        const qbVector3<double>& locNorm = intTemp;
        hitData.localNormal = m_transform.ApplyNormal(locNorm);
        hitData.localNormal.Normalize();

        hitData.localColor = baseColor;

        double x = hitData.intPoint.GetElement(0);
        double y = hitData.intPoint.GetElement(1);
        double z = hitData.intPoint.GetElement(2);

        double u = atan(sqrtf(pow(x, 2.0) + pow(y, 2.0)));
        double v = atan(y/x);

        if(x < 0) v += M_PI;

        u /= M_PI;
        v /= M_PI;

        uvCoords.SetElement(0, u);
        uvCoords.SetElement(1, v);

        return true;
    }

}