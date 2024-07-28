//
// Created by Aman's Laptop on 16-07-2024.
//

#include "../include/rayMarchBase.h"

namespace qbRT::RM
{
    RayMarchBase::RayMarchBase()
    {
        epsilon = 1e-12;
        maxIterations = 100;
    }

    RayMarchBase::~RayMarchBase()
    = default;

    bool RayMarchBase::TestIntersections(const Ray& ray, Data::HitData& hitData)
    {
        if(hasObjectFunction)
        {
            if(!isVisible) return false;

            Ray backRay = m_transform.Apply(ray, BCKTFORM);

            Data::HitData boundHitData;

            if(boundingBox.TestIntersections(backRay, boundHitData))
            {
                qbVector<double> vhat = backRay.m_lab;
                vhat.Normalize();

                qbVector<double> currLoc = backRay.m_point1;
                double dist = EvaluateSDF(&currLoc, &params);
                int currIter = 0;

                while(dist > epsilon && currIter < maxIterations)
                {
                    currLoc = currLoc + vhat * dist;
                    dist = EvaluateSDF(&currLoc, &params);
                    if(dist > 1e6)
                    {
                        currIter = maxIterations;
                        break;
                    }
                    currIter++;
                }

                if(currIter == maxIterations)
                {
                    return false;
                }
                hitData.intPoint = m_transform.Apply(currLoc, FWDTFORM);

                qbVector<double> surfaceNormal{3};
                qbVector<double> x1 = currLoc + m_xDisp;
                qbVector<double> x2 = currLoc - m_xDisp;
                qbVector<double> y1 = currLoc + m_yDisp;
                qbVector<double> y2 = currLoc - m_yDisp;
                qbVector<double> z1 = currLoc + m_zDisp;
                qbVector<double> z2 = currLoc - m_zDisp;
                surfaceNormal.SetElement(0, EvaluateSDF(&x1, &params) - EvaluateSDF(&x2, &params));
                surfaceNormal.SetElement(1, EvaluateSDF(&y1, &params) - EvaluateSDF(&y2, &params));
                surfaceNormal.SetElement(2, EvaluateSDF(&z1, &params) - EvaluateSDF(&z2, &params));
                surfaceNormal.Normalize();

                hitData.localNormal = m_transform.ApplyNormal(surfaceNormal);
                hitData.localColor = baseColor;

                return true;
            }
        }
        return false;
    }

    void RayMarchBase::SetObjectFunction(std::function<double(qbVector<double>*, qbVector<double>*)> objFunc)
    {
        objectFunction = objFunc;
        hasObjectFunction = true;
    }

    double RayMarchBase::EvaluateSDF(qbVector<double>* location, qbVector<double>* params)
    {
        return objectFunction(location, params);
    }




}