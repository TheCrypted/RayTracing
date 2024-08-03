//
// Created by Aman's Laptop on 26-07-2024.
//

#include "../include/basicNoiseText.h"

#include <algorithm>

namespace qbRT::TextureBase
{
    BasicNoise::BasicNoise()
    {
        noiseGen.SetGrid(scale);
    }

    BasicNoise::~BasicNoise()
    = default;

    qbVector4<double> BasicNoise::GetColor(const qbVector2<double>& uv)
    {
        qbVector2<double> in_coord = uv;
        qbVector2<double> backCoord = ApplyTransform(uv);
        double u = backCoord.GetElement(0);
        double v = backCoord.GetElement(1);

        qbVector4<double> locColor;

        if(!hasColorMap) locColor = qbVector4{1.0, 0.0, 1.0, 1.0};
        else
        {
            double mapPos = std::clamp(noiseGen.GetValue(u, v) * amplitude, 0.0, 1.0);
            locColor = colorMap->GetColor(mapPos);
        }
        return locColor;
    }

    void BasicNoise::SetColor(const std::shared_ptr<Colormap>& in_colorMap)
    {
        colorMap = in_colorMap;
        hasColorMap = true;
    }

    void BasicNoise::SetAmplitude(double in_amplitude)
    {
        amplitude = in_amplitude;
    }

    void BasicNoise::SetScale(int in_scale)
    {
        scale = in_scale;
        noiseGen.SetGrid(scale);
    }

}
