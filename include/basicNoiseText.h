//
// Created by Aman's Laptop on 26-07-2024.
//

#ifndef BASICNOISETEXTURE_H
#define BASICNOISETEXTURE_H
#include "colormap.h"
#include "texture.h"
#include "valNoise.h"


namespace qbRT::TextureBase
{
    class BasicNoise : public Texture{
        public:
            BasicNoise();
            ~BasicNoise() override;

            qbVector4<double> GetColor(const qbVector2<double>& uv) override;

            void SetColor(const std::shared_ptr<Colormap>& in_colorMap);
            void SetAmplitude(double in_amplitude);
            void SetScale(int in_scale);

        public:
            std::shared_ptr<Colormap> colorMap;
            Noise::ValNoise noiseGen;
            bool hasColorMap = false;
            double amplitude = 0.0;
            int scale = 3;
    };
}



#endif //BASICNOISETEXTURE_H
