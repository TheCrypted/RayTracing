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

            qbVector4<double> GetColor(const qbVector2<double>& coords) override;
            double GetValue(const qbVector2<double>& coords) override;
            void SetStop(double stop, const qbVector4<double> &color);

        private:
            Colormap colormap;
    };
}



#endif //GRADIENT_H
