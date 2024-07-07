//
// Created by Aman's Laptop on 07-07-2024.
//

#ifndef LIGHT_H
#define LIGHT_H
#include <memory>

#include "ray.h"
#include "object.h"
#include "qbLinAlg/qbVector.h"


namespace qbRT
{
    class Light {
        public:
            Light();
            virtual ~Light();

            virtual bool CalculateLighting(qbVector<double> &intPoint, qbVector<double> &normal,
                std::vector<std::shared_ptr<Object>> &objList, std::shared_ptr<Object> &currObj,
                qbVector<double> &color, double &lightIntensity);
        public:
            qbVector<double> m_position {3};
            qbVector<double> m_color {3};
            double m_intensity{};
    };
}



#endif //LIGHT_H
