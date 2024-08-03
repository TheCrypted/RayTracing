//
// Created by Aman's Laptop on 07-07-2024.
//

#ifndef LIGHT_H
#define LIGHT_H
#include <memory>

#include "ray.h"
#include "object.h"
#include "qbLinAlg/qbVector.h"
#include "qbLinAlg/qbVector2.hpp"
#include "qbLinAlg/qbVector3.hpp"
#include "qbLinAlg/qbVector4.hpp"


namespace qbRT
{
    class Light {
        public:
            Light();
            virtual ~Light();

            virtual bool CalculateLighting(const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
                    const std::vector<std::shared_ptr<Object>> &objectList,
                    const std::shared_ptr<Object> &currentObject,
                    qbVector3<double> &color, double &intensity);

        public:
            qbVector3<double> m_position;
            qbVector3<double> m_color;
            double m_intensity;
    };
}



#endif //LIGHT_H
