//
// Created by Aman's Laptop on 30-06-2024.
//

#ifndef OBJECT_H
#define OBJECT_H

#include "qbLinAlg/qbVector.h"
#include "ray.h"
#include "gtfm.h"

namespace qbRT
{
    class Material;

    class Object {
        public:
            Object();
            virtual ~Object();

            void SetTransform(const qbRT::GTform &transform);
            virtual bool TestIntersections(const Ray &ray, qbVector<double> &intPoint, qbVector<double> &normal, qbVector<double> &color);
            static bool closeEnough(double a, double b);
            bool AssignMaterial(const std::shared_ptr<Material> &objectMaterial);

        public:
            bool isVisible = true;

            qbVector<double> baseColor {3};
            GTform m_transform;

            std::shared_ptr<Material> m_pMaterial;
            qbVector<double> uvCoords{2};

            bool m_hasMaterial = false;
    };
}



#endif //OBJECT_H
