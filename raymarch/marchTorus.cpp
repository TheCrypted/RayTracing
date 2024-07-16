//
// Created by Aman's Laptop on 16-07-2024.
//

#include "../include/marchTorus.h"

namespace qbRT::RM
{
    MarchTorus::MarchTorus()
    {
        std::function f = [=](qbVector<double>* loc, qbVector<double>* parms)
        {
            return this -> ObjectFcn(loc, parms);
        };

        SetObjectFunction(f);

        boundingBox.SetTransform(GTform{qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{1.3, 1.3, 1.3}}});
    }

    MarchTorus::~MarchTorus()
    = default;

    void MarchTorus::SetRadii(double r1, double r2)
    {
        params.SetElement(0, r1);
        params.SetElement(1, r2);
        UpdateBounds();
    }

    void MarchTorus::UpdateBounds()
    {
        boundingBox.SetTransform(GTform{qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{r1+r2+0.3, r1+r2+0.3, r2+0.2}}});
    }

    double MarchTorus::ObjectFcn(const qbVector<double>* p, const qbVector<double>* params)
    {
        qbVector center = std::vector{0.0, 0.0, 0.0};
        return SDF::Torus(*p, center, *params);
    }


}