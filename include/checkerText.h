//
// Created by Aman's Laptop on 13-07-2024.
//

#ifndef CHECKERTEXT_H
#define CHECKERTEXT_H
#include "texture.h"


namespace qbRT::TextureBase
{
    class Checker : public Texture{
        public:
            Checker();
            ~Checker() override;

            qbVector<double> GetColor(const qbVector<double>& uv) override;
            void SetColor(const qbVector<double>& color1, const qbVector<double>& color2);

        private:
            qbVector<double> color1{4};
            qbVector<double> color2{4};
    };
}




#endif //CHECKERTEXT_H
