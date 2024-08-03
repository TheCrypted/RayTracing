//
// Created by Aman's Laptop on 26-07-2024.
//

#include "../include/marbleText.h"

namespace qbRT::TextureBase
{
    MarbleText::MarbleText()
    {
        noiseGenList.emplace_back();
        noiseGenList.emplace_back();

        noiseGenList[0].SetGrid(4);
        noiseGenList[1].SetGrid(40);

        maxVal = 3.0;
        minVal = -3.0;
    }

    MarbleText::~MarbleText()
    = default;


    qbVector4<double> MarbleText::GetColor(const qbVector2<double>& uv)
    {
        qbVector2<double> in_coord = uv;
        qbVector2<double> backCoord = ApplyTransform(uv);
        double u = backCoord.GetElement(0);
        double v = backCoord.GetElement(1);

        qbVector4<double> locColor;

        if(!hasColorMap) locColor = qbVector4{1.0, 0.0, 1.0, 1.0};
        else
        {
            double mapPos = sinAmp * sin(sinFreq * M_PI * ((u + v)/2.0 + (noiseGenList[0].GetValue(u, v) * amplitude1) *
                (noiseGenList[1].GetValue(u, v) * amplitude2)));
            mapPos = std::clamp((mapPos - minVal) / (maxVal - minVal), 0.0, 1.0);

            locColor = colorMap->GetColor(mapPos);
        }
        return locColor;
    }

    void MarbleText::SetColor(const std::shared_ptr<Colormap>& in_colorMap)
    {
        colorMap = in_colorMap;
        hasColorMap = true;
    }

    void MarbleText::SetAmplitude(double in_amplitude1, double in_amplitude2)
    {
        amplitude1 = in_amplitude1;
        amplitude2 = in_amplitude2;
    }

    void MarbleText::SetScale(int in_scale1, int in_scale2)
    {
        scale1 = in_scale1;
        scale2 = in_scale2;
        noiseGenList[0].SetGrid(scale1);
        noiseGenList[1].SetGrid(scale2);
    }

    void MarbleText::SetMinMax(double in_min, double in_max)
    {
        minVal = in_min;
        maxVal = in_max;
    }

    void MarbleText::SetSin(double in_amp, double in_freq)
    {
        sinAmp = in_amp;
        sinFreq = in_freq;
    }

}