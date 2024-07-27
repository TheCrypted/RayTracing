//
// Created by Aman's Laptop on 13-07-2024.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "qbLinAlg/qbMatrix.h"
#include "qbLinAlg/qbVector.h"
#include "ray.h"



namespace qbRT::TextureBase
{
    class Texture {
        public:
            Texture();
            virtual ~Texture();

            virtual qbVector<double> GetColor(const qbVector<double> &coords);
            virtual double GetValue(const qbVector<double> &coords);
            void SetTransform(const qbVector<double> &translation, const double &rotation,
                const qbVector<double> &scale);

            qbVector<double> ApplyTransform(const qbVector<double> &vec);

            static qbVector<double> BlendColors(const std::vector<qbVector<double>> &colors);

        private:

        private:
            qbMatrix2<double> m_transform {3, 3, std::vector<double>{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};
    };
}




#endif //TEXTURE_H
