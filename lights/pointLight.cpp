//
// Created by Aman's Laptop on 07-07-2024.
//

#include "../include/pointLight.h"

#include <complex>

namespace qbRT
{
    PointLight::PointLight()
    {
        m_color = qbVector3{1.0, 1.0, 1.0};
        m_intensity = 1.0;
    }

    PointLight::~PointLight()
    = default;

    bool PointLight::CalculateLighting(const qbVector3<double> &intPoint, const qbVector3<double> &normal,
                const std::vector<std::shared_ptr<Object>> &objList, const std::shared_ptr<Object> &currObj,
                qbVector3<double> &color, double &lightIntensity)
    {
        const qbVector3<double> lightDir = (m_position - intPoint).Normalized();
        double lightDist = (m_position - intPoint).norm();

        Data::HitData hitData;
        bool validInt = false;
        Ray lightRay{intPoint, intPoint + lightDir};

        for(auto obj : objList)
        {
            if(obj != currObj)
            {
                validInt = obj->TestIntersections(lightRay, hitData);

                if(validInt)
                {
                    double dist = (hitData.intPoint - intPoint).norm();
                    if(dist > lightDist)
                    {
                        validInt = false;
                    }
                }
            }
            if(validInt)
            {
                break;
            }
        }

        color = m_color;

        if(!validInt)
        {
            const double angle = std::acos(qbVector3<double>::dot(lightDir, normal));

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

