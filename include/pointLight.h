//
// Created by Aman's Laptop on 07-07-2024.
//

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"

namespace qbRT
{
    class PointLight : public Light {
        public:
            PointLight();
            ~PointLight() override;

        bool CalculateLighting(const qbVector<double> &intPoint, const qbVector<double> &normal,
            const std::vector<std::shared_ptr<Object>> &objList, const std::shared_ptr<Object> &currObj,
            qbVector<double> &color, double &lightIntensity) override;

        public:
            qbVector<double> m_position {3};
            qbVector<double> m_color {3};
            double m_intensity{};
    };
}



#endif //POINTLIGHT_H
