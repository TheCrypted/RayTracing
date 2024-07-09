//
// Created by Aman's Laptop on 07-07-2024.
//

#include "../include/pointLight.h"

#include <complex>

namespace qbRT
{
    PointLight::PointLight()
    {
        m_color = qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}};
        m_intensity = 1.0;
    }

    PointLight::~PointLight()
    = default;

    bool PointLight::CalculateLighting(qbVector<double> &intPoint, qbVector<double> &normal,
                std::vector<std::shared_ptr<Object>> &objList, std::shared_ptr<Object> &currObj,
                qbVector<double> &color, double &lightIntensity)
    {
        const qbVector<double> lightDir = (m_position - intPoint).Normalized();

        qbVector<double> interPoint{3};
        qbVector<double> interNormal{3};
        qbVector<double> interColor{3};
        bool validInt = false;
        Ray lightRay{intPoint, intPoint + lightDir};

        for(auto obj : objList)
        {
            if(obj != currObj)
            {
                validInt = obj->TestIntersections(lightRay, interPoint, interNormal, interColor);
            }
            if(validInt)
            {
                break;
            }
        }

        color = m_color;

        if(!validInt)
        {
            const double angle = std::acos(qbVector<double>::dot(lightDir, normal));

            if(angle > 1.5708)
            {
                lightIntensity = 0.0;
                return false;
            }
            else
            {
                lightIntensity = m_intensity * (1.0 - (angle / 1.5708));
                return true;
            }
        } else
        {
            lightIntensity = 0.0;
            return false;
        }

        return true;
    }

}

