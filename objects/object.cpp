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

    void Object::GetExtents(qbVector2<double>& x, qbVector2<double>& y, qbVector2<double>& z)
    {
        std::vector<qbVector3<double>> cubeVerts = GetCube(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

        GTform netTransform = m_transform * boxTransform;

        double xMin = 10e6;
        double yMin = 10e6;
        double zMin = 10e6;
        double xMax = -10e6;
        double yMax = -10e6;
        double zMax = -10e6;

        for (const auto & cubeVert : cubeVerts)
        {
            xMin = std::min(xMin, cubeVert.GetElement(0));
            xMax = std::max(xMax, cubeVert.GetElement(0));
            yMin = std::min(yMin, cubeVert.GetElement(1));
            yMax = std::max(yMax, cubeVert.GetElement(1));
            zMin = std::min(zMin, cubeVert.GetElement(2));
            zMax = std::max(zMax, cubeVert.GetElement(2));
        }

        x.SetElement(0, xMin);
        x.SetElement(1, xMax);
        y.SetElement(0, yMin);
        y.SetElement(1, yMax);
        z.SetElement(0, zMin);
        z.SetElement(1, zMax);
    }

    void Object::GetExtents(const GTform& transform, qbVector2<double>& x, qbVector2<double>& y, qbVector2<double>& z)
    {

    }

    std::vector<qbVector3<double>> Object::GetCube(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax)
    {
        std::vector<qbVector3<double>> cornerPoints (8);

        cornerPoints.at(0) = std::vector {xMin - boxPadding, yMin - boxPadding, zMin - boxPadding};
        cornerPoints.at(1) = std::vector {xMin - boxPadding, yMin - boxPadding, zMax + boxPadding};
        cornerPoints.at(2) = std::vector {xMax + boxPadding, yMin - boxPadding, zMax + boxPadding};
        cornerPoints.at(3) = std::vector {xMax + boxPadding, yMin - boxPadding, zMin - boxPadding};
        cornerPoints.at(4) = std::vector {xMin - boxPadding, yMax + boxPadding, zMin - boxPadding};
        cornerPoints.at(5) = std::vector {xMin - boxPadding, yMax + boxPadding, zMax - boxPadding};
        cornerPoints.at(6) = std::vector {xMax + boxPadding, yMax + boxPadding, zMax + boxPadding};
        cornerPoints.at(7) = std::vector {xMax + boxPadding, yMax + boxPadding, zMin - boxPadding};

        return cornerPoints;
    }


    void Object::SetTransform(const qbRT::GTform &transform)
    {
        m_transform = transform;
    }

    bool Object::TestIntersections(const Ray &ray, Data::HitData &hitData)
    {
        return false;
    }

    void Object::ComputeUV(const qbVector3<double>& localIntersection, qbVector2<double>& uvCoords)
    {
        switch (uvMapType)
        {
            case uvSphere:
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
