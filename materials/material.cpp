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
        } else
        {
            for (int i = 0; i < 3; ++i)
            {
                diffuseColor.SetElement(i, baseColor.GetElement(i) * ambientColor.GetElement(i) * ambientIntensity);
            }
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
        Data::HitData closestHitData;


        bool intersectionFound = CastRay(reflectionRay, objectList, currentObject, closestObj, closestHitData);

        qbVector<double> matColor{3};
        if((intersectionFound) && (reflectionRayCount < maxReflectionDepth))
        {
            reflectionRayCount++;
            if(closestObj -> m_hasMaterial)
            {
                matColor = closestObj -> m_pMaterial -> ComputeColor(objectList, lightList, closestObj, closestHitData.intPoint, closestHitData.localNormal, reflectionRay);
            } else
            {
                matColor = ComputeDiffuseColor(objectList, lightList, closestObj, closestHitData.intPoint, closestHitData.localNormal, closestObj -> baseColor);
            }
        }
        reflectionColor = matColor;
        return reflectionColor;
    }

    bool Material::CastRay(const Ray& castRay, const std::vector<std::shared_ptr<Object>>& objectList,
        const std::shared_ptr<Object>& thisObject, std::shared_ptr<Object>& closestObject,
        Data::HitData& closestHitData)
    {
        Data::HitData hitData;

        double minDist = 1e6;
        bool intersectionFound = false;

        for(auto object : objectList)
        {
            if(object != thisObject)
            {
                bool validInt = object -> TestIntersections(castRay, hitData);
                if(validInt)
                {
                    double dist = (hitData.intPoint - castRay.m_point1).norm();
                    intersectionFound = true;
                    if(dist < minDist)
                    {
                        minDist = dist;
                        closestObject = object;
                        closestHitData = hitData;
                    }
                }
            }
        }
        return intersectionFound;
    }

    void Material::AssignTexture(const std::shared_ptr<TextureBase::Texture>& texture)
    {
        textureList.push_back(texture);
        hasTexture = true;
    }

    void Material::AssignNormalMap(const std::shared_ptr<Normal::NormalBase>& normMap)
    {
        normMapList.push_back(normMap);
        hasNormMap = true;
    }

    qbVector<double> Material::GetTextureColor(const qbVector<double>& coords)
    {
        qbVector<double> res{4};

        if(textureList.size() > 1)
        {
            res = textureList[0] -> GetColor(coords);
            for (int i = 1; i < textureList.size(); ++i)
            {
                BlendColors(res, textureList[i] -> GetColor(coords));
            }
        } else
        {
            res = textureList[0] -> GetColor(coords);
        }

        return res;
    }

    qbVector<double> Material::PerturbNormal(const qbVector<double>& normal, const qbVector<double>& uvCoords)
    {
        qbVector<double> newNorm = normal;

        for (auto & i : normMapList)
        {
            newNorm = i -> CompPerturbation(newNorm, uvCoords);
        }

        return newNorm;
    }


    void Material::BlendColors(qbVector<double>& color1, const qbVector<double>& color2)
    {
        color1 = (color2 * color2.GetElement(3)) + (color1 * (1.0 - color2.GetElement(3)));
    }



}