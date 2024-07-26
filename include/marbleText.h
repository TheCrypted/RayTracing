//
// Created by Aman's Laptop on 26-07-2024.
//

#ifndef MARBLETEXT_H
#define MARBLETEXT_H

#include "gradNoise.h"
#include "colormap.h"
#include "texture.h"
#include <algorithm>


namespace qbRT::TextureBase
{
    class MarbleText : public Texture{
        public:
            MarbleText();
            ~MarbleText() override;

            qbVector<double> GetColor(const qbVector<double>& uv) override;

            void SetColor(const std::shared_ptr<Colormap>& in_colorMap);
            void SetAmplitude(double in_amplitude1, double in_amplitude2);
            void SetScale(int in_scale1, int in_scale2);
            void SetMinMax(double in_min, double in_max);
            void SetSin(double in_amp, double in_freq);

        public:
            std::shared_ptr<Colormap> colorMap;
            std::vector<Noise::GradNoise> noiseGenList;
            bool hasColorMap = false;

            double amplitude1 = 8.0;
            double amplitude2 = 8.0;

            int scale1 = 4;
            int scale2 = 40;

            double maxVal = 1.0;
            double minVal = -1.0;

            double sinAmp = 0.25;
            double sinFreq = 4.0;
    };
}



#endif //MARBLETEXT_H
