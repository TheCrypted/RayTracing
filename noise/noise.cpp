//
// Created by Aman's Laptop on 25-07-2024.
//

#include "../include/noise.h"


namespace qbRT::Noise
{
    NoiseBase::NoiseBase()
    = default;

    NoiseBase::~NoiseBase()
    = default;

    double NoiseBase::GetValue(double u, double v)
    {
        return 0.0;
    }

    void NoiseBase::SetGrid(int in_scale)
    {
        scale = in_scale;
    }

    double NoiseBase::CalcInterpolation(double a, double b, double pos)
    {
        return a + (b - a) * (3 * std::pow(pos, 2) - std::pow(pos, 3) * 2);
    }







}
