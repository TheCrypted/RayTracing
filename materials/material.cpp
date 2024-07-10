//
// Created by Aman's Laptop on 10-07-2024.
//

#include "../include/material.h"

namespace qbRT
{
    Material::Material()
    {

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
        const std::vector<std::shared_ptr<Light>> &lightList,
        const std::shared_ptr<Object> &currentObject,
        const qbVector<double> &intPoint, const qbVector<double> &localNormal,
        const qbVector<double> &baseColor)
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


}