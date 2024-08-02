//
// Created by Aman's Laptop on 30-06-2024.
//

#ifndef OBJECT_H
#define OBJECT_H

#include "qbLinAlg/qbVector.h"
#include "ray.h"
#include "gtfm.h"
#include "utils.h"
#include "qbLinAlg/qbVector2.hpp"

namespace qbRT
{
    class Material;

    constexpr int uvSphere = 0;
    constexpr int uvPlane = 1;
    constexpr int uvCylinder = 2;
    constexpr int uvCube = 3;

    class Object {
        public:
            Object();
            virtual ~Object();

            virtual void GetExtents(qbVector2<double>& x, qbVector2<double>& y, qbVector2<double>& z);
            virtual void GetExtents(const GTform& transform, qbVector2<double>& x, qbVector2<double>& y, qbVector2<double>& z);
            std::vector<qbVector3<double>> GetCube(double xMax, double xMin, double yMax, double yMin, double zMax, double zMin);

            void SetTransform(const GTform &transform);
            virtual bool TestIntersections(const Ray &ray, Data::HitData &hitData);
            static bool closeEnough(double a, double b);
            bool AssignMaterial(const std::shared_ptr<Material> &objectMaterial);
            void ComputeUV(const qbVector3<double>& localIntersection, qbVector2<double>& uvCoords);

        public:
            bool isVisible = true;

            qbVector3<double> baseColor;
            GTform m_transform;

            std::shared_ptr<Material> m_pMaterial;
            qbVector2<double> uvCoords;

            bool m_hasMaterial = false;
            int uvMapType = uvSphere;

            GTform boxTransform;
            double boxPadding = 0.0;
    };
}



#endif //OBJECT_H
