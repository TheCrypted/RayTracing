//
// Created by Aman's Laptop on 13-07-2024.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "qbLinAlg/qbMatrix.h"
#include "qbLinAlg/qbVector.h"
#include "ray.h"
#include "qbLinAlg/qbVector2.hpp"
#include "qbLinAlg/qbMatrix33.hpp"


namespace qbRT::TextureBase
{
    class Texture {
        public:
            Texture();
            virtual ~Texture();

            virtual qbVector4<double> GetColor(const qbVector2<double> &coords);
            virtual double GetValue(const qbVector2<double> &coords);
            void SetTransform(const qbVector2<double> &translation, const double &rotation,
                const qbVector2<double> &scale);

            qbVector2<double> ApplyTransform(const qbVector2<double> &vec);

            static qbVector3<double> BlendColors(const std::vector<qbVector3<double>> &colors);

        private:

        private:
            qbMatrix33<double> m_transform {std::vector{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};
    };
}




#endif //TEXTURE_H
