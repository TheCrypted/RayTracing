//
// Created by Aman's Laptop on 07-07-2024.
//

#include "include/objectPlane.h"
#include <cmath>

namespace qbRT
{
    ObjPlane::ObjPlane()
    = default;

    ObjPlane::~ObjPlane()
    = default;

    bool ObjPlane::TestIntersections(const Ray& rayOrig, qbVector<double>& intPoint, qbVector<double>& normal, qbVector<double>& color)
    {
        Ray backRay = m_transform.Apply(rayOrig, BCKTFORM);

        qbVector<double> cop_m_lab = backRay.m_lab;
        cop_m_lab.Normalize();

        if(!closeEnough(cop_m_lab.GetElement(2), 0.0))
        {
            double t = backRay.m_point1.GetElement(2) / - cop_m_lab.GetElement(2);

            if(t > 0)
            {
                const double u = backRay.m_point1.GetElement(0) + t * cop_m_lab.GetElement(0);
                const double v = backRay.m_point1.GetElement(1) + t * cop_m_lab.GetElement(1);

                if(abs(u) < 1.0 && abs(v) < 1.0)
                {
                    qbVector<double> intTemp = backRay.m_point1 + t * cop_m_lab;
                    intPoint = m_transform.Apply(intTemp, FWDTFORM);

                    qbVector localOrigin{std::vector{0.0, 0.0, 0.0}};
                    qbVector localNormal{std::vector{0.0, 0.0, -1.0}};
                    qbVector<double> globalOrigin = m_transform.Apply(localOrigin, FWDTFORM);
                    normal = m_transform.Apply(localNormal, FWDTFORM) - globalOrigin;
                    normal.Normalize();

                    color = baseColor;
                    return true;
                } else
                {
                    return false;
                }
            } else
            {
                return false;
            }
        } else
        {
            return false;
        }
        return false;
    }


}