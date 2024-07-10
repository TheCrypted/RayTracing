//
// Created by Aman's Laptop on 07-07-2024.
//

#include "../include/light.h"

namespace qbRT
{
    Light::Light()
    = default;

    Light::~Light()
    = default;

    bool Light::CalculateLighting(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
        const std::vector<std::shared_ptr<Object>> &objectList,
        const std::shared_ptr<Object> &currentObject,
        qbVector<double> &color, double &intensity)
    {
        return false;
    }
}