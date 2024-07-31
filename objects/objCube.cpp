//
// Created by Aman's Laptop on 15-07-2024.
//

#include "../include/objCube.h"

namespace qbRT
{
    ObjCube::ObjCube()
    {
        uvMapType = uvCube;
        boxTransform.SetTransform(qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{1.0, 1.0, 1.0}});
    }

    ObjCube::~ObjCube()
    = default;

    bool ObjCube::TestIntersections(const Ray& ray, Data::HitData& hitData)
    {
        if(!isVisible) return false;

        Ray backRay = m_transform.Apply(ray, BCKTFORM);

        double ax = backRay.m_point1.GetElement(0);
        double ay = backRay.m_point1.GetElement(1);
        double az = backRay.m_point1.GetElement(2);

        qbVector<double> k = backRay.m_lab;
        k.Normalize();

        double kx = k.GetElement(0);
        double ky = k.GetElement(1);
        double kz = k.GetElement(2);

        if(!closeEnough(kz, 0.0))
        {
            t[0] = (az - 1.0) / -kz;
            t[1] = (az + 1.0) / -kz;
            u[0] = ax + kx * t[0];
            u[1] = ax + kx * t[1];
            v[0] = ay + ky * t[0];
            v[1] = ay + ky * t[1];
        } else
        {
            t[0] = 100e6;
            t[1] = 100e6;
            u[0] = 0.0;
            u[1] = 0.0;
            v[0] = 0.0;
            v[1] = 0.0;
        }

        if(!closeEnough(kx, 0.0))
        {
            t[2] = (ax + 1.0) / -kx;
            t[3] = (ax - 1.0) / -kx;
            u[2] = az + kz * t[2];
            u[3] = az + kz * t[3];
            v[2] = ay + ky * t[2];
            v[3] = ay + ky * t[3];
        } else
        {
            t[2] = 100e6;
            t[3] = 100e6;
            u[2] = 0.0;
            u[3] = 0.0;
            v[2] = 0.0;
            v[3] = 0.0;
        }

        if(!closeEnough(ky, 0.0))
        {
            t[4] = (ay + 1.0) / -ky;
            t[5] = (ay - 1.0) / -ky;
            u[4] = ax + kx * t[4];
            u[5] = ax + kx * t[5];
            v[4] = az + kz * t[4];
            v[5] = az + kz * t[5];
        } else
        {
            t[4] = 100e6;
            t[5] = 100e6;
            u[4] = 0.0;
            u[5] = 0.0;
            v[4] = 0.0;
            v[5] = 0.0;
        }

        double finU = 0.0, finV = 0.0, finT = 100e6;
        int finInd = 0;
        bool validIntersection = false;
        for (int i = 0; i < 6; ++i)
        {
            if((t[i] < finT) && (t[i] > 0.0) && (abs(u[i]) < 1.0) && (abs(v[i]) < 1.0))
            {
                finT = t[i];
                finU = u[i];
                finV = v[i];
                finInd = i;
                validIntersection = true;
            }
        }

        if(validIntersection)
        {
            qbVector<double> locIntPoint = backRay.m_point1 + finT * k;
            qbVector<double> norm;

            switch (finInd)
            {
                case 0:
                    norm = std::vector{0.0, 0.0, 1.0};
                    break;
                case 1:
                    norm = std::vector{0.0, 0.0, -1.0};
                    break;
                case 2:
                    norm = std::vector{-1.0, 0.0, 0.0};
                    break;
                case 3:
                    norm = std::vector{1.0, 0.0, 0.0};
                    break;
                case 4:
                    norm = std::vector{0.0, -1.0, 0.0};
                    break;
                case 5:
                    norm = std::vector{0.0, 1.0, 0.0};
                    break;
            }
            hitData.intPoint = m_transform.Apply(locIntPoint, FWDTFORM);

            hitData.localNormal = m_transform.ApplyNormal(norm);
            hitData.localNormal.Normalize();

            hitData.localColor = baseColor;

            ComputeUV(locIntPoint, uvCoords);
            hitData.uvCoords = uvCoords;
            hitData.hitObject = std::make_shared<Object>(*this);

            return true;
        } else
        {
            return false;
        }
    }

    bool ObjCube::TestIntersections(const Ray& ray)
    {
        if(!isVisible) return false;

        Ray backRay = m_transform.Apply(ray, BCKTFORM);

        double ax = backRay.m_point1.GetElement(0);
        double ay = backRay.m_point1.GetElement(1);
        double az = backRay.m_point1.GetElement(2);

        qbVector<double> k = backRay.m_lab;
        k.Normalize();

        double kx = k.GetElement(0);
        double ky = k.GetElement(1);
        double kz = k.GetElement(2);

        if(!closeEnough(kz, 0.0))
        {
            t[0] = (az - 1.0) / -kz;
            t[1] = (az + 1.0) / -kz;
            u[0] = ax + kx * t[0];
            u[1] = ax + kx * t[1];
            v[0] = ay + ky * t[0];
            v[1] = ay + ky * t[1];
        }

        if(!closeEnough(kx, 0.0))
        {
            t[2] = (ax + 1.0) / -kx;
            t[3] = (ax - 1.0) / -kx;
            u[2] = az + kz * t[2];
            u[3] = az + kz * t[3];
            v[2] = ay + ky * t[2];
            v[3] = ay + ky * t[3];
        }

        if(!closeEnough(ky, 0.0))
        {
            t[4] = (ay + 1.0) / -ky;
            t[5] = (ay - 1.0) / -ky;
            u[4] = ax + kx * t[4];
            u[5] = ax + kx * t[5];
            v[4] = az + kz * t[4];
            v[5] = az + kz * t[5];
        }

        bool validIntersection = false;
        for (int i = 0; i < 6 && !validIntersection; i++)
        {
            if((t[i] < 100e6) && (t[i] > 0.0) && (abs(u[i]) <= 1.0) && (abs(v[i]) <= 1.0))
            {
                validIntersection = true;
            }
        }
        return validIntersection;
    }



}