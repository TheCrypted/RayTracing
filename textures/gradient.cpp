//
// Created by Aman's Laptop on 18-07-2024.
//

#include "../include/gradient.h"

namespace qbRT::TextureBase
{
    Gradient::Gradient()
    = default;

    Gradient::~Gradient()
    = default;

    qbVector4<double> Gradient::GetColor(const qbVector2<double>& coords)
    {
        qbVector2<double> input = coords;
        qbVector2<double> newInput = ApplyTransform(input);
        double uScaled = std::min((newInput.GetElement(1) + 1.0) / 2.0, 1.0);
        return colormap.GetColor(uScaled);
    }

    double Gradient::GetValue(const qbVector2<double>& coords)
    {
        qbVector2<double> input = coords;
        qbVector2<double> newInput = ApplyTransform(input);
        return std::min((newInput.GetElement(1) + 1.0) / 2.0, 1.0);
    }

    void Gradient::SetStop(double stop, const qbVector4<double>& color)
    {
        colormap.SetStop(stop, color);
    }
}