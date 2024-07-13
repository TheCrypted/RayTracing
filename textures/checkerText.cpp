//
// Created by Aman's Laptop on 13-07-2024.
//

#include "../include/checkerText.h"

namespace qbRT::TextureBase
{
    Checker::Checker()
    {
        color1 = qbVector{std::vector{1.0, 1.0, 1.0, 1.0}};
        color2 = qbVector{std::vector{0.2, 0.2, 0.2, 1.0}};
    }

    Checker::~Checker()
    = default;

    qbVector<double> Checker::GetColor(const qbVector<double>& uv)
    {
        qbVector<double> convCoord = ApplyTransform(uv);
        double u = convCoord.GetElement(0);
        double v = convCoord.GetElement(1);

        qbVector<double> res{4};
        if((static_cast<int>(floor(u)) + static_cast<int>(floor(v))) % 2 == 0)
        {
            res = color1;
        } else
        {
            res = color2;
        }
        return res;
    }

    void Checker::SetColor(const qbVector<double>& in_color1, const qbVector<double>& in_color2)
    {
        color1 = in_color1;
        color2 = in_color2;
    }
}