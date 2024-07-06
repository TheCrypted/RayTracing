//
// Created by Aman's Laptop on 30-06-2024.
//

#include "include/object.h"
#include <cmath>

#define EPSILON 1e-21f;

namespace qbRT
{
    Object::Object()
    = default;

    Object::~Object()
    = default;

    bool Object::TestIntersections(const Ray &ray, qbVector<double> &intPoint, qbVector<double> &normal, qbVector<double> color)
    {
        return false;
    }

    bool Object::closeEnough(const double a, const double b)
    {
        return std::abs(a - b) < EPSILON;
    }
}
