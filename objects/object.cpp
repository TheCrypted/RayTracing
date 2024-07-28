//
// Created by Aman's Laptop on 30-06-2024.
//

#include "../include/object.h"
#include <cmath>

#define EPSILON 1e-21f;

namespace qbRT
{
    Object::Object()
    = default;

    Object::~Object()
    = default;

    void Object::SetTransform(const qbRT::GTform &transform)
    {
        m_transform = transform;
    }

    bool Object::TestIntersections(const Ray &ray, Data::HitData &hitData)
    {
        return false;
    }

    void Object::ComputeUV(const qbVector<double>& localIntersection, qbVector<double>& uvCoords)
    {
        switch (uvMapType)
        {
            case qbRT::uvSphere:
            {
                double x = localIntersection.GetElement(0);
                double y = localIntersection.GetElement(1);
                double z = localIntersection.GetElement(2);

                double u = atan2(y, x) / M_PI;
                double v = 2.0 * (atan2(sqrtf(pow(x, 2.0) + pow(y, 2.0)), z) / M_PI) - 1.0;
                uvCoords.SetElement(0, u);
                uvCoords.SetElement(1, v);
                break;
            }

            case qbRT::uvPlane:
            {
                uvCoords.SetElement(0, localIntersection.GetElement(0));
                uvCoords.SetElement(1, localIntersection.GetElement(1));
                break;
            }

            case qbRT::uvCylinder:
            {
                double x = localIntersection.GetElement(0);
                double y = localIntersection.GetElement(1);
                double z = localIntersection.GetElement(2);

                double u = atan2(y, x) / M_PI;
                double v = -z;

                uvCoords.SetElement(0, u);
                uvCoords.SetElement(1, v);
                break;
            }

            case qbRT::uvCube:
            {
                double x = localIntersection.GetElement(0);
                double y = localIntersection.GetElement(1);
                double z = localIntersection.GetElement(2);
                double u = 0.0;
                double v = 0.0;

                qbMatrix2<double> uvTransform {3,3};
                uvTransform.SetToIdentity();

                if (closeEnough(x, -1.0))
                {
                    u = -(y * 0.25) - 0.75;
                    v = -z * 0.25;

                }
                else if (closeEnough(x, 1.0))
                {
                    u = (y * 0.25) + 0.25;
                    v = -z * 0.25;
                }
                else if (closeEnough(y, -1.0))
                {
                    u = (x * 0.25) - 0.25;
                    v = (-z * 0.25) - 0.5;
                }
                else if (closeEnough(y, 1.0))
                {
                    u = -(x * 0.25) - 0.25;;
                    v = (-z * 0.25) + 0.5;
                }
                else if (closeEnough(z, -1.0))
                {
                    u = (x * 0.25) + 0.75;
                    v = y * 0.25;
                }
                else if (closeEnough(z, 1.0))
                {
                    u = (x * 0.25) - 0.25;
                    v = y * 0.25;
                }

                uvCoords.SetElement(0, u);
                uvCoords.SetElement(1, v);

                break;
            }
        }
    }

    bool Object::closeEnough(const double a, const double b)
    {
        return std::fabs(a - b) < EPSILON;
    }

    bool Object::AssignMaterial(const std::shared_ptr<Material> &objectMaterial)
    {
        m_pMaterial = objectMaterial;
        m_hasMaterial = true;
        return m_hasMaterial;
    }
}
