//
// Created by Aman's Laptop on 13-07-2024.
//

#include "../include/texture.h"

namespace qbRT::TextureBase
{
    Texture::Texture()
    = default;

    Texture::~Texture()
    = default;

    qbVector<double> Texture::GetColor(const qbVector<double>& coords)
    {
        qbVector<double> res{4};
        return res;
    }

    void Texture::SetTransform(const qbVector<double>& translation, const double &rotation, const qbVector<double>& scale)
    {
        qbMatrix2 transMat{3, 3, std::vector{1.0, 0.0, translation.GetElement(0),
            0.0, 1.0, translation.GetElement(1),
            0.0, 0.0, 1.0}};

        qbMatrix2 rotMat{3, 3, std::vector{cos(rotation), -sin(rotation), 0.0,
            sin(rotation), cos(rotation), 0.0,
            0.0, 0.0, 1.0}};

        qbMatrix2 scaleMat{3, 3, std::vector{scale.GetElement(0), 0.0, 0.0,
            0.0, scale.GetElement(1), 0.0,
            0.0, 0.0, 1.0}};

        m_transform = transMat * rotMat * scaleMat;
    }

    qbVector<double> Texture::BlendColors(const std::vector<qbVector<double>> &inputColorList)
    {
        qbVector<double> res {3};
        return res;
    }

    qbVector<double> Texture::ApplyTransform(const qbVector<double>& vec)
    {
        qbVector<double> temp{3};
        temp.SetElement(0, vec.GetElement(0));
        temp.SetElement(1, vec.GetElement(1));

        qbVector<double> convVec = m_transform * temp;

        qbVector<double> output{2};
        output.SetElement(0, convVec.GetElement(0));
        output.SetElement(1, convVec.GetElement(1));

        return output;
    }


}