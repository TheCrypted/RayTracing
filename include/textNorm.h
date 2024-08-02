//
// Created by Aman's Laptop on 27-07-2024.
//

#ifndef TEXTNORM_H
#define TEXTNORM_H
#include "normal.h"


namespace qbRT::Normal
{
    class TextureNormal : public NormalBase {
        public:
            TextureNormal();
            ~TextureNormal() override;

            qbVector3<double> CompPerturbation(const qbVector3<double>& normal, const qbVector2<double>& uvCoords) override;
            void AssignTexture(const std::shared_ptr<TextureBase::Texture>& in_texture);

        public:
            double scale = 1.0;
            bool reverse = false;

        private:
            bool hasTexture = false;
            std::shared_ptr<TextureBase::Texture> texture;

    };
}



#endif //TEXTNORM_H
