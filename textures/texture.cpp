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

    qbVector4<double> Texture::GetColor(const qbVector2<double>& coords)
    {
        qbVector4<double> res;
        return res;
    }

    double Texture::GetValue(const qbVector2<double>& coords)
    {
        return 0.0;
    }

    void Texture::SetTransform(const qbVector3<double>& translation, const double &rotation, const qbVector3<double>& scale)
    {
        qbMatrix33 transMat{std::vector{1.0, 0.0, translation.GetElement(0),
            0.0, 1.0, translation.GetElement(1),
            0.0, 0.0, 1.0}};

        qbMatrix33 rotMat{std::vector{cos(rotation), -sin(rotation), 0.0,
            sin(rotation), cos(rotation), 0.0,
            0.0, 0.0, 1.0}};

        qbMatrix33 scaleMat{std::vector{scale.GetElement(0), 0.0, 0.0,
            0.0, scale.GetElement(1), 0.0,
            0.0, 0.0, 1.0}};

        m_transform = transMat * rotMat * scaleMat;
    }

    qbVector3<double> Texture::BlendColors(const std::vector<qbVector3<double>> &inputColorList)
    {
        qbVector3<double> res;
        return res;
    }

    qbVector2<double> Texture::ApplyTransform(const qbVector2<double>& vec)
    {
        qbVector3<double> temp;
        temp.SetElement(0, vec.GetElement(0));
        temp.SetElement(1, vec.GetElement(1));

        qbVector3<double> convVec = m_transform * temp;

        qbVector2<double> output;
        output.SetElement(0, convVec.GetElement(0));
        output.SetElement(1, convVec.GetElement(1));

        return output;
    }

}