//
// Created by Aman's Laptop on 13-07-2024.
//

#include "../include/checkerText.h"

namespace qbRT::TextureBase
{
    Checker::Checker()
    {
        Flat loc_color1;
        Flat loc_color2;
        loc_color1.SetColor(qbVector{std::vector{1.0, 1.0, 1.0, 1.0}});
        loc_color2.SetColor(qbVector{std::vector{0.2, 0.2, 0.2, 1.0}});

        color1 = std::make_shared<Flat>(loc_color1);
        color2 = std::make_shared<Flat>(loc_color2);
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
            res = color1 -> GetColor(uv);
        } else
        {
            res = color2 -> GetColor(uv);
        }

        return res;
    }

    void Checker::SetColor(const qbVector<double>& in_color1, const qbVector<double>& in_color2)
    {

        auto loc_color1 = std::make_shared<Flat>(Flat());
        auto loc_color2 = std::make_shared<Flat>(Flat());

        loc_color1 -> SetColor(in_color1);
        loc_color2 -> SetColor(in_color2);

        color1 = loc_color1;
        color2 = loc_color2;
    }

    void Checker::SetColor(const std::shared_ptr<Texture>& in_color1, const std::shared_ptr<Texture>& in_color2)
    {
        color1 = in_color1;
        color2 = in_color2;
    }

}