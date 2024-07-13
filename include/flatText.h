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

            qbVector<double> GetColor(const qbVector<double>& uv) override;
            void SetColor(const qbVector<double>& color);

        private:
            qbVector<double> color{4};

    };
}





#endif //FLATTEXT_H
