//
// Created by Aman's Laptop on 13-07-2024.
//

#ifndef FLATTEXT_H
#define FLATTEXT_H
#include "texture.h"


namespace qbRT::TextureBase
{
    class Flat : public Texture {
        public:
            Flat();
            ~Flat() override;

            qbVector4<double> GetColor(const qbVector2<double>& uv) override;
            void SetColor(const qbVector4<double>& color);

        private:
            qbVector4<double> color;

    };
}





#endif //FLATTEXT_H
