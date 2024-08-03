//
// Created by Aman's Laptop on 28-07-2024.
//

#include "../include/composite.h"

namespace qbRT::Shape
{
    Composite::Composite()
    {
        xLim = std::vector{1e6, -1e6};
        yLim = std::vector{1e6, -1e6};
        zLim = std::vector{1e6, -1e6};
    }

    Composite::~Composite()
    = default;

    void Composite::AddSubShape(std::shared_ptr<Object> obj)
    {
        qbVector2<double> x_lim;
        qbVector2<double> y_lim;
        qbVector2<double> z_lim;
        obj->GetExtents(x_lim, y_lim, z_lim);

        if(x_lim.GetElement(0) < xLim.GetElement(0))
            xLim.SetElement(0, x_lim.GetElement(0));
        if(x_lim.GetElement(1) > xLim.GetElement(1))
            xLim.SetElement(1, x_lim.GetElement(1));

        if(y_lim.GetElement(0) < yLim.GetElement(0))
            yLim.SetElement(0, y_lim.GetElement(0));
        if(y_lim.GetElement(1) > yLim.GetElement(1))
            yLim.SetElement(1, y_lim.GetElement(1));

        if(z_lim.GetElement(0) < zLim.GetElement(0))
            zLim.SetElement(0, z_lim.GetElement(0));
        if(z_lim.GetElement(1) > zLim.GetElement(1))
            zLim.SetElement(1, z_lim.GetElement(1));

        double xDist = xLim.GetElement(1) - xLim.GetElement(0);
        double yDist = yLim.GetElement(1) - yLim.GetElement(0);
        double zDist = zLim.GetElement(1) - zLim.GetElement(0);

        double xCentre = xLim.GetElement(0) + xDist / 2.0;
        double yCentre = yLim.GetElement(0) + yDist / 2.0;
        double zCentre = zLim.GetElement(0) + zDist / 2.0;

        boxTransform.SetTransform(qbVector3{std::vector{xCentre, yCentre, zCentre}},
            qbVector3{0.0, 0.0, 0.0},
            qbVector3{std::vector{xDist/2.0, yDist/2.0, zDist/2.0}}
            );

        boundingBox.SetTransform(boxTransform);

        shapes.push_back(obj);
    }

    void Composite::UpdateExtents()
    {
        xLim = std::vector{1e6, -1e6};
        yLim = std::vector{1e6, -1e6};
        zLim = std::vector{1e6, -1e6};

        qbVector2<double> x_lim;
        qbVector2<double> y_lim;
        qbVector2<double> z_lim;

        for(const auto& obj : shapes)
        {
            obj->GetExtents(x_lim, y_lim, z_lim);
            if(x_lim.GetElement(0) < xLim.GetElement(0))
                xLim.SetElement(0, x_lim.GetElement(0));
            if(x_lim.GetElement(1) > xLim.GetElement(1))
                xLim.SetElement(1, x_lim.GetElement(1));

            if(y_lim.GetElement(0) < yLim.GetElement(0))
                yLim.SetElement(0, y_lim.GetElement(0));
            if(y_lim.GetElement(1) > yLim.GetElement(1))
                yLim.SetElement(1, y_lim.GetElement(1));

            if(z_lim.GetElement(0) < zLim.GetElement(0))
                zLim.SetElement(0, z_lim.GetElement(0));
            if(z_lim.GetElement(1) > zLim.GetElement(1))
                zLim.SetElement(1, z_lim.GetElement(1));
        }

        double xDist = xLim.GetElement(1) - xLim.GetElement(0);
        double yDist = yLim.GetElement(1) - yLim.GetElement(0);
        double zDist = zLim.GetElement(1) - zLim.GetElement(0);

        double xCentre = xLim.GetElement(0) + (xDist / 2.0);
        double yCentre = yLim.GetElement(0) + (yDist / 2.0);
        double zCentre = zLim.GetElement(0) + (zDist / 2.0);

        boxTransform.SetTransform(qbVector3{std::vector{xCentre, yCentre, zCentre}},
            qbVector3{0.0, 0.0, 0.0},
            qbVector3{std::vector{xDist/2.0, yDist/2.0, zDist/2.0}}
            );

        boundingBox.SetTransform(boxTransform);
    }

    void Composite::GetExtents(qbVector2<double>& x, qbVector2<double>& y, qbVector2<double>& z)
    {
        std::vector<qbVector3<double>> extents = GetCube(xLim.GetElement(0), xLim.GetElement(1),
            yLim.GetElement(0), yLim.GetElement(1), zLim.GetElement(0), zLim.GetElement(1));

        double xMin = 1e6, yMin = 1e6, zMin = 1e6;
        double xMax = -1e6, yMax = -1e6, zMax = -1e6;

        for (int i = 0; i < 8; ++i)
        {
            extents[i] = m_transform.Apply(extents[i], FWDTFORM);
            xMin = std::min(xMin, extents[i].GetElement(0));
            xMax = std::max(xMax, extents[i].GetElement(0));
            yMin = std::min(yMin, extents[i].GetElement(1));
            yMax = std::max(yMax, extents[i].GetElement(1));
            zMin = std::min(zMin, extents[i].GetElement(2));
            zMax = std::max(zMax, extents[i].GetElement(2));
        }

        x.SetElement(0, xMin);
        x.SetElement(1, xMax);
        y.SetElement(0, yMin);
        y.SetElement(1, yMax);
        z.SetElement(0, zMin);
        z.SetElement(1, zMax);
    }

    bool Composite::TestIntersections(const Ray& ray, Data::HitData& hitData)
    {
        if(isVisible)
        {
            Ray backRay = m_transform.Apply(ray, BCKTFORM);

            if(!useBoundingBox || boundingBox.TestIntersections(backRay))
            {
                qbVector3<double> globalIntersection;
                Data::HitData locHitData;
                double currDist = 100e6;

                int shapeInd = TestIntersections(ray, backRay, globalIntersection, currDist, locHitData);

                if(shapeInd > -1)
                {
                    qbVector3 newNormal = m_transform.ApplyNormal(locHitData.localNormal);
                    newNormal.Normalize();
                    locHitData.hitObject -> ComputeUV(locHitData.localIntPoint, hitData.uvCoords);
                    uvCoords = hitData.uvCoords;

                    hitData.intPoint = globalIntersection;
                    hitData.localNormal = newNormal;
                    hitData.localColor = locHitData.localColor;
                    hitData.hitObject = locHitData.hitObject;
                    hitData.localIntPoint = locHitData.localIntPoint;

                    return true;
                }
            }
        }
        return false;
    }

    int Composite::TestIntersections(const Ray& castRay, const Ray& bckRay, qbVector3<double>& intPoint, double& currDist, Data::HitData& hitData)
    {
        int validShapeInd = -1;
        Data::HitData loc_hitData;
        for (int i = 0; i < shapes.size(); ++i)
        {
            auto obj = shapes[i];
            if(obj -> isVisible)
            {
                bool shapeHit = obj -> TestIntersections(bckRay, loc_hitData);
                if(shapeHit)
                {
                    qbVector3<double> loc_intPoint = m_transform.Apply(loc_hitData.intPoint, FWDTFORM);
                    double dist = (loc_intPoint - castRay.m_point1).norm();

                    if(dist < currDist)
                    {
                        currDist = dist;
                        validShapeInd = i;
                        intPoint = loc_intPoint;
                        hitData = loc_hitData;
                    }
                }
            }
        }

        return validShapeInd;
    }

}