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

    qbVector3<double> SimpleRefractive::ComputeColor(const std::vector<std::shared_ptr<Object>>& objectList,
        const std::vector<std::shared_ptr<Light>>& lightList, const std::shared_ptr<Object>& currentObject,
        const qbVector3<double>& intPoint, const qbVector3<double>& localNormal, const Ray& cameraRay)
    {
        qbVector3<double> refCol;
        qbVector3<double> matCol;
        qbVector3<double> traCol;
        qbVector3<double> spcCol;
        qbVector3<double> difCol;

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

    qbVector3<double> SimpleRefractive::ComputeTranslucency(const std::vector<std::shared_ptr<Object>>& objectList,
        const std::vector<std::shared_ptr<Light>>& lightList, const std::shared_ptr<Object>& currentObject,
        const qbVector3<double>& intPoint, const qbVector3<double>& localNormal, const Ray& cameraRay)
    {
        qbVector3<double> trnCol;

        qbVector3<double> p = cameraRay.m_lab;
        p.Normalize();
        qbVector3<double> tempNormal = localNormal;
        double r = 1.0 / refractiveIndex;
        double c = -qbVector3<double>::dot(tempNormal, p);
        if(c < 0.0)
        {
            tempNormal = tempNormal * -1.0;
            c = -qbVector3<double>::dot(tempNormal, p);
        }

        qbVector3<double> refracted1 = r*p + (r*c - sqrtf(1.0-pow(r,2.0) * (1.0-pow(c,2.0)))) * tempNormal;

        Ray ref1Ray{intPoint + (refracted1 * 0.0001), intPoint + refracted1};

        std::shared_ptr<Object> obj;

        Data::HitData closestHitData;
        Data::HitData hitData;

        bool secondInt = currentObject -> TestIntersections(ref1Ray, hitData);
        bool intFound = false;
        Ray finalRay;

        if(secondInt)
        {
            qbVector3<double> p2 = ref1Ray.m_lab;
            p2.Normalize();
            qbVector3<double> tempNormal2 = hitData.localNormal;
            double r2 = refractiveIndex;
            double c2 = -qbVector3<double>::dot(tempNormal2, p2);
            if(c2 < 0.0)
            {
                tempNormal2 = tempNormal2 * -1.0;
                c2 = -qbVector3<double>::dot(tempNormal2, p2);
            }

            qbVector3<double> refracted2 = r2*p2 + (r2*c2 - sqrtf(1.0-pow(r2,2.0) * (1.0-pow(c2,2.0)))) * tempNormal2;

            Ray ref2Ray{hitData.intPoint + (refracted2 * 0.0001), hitData.intPoint + refracted2};
            intFound = CastRay(ref2Ray, objectList, currentObject, obj, closestHitData);

            finalRay = ref2Ray;
        } else
        {
            intFound = CastRay(ref1Ray, objectList, currentObject, obj, closestHitData);
            finalRay = ref1Ray;
        }

        qbVector3<double> matColor;

        if(intFound)
        {
            if(obj->m_hasMaterial)
            {
                matColor = obj -> m_pMaterial -> ComputeColor(objectList, lightList, obj, closestHitData.intPoint, closestHitData.localNormal, finalRay);
            } else
            {
                matColor = ComputeDiffuseColor(objectList, lightList, obj, closestHitData.intPoint, closestHitData.localNormal, obj->baseColor);
            }
        }

        trnCol = matColor;
        return trnCol;
    }

    qbVector3<double> SimpleRefractive::ComputeSpecular(const std::vector<std::shared_ptr<Object>>& objectList,
        const std::vector<std::shared_ptr<Light>>& lightList, const qbVector3<double>& intPoint,
        const qbVector3<double>& localNormal, const Ray& cameraRay)
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