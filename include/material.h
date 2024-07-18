//
// Created by Aman's Laptop on 10-07-2024.
//

#ifndef MATERIAL_H
#define MATERIAL_H


#include <memory>
#include "object.h"
#include "light.h"
#include "qbLinAlg/qbVector.h"
#include "ray.h"
#include "texture.h"


namespace qbRT
{
    class Material {
        public:
			Material();
			virtual ~Material();

			virtual qbVector<double> ComputeColor(const std::vector<std::shared_ptr<Object>> &objectList,
				const std::vector<std::shared_ptr<Light>> &lightList,
				const std::shared_ptr<Object> &currentObject,
				const qbVector<double> &intPoint, const qbVector<double> &localNormal,
				const Ray &cameraRay);

			static qbVector<double> ComputeDiffuseColor(const std::vector<std::shared_ptr<Object>> &objectList,
				const std::vector<std::shared_ptr<Light>> &lightList,
				const std::shared_ptr<Object> &currentObject,
				const qbVector<double> &intPoint, const qbVector<double> &localNormal,
				const qbVector<double> &baseColor);

			qbVector<double> ComputeReflectionColor(const std::vector<std::shared_ptr<Object>> &objectList,
				const std::vector<std::shared_ptr<Light>> &lightList,
				const std::shared_ptr<Object> &currentObject,
				const qbVector<double> &intPoint, const qbVector<double> &localNormal,
				const Ray &cameraRay);

			bool CastRay(const Ray &castRay, const std::vector<std::shared_ptr<Object>> &objectList,
				const std::shared_ptr<Object> &thisObject,
				std::shared_ptr<Object> &closestObject,
				qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
				qbVector<double> &closestLocalColor);

			void AssignTexture(const std::shared_ptr<TextureBase::Texture> &texture);

			qbVector<double> GetTextureColor(const qbVector<double> &coords);

			void BlendColors(qbVector<double>& color1, const qbVector<double>& color2);

		public:
			inline static int maxReflectionDepth;
			inline static int reflectionRayCount;
			inline static qbVector<double> ambientColor{std::vector{1.0, 1.0, 1.0}};
			inline static double ambientIntensity = 0.2;
			std::vector<std::shared_ptr<TextureBase::Texture>> textureList;
			bool hasTexture = false;

		private:

    };
}



#endif //MATERIAL_H
