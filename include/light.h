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

        virtual bool CalculateLighting(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                const std::vector<std::shared_ptr<Object>> &objectList,
                const std::shared_ptr<Object> &currentObject,
                qbVector<double> &color, double &intensity);

        public:
            qbVector<double> m_position {3};
            qbVector<double> m_color {3};
            double m_intensity{};
    };
}



#endif //LIGHT_H
