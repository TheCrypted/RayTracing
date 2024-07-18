//
// Created by Aman's Laptop on 18-07-2024.
//

#ifndef GRADIENT_H
#define GRADIENT_H
#include "colormap.h"
#include "texture.h"


namespace qbRT::TextureBase
{
    class Gradient : public Texture {
        public:
            Gradient();
            ~Gradient() override;

            qbVector<double> GetColor(const qbVector<double>& coords) override;
            void SetStop(double stop, const qbVector<double> &color);

        private:
            Colormap colormap;
    };
}



#endif //GRADIENT_H
