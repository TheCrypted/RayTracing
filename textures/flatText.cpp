//
// Created by Aman's Laptop on 13-07-2024.
//

#include "../include/flatText.h"


namespace qbRT::TextureBase
{
    Flat::Flat()
    {
        color = qbVector4{std::vector<double> {1.0, 0.0, 0.0, 1.0}};
    }

    Flat::~Flat()
    = default;

    qbVector4<double> Flat::GetColor(const qbVector2<double>& uv)
    {
        return color;
    }

    void Flat::SetColor(const qbVector4<double>& inpColor)
    {
        color = inpColor;
    }
}

