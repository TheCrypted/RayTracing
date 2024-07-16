//
// Created by Aman's Laptop on 16-07-2024.
//

#include "../include/marchSphere.h"

namespace qbRT::RM
{
    MarchSphere::MarchSphere()
    {
        std::function f = [=](qbVector<double>* loc, qbVector<double>* parms)
        {
            return this -> ObjectFcn(loc, parms);
        };

        SetObjectFunction(f);

        boundingBox.SetTransform(GTform{qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{1.2, 1.2, 1.2}}});
    }

    MarchSphere::~MarchSphere()
    = default;

    double MarchSphere::ObjectFcn(const qbVector<double>* p, const qbVector<double>* params)
    {
        qbVector center = std::vector{0.0, 0.0, 0.0};
        qbVector intParams = std::vector{1.0, 0.0, 0.0};

        return SDF::Sphere(*p, center, intParams);

    }


}
