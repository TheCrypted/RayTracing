//
// Created by Aman's Laptop on 13-07-2024.
//

#ifndef CHECKERTEXT_H
#define CHECKERTEXT_H

#include "texture.h"
#include "flatText.h"


namespace qbRT::TextureBase
{
    class Checker : public Texture{
        public:
            Checker();
            ~Checker() override;

            qbVector4<double> GetColor(const qbVector2<double>& uv) override;
            void SetColor(const qbVector4<double>& color1, const qbVector4<double>& color2);
            void SetColor(const std::shared_ptr<Texture>& in_color1, const std::shared_ptr<Texture>& in_color2);

        private:
            std::shared_ptr<Texture> color1;
            std::shared_ptr<Texture> color2;
    };
}




#endif //CHECKERTEXT_H
