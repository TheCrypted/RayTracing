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

    qbVector3<double> SimpleMaterial::ComputeColor(	const std::vector<std::shared_ptr<Object>> &objectList,
        const std::vector<std::shared_ptr<Light>> &lightList,
        const std::shared_ptr<Object> &currentObject,
        const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
        const Ray &cameraRay)
    {
        qbVector3<double> difColor;
        qbVector3<double> matColor;
        qbVector3<double> refColor;
        qbVector3<double> specColor;

        qbVector3<double> normCopy = localNormal;

        if(hasNormMap)
        {
            normCopy = PerturbNormal(normCopy, currentObject -> uvCoords);
        }

        locNorm = normCopy;

        if(!hasTexture)
        {
            difColor = ComputeSDColor(objectList, lightList, currentObject, intPoint, normCopy, baseColor, cameraRay);
        } else
        {
            qbVector3<double> textureCol = GetTextureColor(currentObject -> uvCoords);

            difColor = ComputeSDColor(objectList, lightList, currentObject, intPoint, normCopy,
                textureCol, cameraRay);
        }

        if(reflectivity > 0.0)
            refColor = ComputeReflectionColor(objectList, lightList, currentObject, intPoint, normCopy, cameraRay);

        matColor = (refColor * reflectivity) + (difColor * (1.0 - reflectivity));


        return matColor;
    }

    qbVector3<double> SimpleMaterial::ComputeSpecular(	const std::vector<std::shared_ptr<Object>> &objectList,
        const std::vector<std::shared_ptr<Light>> &lightList,
        const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
        const Ray &cameraRay)
    {
        qbVector3<double> resColor;
        double red = 0.0;
        double green = 0.0;
        double blue = 0.0;

        for(auto light : lightList)
        {
            double intensity = 0.0;

            qbVector3<double> lightDir = (light->m_position - intPoint).Normalized();
            qbVector3<double> startPoint = intPoint + lightDir * 0.0001;

            Ray lightRay = Ray(startPoint, startPoint + lightDir);

            Data::HitData hitData;
            bool validInt = false;

            for(auto object : objectList)
            {
                validInt = object -> TestIntersections(lightRay, hitData);
                if(validInt)
                {
                    break;
                }
            }

            if(!validInt)
            {
                auto r = lightRay.m_lab - (2 * qbVector3<double>::dot(lightRay.m_lab, localNormal) * localNormal);
                r.Normalize();

                qbVector3<double> v = cameraRay.m_lab;
                v.Normalize();

                double dotProd = qbVector3<double>::dot(r, v);

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