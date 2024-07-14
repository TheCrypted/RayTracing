//
// Created by Aman's Laptop on 14-07-2024.
//

#ifndef SIMPLEREFRACTIVE_H
#define SIMPLEREFRACTIVE_H
#include "material.h"


namespace qbRT
{
    class SimpleRefractive : public Material {
        public:
            SimpleRefractive();
            ~SimpleRefractive() override;

            qbVector<double> ComputeColor(const std::vector<std::shared_ptr<Object>>& objectList,
                const std::vector<std::shared_ptr<Light>>& lightList, const std::shared_ptr<Object>& currentObject,
                const qbVector<double>& intPoint, const qbVector<double>& localNormal, const Ray& cameraRay) override;

            qbVector<double> ComputeSpecular(const std::vector<std::shared_ptr<Object>> &objectList,
                const std::vector<std::shared_ptr<Light>> &lightList,
                const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                const Ray &cameraRay);

            qbVector<double> ComputeTranslucency(const std::vector<std::shared_ptr<Object>>& objectList,
                    const std::vector<std::shared_ptr<Light>>& lightList, const std::shared_ptr<Object>& currentObject,
                    const qbVector<double>& intPoint, const qbVector<double>& localNormal, const Ray& cameraRay);

        public:
            qbVector<double> baseColor{std::vector{1.0, 0.0, 1.0}};
            double reflectivity = 0.0;
            double shine = 0.0;
            double refractiveIndex = 1.0;
            double translucency = 0.0;

    };
}



#endif //SIMPLEREFRACTIVE_H
