//
// Created by Aman's Laptop on 11-07-2024.
//

#ifndef SIMPLEMATERIAL_H
#define SIMPLEMATERIAL_H
#include "material.h"


namespace qbRT
{
    class SimpleMaterial : public Material{
        public:
            SimpleMaterial();
            ~SimpleMaterial() override;

            qbVector3<double> ComputeColor(	const std::vector<std::shared_ptr<Object>> &objectList,
                const std::vector<std::shared_ptr<Light>> &lightList,
                const std::shared_ptr<Object> &currentObject,
                const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
                const Ray &cameraRay) override;

            qbVector3<double> ComputeSpecular(	const std::vector<std::shared_ptr<Object>> &objectList,
                const std::vector<std::shared_ptr<Light>> &lightList,
                const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
                const Ray &cameraRay);

        public:
            qbVector3<double> baseColor {std::vector {1.0, 1.0, 1.0}};
            double reflectivity = 0.0;
            double shine = 0.0;


    };
}



#endif //SIMPLEMATERIAL_H
