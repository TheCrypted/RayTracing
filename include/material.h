//
// Created by Aman's Laptop on 10-07-2024.
//

#ifndef MATERIAL_H
#define MATERIAL_H


#include <memory>

#include "normal.h"
#include "object.h"
#include "light.h"
#include "qbLinAlg/qbVector3.hpp"
#include "ray.h"
#include "texture.h"
#include "qbLinAlg/qbVector2.hpp"


namespace qbRT
{
    class Material {
        public:
			Material();
			virtual ~Material();

			virtual qbVector3<double> ComputeColor(const std::vector<std::shared_ptr<Object>> &objectList,
				const std::vector<std::shared_ptr<Light>> &lightList,
				const std::shared_ptr<Object> &currentObject,
				const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
				const Ray &cameraRay);

			static qbVector3<double> ComputeDiffuseColor(const std::vector<std::shared_ptr<Object>> &objectList,
				const std::vector<std::shared_ptr<Light>> &lightList,
				const std::shared_ptr<Object> &currentObject,
				const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
				const qbVector3<double> &baseColor);

			qbVector3<double> ComputeReflectionColor(const std::vector<std::shared_ptr<Object>> &objectList,
				const std::vector<std::shared_ptr<Light>> &lightList,
				const std::shared_ptr<Object> &currentObject,
				const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
				const Ray &cameraRay);

			qbVector3<double> ComputeSDColor(const std::vector<std::shared_ptr<Object>> &objectList,
				const std::vector<std::shared_ptr<Light>> &lightList,
				const std::shared_ptr<Object> &currentObject,
				const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
				const qbVector3<double> &baseColor, const Ray& camRay);

			bool CastRay(const Ray &castRay, const std::vector<std::shared_ptr<Object>> &objectList,
				const std::shared_ptr<Object> &thisObject,
				std::shared_ptr<Object> &closestObject,
				Data::HitData &hitData);

			void AssignTexture(const std::shared_ptr<TextureBase::Texture> &texture);

			void AssignNormalMap(const std::shared_ptr<Normal::NormalBase>& normMap);

			qbVector3<double> GetTextureColor(const qbVector2<double> &coords);

			qbVector3<double> PerturbNormal(const qbVector3<double> &normal, const qbVector2<double> &uvCoords);

			void BlendColors(qbVector4<double>& color1, const qbVector4<double>& color2);

		public:
			inline static int maxReflectionDepth;
			inline static int reflectionRayCount;
			inline static qbVector3<double> ambientColor{std::vector{1.0, 1.0, 1.0}};
			inline static double ambientIntensity = 0.2;
			std::vector<std::shared_ptr<TextureBase::Texture>> textureList;
			std::vector<std::shared_ptr<Normal::NormalBase>> normMapList;
			bool hasTexture = false;
			bool hasNormMap = false;
			qbVector3<double> locNorm;

			double specular = 0.0;
			double shine = 0.0;

		private:

    };
}



#endif //MATERIAL_H
