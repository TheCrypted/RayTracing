//
// Created by Aman's Laptop on 10-07-2024.
//

#include "../include/material.h"

namespace qbRT
{
    Material::Material()
    {
        maxReflectionDepth = 3;
        reflectionRayCount = 0;
    }

    Material::~Material()
    {

    }

    qbVector<double> Material::ComputeColor(	const std::vector<std::shared_ptr<Object>> &objectList,
        const std::vector<std::shared_ptr<Light>> &lightList,
        const std::shared_ptr<Object> &currentObject,
        const qbVector<double> &intPoint, const qbVector<double> &localNormal,
        const Ray &cameraRay)
    {
        qbVector<double> matColor	{3};
        return matColor;
    }

    qbVector<double> Material::ComputeDiffuseColor(	const std::vector<std::shared_ptr<Object>> &objectList,
        const std::vector<std::shared_ptr<Light>> &lightList, const std::shared_ptr<Object> &currentObject,
        const qbVector<double> &intPoint, const qbVector<double> &localNormal, const qbVector<double> &baseColor)
    {
        qbVector<double> diffuseColor	{3};
        double intensity;
        qbVector<double> color {3};
        double red = 0.0;
        double green = 0.0;
        double blue = 0.0;
        bool validIllum = false;
        bool illumFound = false;
        for (auto currentLight : lightList)
        {
            validIllum = currentLight -> CalculateLighting(intPoint, localNormal, objectList, currentObject, color, intensity);
            if (validIllum)
            {
                illumFound = true;
                red += color.GetElement(0) * intensity;
                green += color.GetElement(1) * intensity;
                blue += color.GetElement(2) * intensity;
            }
        }

        if (illumFound)
        {
            diffuseColor.SetElement(0, red * baseColor.GetElement(0));
            diffuseColor.SetElement(1, green * baseColor.GetElement(1));
            diffuseColor.SetElement(2, blue * baseColor.GetElement(2));
        }
        return diffuseColor;
    }

    qbVector<double> Material::ComputeReflectionColor(const std::vector<std::shared_ptr<Object>> &objectList,
        const std::vector<std::shared_ptr<Light>> &lightList, const std::shared_ptr<Object> &currentObject,
        const qbVector<double> &intPoint, const qbVector<double> &localNormal, const Ray &cameraRay)
    {
        qbVector<double> reflectionColor{3};

        qbVector<double> d = cameraRay.m_lab;
        qbVector<double> reflection_vector = d - (2 * qbVector<double>::dot(d, localNormal) * localNormal);

        Ray reflectionRay = Ray(intPoint, intPoint + reflection_vector);

        std::shared_ptr<Object> closestObj;
        qbVector<double> closestIntPoint{3};
        qbVector<double> closestNormal{3};
        qbVector<double> closestColor{3};

        bool intersectionFound = CastRay(reflectionRay, objectList, currentObject, closestObj, closestIntPoint, closestNormal, closestColor);

        qbVector<double> matColor{3};
        if((intersectionFound) && (reflectionRayCount < maxReflectionDepth))
        {
            reflectionRayCount++;
            if(closestObj -> m_hasMaterial)
            {
                matColor = closestObj -> m_pMaterial -> ComputeColor(objectList, lightList, closestObj, closestIntPoint, closestNormal, reflectionRay);
            } else
            {
                matColor = ComputeDiffuseColor(objectList, lightList, closestObj, closestIntPoint, closestNormal, closestObj -> baseColor);
            }
        }
        reflectionColor = matColor;
        return reflectionColor;
    }

    bool Material::CastRay(const Ray& castRay, const std::vector<std::shared_ptr<Object>>& objectList,
        const std::shared_ptr<Object>& thisObject, std::shared_ptr<Object>& closestObject,
        qbVector<double>& closestIntPoint, qbVector<double>& closestLocalNormal, qbVector<double>& closestLocalColor)
    {
        qbVector<double> intPoint{3};
        qbVector<double> localNormal{3};
        qbVector<double> localColor{3};

        double minDist = 1e6;
        bool intersectionFound = false;

        for(auto object : objectList)
        {
            if(object != thisObject)
            {
                bool validInt = object -> TestIntersections(castRay, intPoint, localNormal, localColor);
                if(validInt)
                {
                    double dist = (intPoint - castRay.m_point1).norm();
                    intersectionFound = true;
                    if(dist < minDist)
                    {
                        minDist = dist;
                        closestObject = object;
                        closestIntPoint = intPoint;
                        closestLocalNormal = localNormal;
                        closestLocalColor = localColor;
                    }
                }
            }
        }
        return intersectionFound;
    }



}