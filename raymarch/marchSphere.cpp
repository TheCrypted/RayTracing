//
// Created by Aman's Laptop on 16-07-2024.
//

#include "../include/marchSphere.h"

namespace qbRT::RM
{
    MarchSphere::MarchSphere()
    {
        std::function f = [=](qbVector3<double>* loc, qbVector3<double>* parms)
        {
            return this -> ObjectFcn(loc, parms);
        };

        SetObjectFunction(f);

        boundingBox.SetTransform(GTform{qbVector3{0.0, 0.0, 0.0},
            qbVector3{0.0, 0.0, 0.0},
            qbVector3{1.2, 1.2, 1.2}});
    }

    MarchSphere::~MarchSphere()
    = default;

    double MarchSphere::ObjectFcn(const qbVector3<double>* p, const qbVector3<double>* params)
    {
        qbVector3 center = std::vector{0.0, 0.0, 0.0};
        qbVector3 intParams = std::vector{1.0, 0.0, 0.0};

        return SDF::Sphere(*p, center, intParams);

    }


}
