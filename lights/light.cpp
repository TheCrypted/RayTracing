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

    bool Light::CalculateLighting(qbVector<double> &intPoint, qbVector<double> &normal,
                std::vector<std::shared_ptr<Object>> &objList, std::shared_ptr<Object> &currObj,
                qbVector<double> &color, double &lightIntensity)
    {
        return false;
    }
}