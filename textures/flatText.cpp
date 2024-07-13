//
// Created by Aman's Laptop on 13-07-2024.
//

#include "../include/flatText.h"


namespace qbRT::TextureBase
{
    Flat::Flat()
    {
        color = qbVector{std::vector{1.0, 0.0, 0.0, 1.0}};
    }

    Flat::~Flat()
    = default;

    qbVector<double> Flat::GetColor(const qbVector<double>& uv)
    {
        return color;
    }

    void Flat::SetColor(const qbVector<double>& inpColor)
    {
        color = inpColor;
    }
}

