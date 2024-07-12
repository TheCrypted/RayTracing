//
// Created by Aman's Laptop on 11-07-2024.
//

#include "../include/simpleMaterial.h"

namespace qbRT
{
    SimpleMaterial::SimpleMaterial()
    = default;

    SimpleMaterial::~SimpleMaterial()
    = default;

    qbVector<double> SimpleMaterial::ComputeColor(	const std::vector<std::shared_ptr<Object>> &objectList,
        const std::vector<std::shared_ptr<Light>> &lightList,
        const std::shared_ptr<Object> &currentObject,
        const qbVector<double> &intPoint, const qbVector<double> &localNormal,
        const Ray &cameraRay)
    {
        qbVector<double> matColor{3};
        qbVector<double> refColor{3};
        qbVector<double> specColor{3};

        qbVector<double> difColor = ComputeDiffuseColor(objectList, lightList, currentObject, intPoint, localNormal, baseColor);

        if(reflectivity > 0.0)
            refColor = ComputeReflectionColor(objectList, lightList, currentObject, intPoint, localNormal, cameraRay);

        matColor = (refColor * reflectivity) + (difColor * (1.0 - reflectivity));

        if(shine > 0.0)
            specColor = ComputeSpecular(objectList, lightList, intPoint, localNormal, cameraRay);

        matColor = matColor + specColor;

        return matColor;
    }

    qbVector<double> SimpleMaterial::ComputeSpecular(	const std::vector<std::shared_ptr<Object>> &objectList,
        const std::vector<std::shared_ptr<Light>> &lightList,
        const qbVector<double> &intPoint, const qbVector<double> &localNormal,
        const Ray &cameraRay)
    {
        qbVector<double> resColor{3};
        double red = 0.0;
        double green = 0.0;
        double blue = 0.0;
        double intensity = 0;

        for(auto light : lightList)
        {
            double intensity = 0.0;

            qbVector<double> lightDir = (light->m_position - intPoint).Normalized();
            qbVector<double> startPoint = intPoint + lightDir * 0.0001;

            Ray lightRay = Ray(startPoint, startPoint + lightDir);

            qbVector<double> poi{3};
            qbVector<double> poiNormal{3};
            qbVector<double> poiColor{3};
            bool validInt = false;

            for(auto object : objectList)
            {
                validInt = object -> TestIntersections(lightRay, poi, poiNormal, poiColor);
                if(validInt)
                {
                    break;
                }
            }

            if(!validInt)
            {
                auto r = lightRay.m_lab - (2 * qbVector<double>::dot(lightRay.m_lab, localNormal) * localNormal);
                r.Normalize();

                qbVector<double> v = cameraRay.m_lab;
                v.Normalize();

                double dotProd = qbVector<double>::dot(r, v);

                if(dotProd > 0.0)
                {
                    intensity = reflectivity * pow(dotProd, shine);
                }
            }

            red += intensity * light->m_color.GetElement(0);
            green += intensity * light->m_color.GetElement(1);
            blue += intensity * light->m_color.GetElement(2);
        }

        resColor.SetElement(0, red);
        resColor.SetElement(1, green);
        resColor.SetElement(2, blue);

        return resColor;
    }

}