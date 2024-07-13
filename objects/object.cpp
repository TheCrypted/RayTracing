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

    bool Object::TestIntersections(const Ray &ray, qbVector<double> &intPoint, qbVector<double> &normal, qbVector<double> &color)
    {
        return false;
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
