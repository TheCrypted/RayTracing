//
// Created by Aman's Laptop on 07-07-2024.
//

#include "../include/objectPlane.h"

namespace qbRT
{
    ObjPlane::ObjPlane()
    {
        uvMapType = uvPlane;
        boxTransform.SetTransform(qbVector3{0.0, 0.0, 0.0},
            qbVector3{0.0, 0.0, 0.0},
            qbVector3{1.0, 1.0, 0.01});
    }

    ObjPlane::~ObjPlane()
    = default;

    bool ObjPlane::TestIntersections(const Ray& rayOrig, Data::HitData& hitData)
    {
        Ray backRay = m_transform.Apply(rayOrig, BCKTFORM);

        qbVector3 cop_m_lab = backRay.m_lab;

        if(!closeEnough(cop_m_lab.GetElement(2), 0.0))
        {
            double t = backRay.m_point1.GetElement(2) / - cop_m_lab.GetElement(2);

            if(t > 0)
            {
                const double u = backRay.m_point1.GetElement(0) + t * cop_m_lab.GetElement(0);
                const double v = backRay.m_point1.GetElement(1) + t * cop_m_lab.GetElement(1);

                if(abs(u) < 1.0 && abs(v) < 1.0)
                {
                    qbVector3 intTemp = backRay.m_point1 + t * cop_m_lab;
                    hitData.intPoint = m_transform.Apply(intTemp, FWDTFORM);

                    qbVector3 locNorm{0.0, 0.0, -1.0};
                    hitData.localNormal = m_transform.ApplyNormal(locNorm);
                    hitData.localNormal.Normalize();

                    hitData.localColor = baseColor;

                    ComputeUV(intTemp, uvCoords);
                    hitData.uvCoords = uvCoords;
                    hitData.hitObject = std::make_shared<Object>(*this);

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