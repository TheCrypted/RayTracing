//
// Created by Aman's Laptop on 14-07-2024.
//

#include "../include/simpleRefractive.h"

namespace qbRT
{
    SimpleRefractive::SimpleRefractive()
    = default;

    SimpleRefractive::~SimpleRefractive()
    = default;

    qbVector<double> SimpleRefractive::ComputeColor(const std::vector<std::shared_ptr<Object>>& objectList,
        const std::vector<std::shared_ptr<Light>>& lightList, const std::shared_ptr<Object>& currentObject,
        const qbVector<double>& intPoint, const qbVector<double>& localNormal, const Ray& cameraRay)
    {
        qbVector<double> refCol{3};
        qbVector<double> matCol{3};
        qbVector<double> traCol{3};
        qbVector<double> spcCol{3};
        qbVector<double> difCol{3};

        if(hasTexture)
        {
            difCol = ComputeDiffuseColor(objectList, lightList, currentObject, intPoint, localNormal,
                textureList.at(0)->GetColor(currentObject -> uvCoords));
        } else
        {
            difCol = ComputeDiffuseColor(objectList, lightList, currentObject, intPoint, localNormal, baseColor);
        }

        if(reflectivity > 0.0)
        {
            refCol = ComputeReflectionColor(objectList, lightList, currentObject, intPoint, localNormal, cameraRay);
        }

        matCol = (refCol * reflectivity) + (difCol * (1 - reflectivity));

        if(translucency > 0.0)
        {
            traCol = ComputeTranslucency(objectList, lightList, currentObject, intPoint, localNormal, cameraRay);
        }

        matCol = (traCol * translucency) + (matCol * (1 - translucency));

        if(shine > 0.0)
        {
            spcCol = ComputeSpecular(objectList, lightList, intPoint, localNormal, cameraRay);
        }

        matCol = matCol + spcCol;

        return matCol;
    }

    qbVector<double> SimpleRefractive::ComputeTranslucency(const std::vector<std::shared_ptr<Object>>& objectList,
        const std::vector<std::shared_ptr<Light>>& lightList, const std::shared_ptr<Object>& currentObject,
        const qbVector<double>& intPoint, const qbVector<double>& localNormal, const Ray& cameraRay)
    {
        qbVector<double> trnCol{3};

        qbVector<double> p = cameraRay.m_lab;
        p.Normalize();
        qbVector<double> tempNormal = localNormal;
        double r = 1.0 / refractiveIndex;
        double c = -qbVector<double>::dot(tempNormal, p);
        if(c < 0.0)
        {
            tempNormal = tempNormal * -1.0;
            c = -qbVector<double>::dot(tempNormal, p);
        }

        qbVector<double> refracted1 = r*p + (r*c - sqrtf(1.0-pow(r,2.0) * (1.0-pow(c,2.0)))) * tempNormal;

        Ray ref1Ray{intPoint + (refracted1 * 0.0001), refracted1};

        std::shared_ptr<Object> obj;
        qbVector<double> closestIntPoint{3};
        qbVector<double> closestNormal{3};
        qbVector<double> closestColor{3};

        qbVector<double> newIntPoint{3};
        qbVector<double> newNormal{3};
        qbVector<double> newColor{3};

        bool secondInt = currentObject -> TestIntersections(ref1Ray, newIntPoint, newNormal, newColor);
        bool intFound = false;
        Ray finalRay;

        if(secondInt)
        {
            qbVector<double> p2 = ref1Ray.m_lab;
            p2.Normalize();
            qbVector<double> tempNormal2 = newNormal;
            double r2 = refractiveIndex;
            double c2 = -qbVector<double>::dot(tempNormal2, p2);
            if(c2 < 0.0)
            {
                tempNormal2 = tempNormal2 * -1.0;
                c2 = -qbVector<double>::dot(tempNormal2, p2);
            }

            qbVector<double> refracted2 = r2*p2 + (r2*c2 - sqrtf(1.0-pow(r2,2.0) * (1.0-pow(c2,2.0)))) * tempNormal2;

            Ray ref2Ray{intPoint + (refracted2 * 0.0001), refracted2};
            intFound = CastRay(ref2Ray, objectList, currentObject, obj, closestIntPoint, closestNormal, closestColor);

            finalRay = ref2Ray;
        } else
        {
            intFound = CastRay(ref1Ray, objectList, currentObject, obj, closestIntPoint, closestNormal, closestColor);
            finalRay = ref1Ray;
        }

        qbVector<double> matColor{3};

        if(intFound)
        {
            if(obj->m_hasMaterial)
            {
                matColor = obj -> m_pMaterial -> ComputeColor(objectList, lightList, obj, closestIntPoint, closestNormal, finalRay);
            } else
            {
                matColor = Material::ComputeDiffuseColor(objectList, lightList, obj, closestIntPoint, closestNormal, obj->baseColor);
            }
        }

        trnCol = matColor;
        return trnCol;
    }

    qbVector<double> SimpleRefractive::ComputeSpecular(const std::vector<std::shared_ptr<Object>>& objectList,
        const std::vector<std::shared_ptr<Light>>& lightList, const qbVector<double>& intPoint,
        const qbVector<double>& localNormal, const Ray& cameraRay)
    {
        qbVector<double> resColor{3};
        double red = 0.0;
        double green = 0.0;
        double blue = 0.0;

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