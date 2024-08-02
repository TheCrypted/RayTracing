//
// Created by Aman's Laptop on 26-07-2024.
//

#include "../include/normal.h"

namespace qbRT::Normal
{
    NormalBase::NormalBase()
    = default;

    NormalBase::~NormalBase()
    = default;

    qbVector3<double> NormalBase::CompPerturbation(const qbVector3<double>& normal, const qbVector2<double>& uvCoords)
    {
        return qbVector3{0.0, 0.0, 0.0};
    }

    qbVector3<double> NormalBase::PerturbNormal(const qbVector3<double>& normal, const qbVector3<double>& perturbation)
    {
        qbVector3 upVec = std::vector{0.0, 0.0, -1.0};
        if(normal.GetElement(2) > 0.99 || normal.GetElement(2) < -0.99) upVec = std::vector{1.0, 0.0, 0.0};

        qbVector3<double> v = qbVector3<double>::cross(upVec, normal);
        v.Normalize();
        qbVector3<double> u = qbVector3<double>::cross(normal, v);
        u.Normalize();

        qbVector3<double> res = normal + perturbation.GetElement(0) * u + perturbation.GetElement(1) * v + perturbation.GetElement(2) * normal;
        res.Normalize();

        return res;
    }

    qbVector2<double> NormalBase::TextureDiff(const std::shared_ptr<TextureBase::Texture>& inputTexture, const qbVector2<double>& uvCoords)
    {
        double h = 0.001;
        qbVector2 uDis = std::vector{h, 0.0};
        qbVector2 vDis = std::vector{0.0, h};
        double uGrad = (inputTexture->GetValue(uvCoords + uDis) - inputTexture->GetValue(uvCoords - uDis)) / (2.0 * h);
        double vGrad = (inputTexture->GetValue(uvCoords + vDis) - inputTexture->GetValue(uvCoords - vDis)) / (2.0 * h);

        qbVector2 output = std::vector{uGrad, vGrad};
        return output;
    }


    void NormalBase::SetAmplitude(double in_amp)
    {
        amplitude = in_amp;
    }

    qbVector2<double> NormalBase::ApplyTransform(const qbVector2<double>& inputVec)
    {
        qbVector3<double> adjInput;
        adjInput.SetElement(0, inputVec.GetElement(0));
        adjInput.SetElement(1, inputVec.GetElement(1));
        qbVector3<double> res = transMat * adjInput;

        return qbVector2{res.GetElement(0), res.GetElement(1)};
    }

    void NormalBase::SetTransform(const qbVector3<double>& translation, const double rotation, const qbVector3<double>& scale)
    {
        qbMatrix33 rotationMatrix = {std::vector {
            cos(rotation), -sin(rotation), 0.0,
            sin(rotation), cos(rotation), 0.0,
            0.0, 0.0, 1.0}};

        qbMatrix33 scaleMatrix = {std::vector {
            scale.GetElement(0), 0.0, 0.0,
            0.0, scale.GetElement(1), 0.0,
            0.0, 0.0, 1.0}};

        qbMatrix33 translationMatrix = {std::vector {
            1.0, 0.0, translation.GetElement(0),
            0.0, 1.0, translation.GetElement(1),
            0.0, 0.0, 1.0}};

        transMat = translationMatrix * rotationMatrix * scaleMatrix;
    }
}
