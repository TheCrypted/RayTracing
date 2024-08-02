//
// Created by Aman's Laptop on 26-07-2024.
//

#ifndef NORMAL_H
#define NORMAL_H

#include <memory>
#include "ray.h"
#include "texture.h"
#include "qbLinAlg/qbMatrix.h"
#include "qbLinAlg/qbVector.h"
#include "qbLinAlg/qbVector2.hpp"
#include "qbLinAlg/qbMatrix33.hpp"


namespace qbRT::Normal
{
    class NormalBase {
        public:
            NormalBase();
            virtual ~NormalBase();

            virtual qbVector3<double> CompPerturbation(const qbVector3<double>& normal, const qbVector2<double>& uvCoords);
            qbVector3<double> PerturbNormal(const qbVector3<double>& normal, const qbVector3<double>& perturbation);
            qbVector2<double> TextureDiff(const std::shared_ptr<TextureBase::Texture>& inputTexture, const qbVector2<double>& uvCoords);

            void SetAmplitude(double in_amp);
            void SetTransform(const qbVector3<double>& translation, const double rotation, const qbVector3<double>& scale);
            qbVector2<double> ApplyTransform(const qbVector2<double>& inputVec);

        public:
            double amplitude = 1.0;

        private:
            qbMatrix33<double> transMat{std::vector{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};

    };
}



#endif //NORMAL_H
