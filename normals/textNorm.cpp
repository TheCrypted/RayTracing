//
// Created by Aman's Laptop on 27-07-2024.
//

#include "../include/textNorm.h"

namespace qbRT::Normal
{
    TextureNormal::TextureNormal()
    = default;

    TextureNormal::~TextureNormal()
    = default;

    void TextureNormal::AssignTexture(const std::shared_ptr<TextureBase::Texture>& in_texture)
    {
        texture = in_texture;
        hasTexture = true;
    }

    qbVector<double> TextureNormal::CompPerturbation(const qbVector<double>& normal, const qbVector<double>& uvCoords)
    {
        double x = 0.0, y = 0.0, z = 0.0;

        if(hasTexture)
        {
            qbVector<double> uvDiff = TextureDiff(texture, uvCoords);
            if(!reverse)
            {
                x = -uvDiff.GetElement(0) * scale;
                y = -uvDiff.GetElement(1) * scale;
            } else
            {
                x = uvDiff.GetElement(0) * scale;
                y = uvDiff.GetElement(1) * scale;
            }

            qbVector perturbation = std::vector{x, y, z};
            return PerturbNormal(normal, perturbation);
        }
    }
}