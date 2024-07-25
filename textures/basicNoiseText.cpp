//
// Created by Aman's Laptop on 26-07-2024.
//

#include "../include/basicNoiseText.h"

#include <bits/stl_algo.h>

namespace qbRT::TextureBase
{
    BasicNoise::BasicNoise()
    {
        noiseGen.SetGrid(scale);
    }

    BasicNoise::~BasicNoise()
    = default;

    qbVector<double> BasicNoise::GetColor(const qbVector<double>& uv)
    {
        qbVector<double> in_coord = uv;
        qbVector<double> backCoord = ApplyTransform(uv);
        double u = backCoord.GetElement(0);
        double v = backCoord.GetElement(1);

        qbVector<double> locColor{4};

        if(!hasColorMap) locColor = qbVector{std::vector{1.0, 0.0, 1.0, 1.0}};
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
