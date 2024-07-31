//
// Created by Aman's Laptop on 12-07-2024.
//

#include "../include/objectCylinder.h"

namespace qbRT
{
    ObjCylinder::ObjCylinder()
    {
        uvMapType = uvCylinder;

        boxTransform.SetTransform(qbVector{std::vector{0.0, 0.0, 0.5}},
            qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{1.0, 1.0, 1.0}});
    }

    ObjCylinder::~ObjCylinder()
    = default;

    bool ObjCylinder::TestIntersections(const Ray& ray, Data::HitData& hitData)
    {
        Ray backRay = m_transform.Apply(ray, BCKTFORM);

        qbVector<double> v = backRay.m_lab;
        v.Normalize();

        qbVector<double> p = backRay.m_point1;

        double a  = std::pow(v.GetElement(0), 2.0) + std::pow(v.GetElement(1), 2.0);
        double b = 2.0 * (v.GetElement(0) * p.GetElement(0) + v.GetElement(1) * p.GetElement(1));
        double c = std::pow(p.GetElement(0), 2.0) + std::pow(p.GetElement(1), 2.0) - 1.0;

        double sqrt = std::pow(b, 2.0) - 4.0 * a * c; // [WARNING] THIS ISNT THE ACTUAL ROOT
        std::array<qbVector<double>, 4> poi;
        std::array<double, 4> t;
        bool valid1, valid2, valid3, valid4;

        if(sqrt > 0.0)
        {
            t[0] = (-b + std::sqrt(sqrt)) / (2.0 * a);
            t[1] = (-b - std::sqrt(sqrt)) / (2.0 * a);

            poi[0] = p + v * t[0];
            poi[1] = p + v * t[1];

            if((t[0] > 0.0) && (fabs(poi[0].GetElement(2)) < 1.0)) valid1 = true;
            else
            {
                valid1 = false;
                t[0] = 100e6;
            }

            if((t[1] > 0.0) && (fabs(poi[1].GetElement(2)) < 1.0)) valid2 = true;
            else
            {
                valid2 = false;
                t[1] = 100e6;
            }

        } else
        {
            valid1 = false;
            t[0] = 100e6;
            valid2 = false;
            t[1] = 100e6;
        }

        if(closeEnough(v.GetElement(2), 0.0))
        {
            valid3 = false;
            t[2] = 100e6;
            valid4 = false;
            t[3] = 100e6;
        } else
        {
            t[2] = (p.GetElement(2) - 1.0) / -v.GetElement(2);
            t[3] = (p.GetElement(2) + 1.0) / -v.GetElement(2);

            poi[2] = p + t[2] * v;
            poi[3] = p + t[3] * v;

            if ((t[2] > 0.0) && (sqrtf(std::pow(poi[2].GetElement(0), 2.0) + std::pow(poi[2].GetElement(1), 2.0)) < 1.0))
            {
                valid3 = true;
            }
            else
            {
                valid3 = false;
                t[2] = 100e6;
            }

            if ((t[3] > 0.0) && (sqrtf(std::pow(poi[3].GetElement(0), 2.0) + std::pow(poi[3].GetElement(1), 2.0)) < 1.0))
            {
                valid4 = true;
            }
            else
            {
                valid4 = false;
                t[3] = 100e6;
            }
        }

        if(!valid1 && !valid2 && !valid3 && !valid4) return false;

        int minInd = 0;
        double minVal = 10e6;
        for (int i = 0; i < 4; ++i)
        {
            if(t[i] < minVal)
            {
                minVal = t[i];
                minInd = i;
            }
        }

        qbVector<double> finalPOI = poi[minInd];

        if(minInd < 2)
        {
            hitData.intPoint = m_transform.Apply(finalPOI, FWDTFORM);

            qbVector<double> preNorm{3};
            qbVector<double> resNormal{3};
            qbVector<double> globalOrigin = m_transform.Apply(qbVector{std::vector{0.0, 0.0, 0.0}}, FWDTFORM);
            preNorm.SetElement(0, finalPOI.GetElement(0));
            preNorm.SetElement(1, finalPOI.GetElement(1));
            preNorm.SetElement(2, 0.0);
            resNormal = m_transform.ApplyNormal(preNorm);
            resNormal.Normalize();

            hitData.localNormal = resNormal;
            hitData.localColor = baseColor;

            double x = finalPOI.GetElement(0);
            double y = finalPOI.GetElement(1);

            double u = atan(y/x) / M_PI;
            double v1 = finalPOI.GetElement(2);

            ComputeUV(finalPOI, uvCoords);
            hitData.uvCoords = uvCoords;
            hitData.hitObject = std::make_shared<Object>(*this);

            return true;
        } else
        {
            if(!closeEnough(v.GetElement(2), 0.0))
            {
                if(sqrtf(std::pow(finalPOI.GetElement(0), 2.0) + std::pow(finalPOI.GetElement(1), 2.0)) < 1.0)
                {
                    hitData.intPoint = m_transform.Apply(finalPOI, FWDTFORM);

                    qbVector preNorm{std::vector{0.0, 0.0, 0.0 + finalPOI.GetElement(2)}};
                    hitData.localNormal = m_transform.ApplyNormal(preNorm);

                    hitData.localNormal.Normalize();
                    hitData.localColor = baseColor;

                    ComputeUV(finalPOI, uvCoords);
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
        }

        return false;
    }
}