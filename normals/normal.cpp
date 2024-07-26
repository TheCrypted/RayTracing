//
// Created by Aman's Laptop on 26-07-2024.
//

#include "../include/normal.h"

namespace qbRT::Normal
{
    NormalBase::NormalBase()
    {

    }

    NormalBase::~NormalBase()
    = default;

    qbVector<double> NormalBase::CompPerturbation(const qbVector<double>& normal, const qbVector<double>& uvCoords)
    {
        return qbVector{std::vector{0.0, 0.0, 0.0}};
    }

    qbVector<double> NormalBase::PerturbNormal(const qbVector<double>& normal, const qbVector<double>& perturbation)
    {
        qbVector upVec = std::vector{0.0, 0.0, -1.0};
        if(normal.GetElement(2) > 0.99 || normal.GetElement(2) < -0.99)
            upVec = std::vector{1.0, 0.0, 0.0};

        qbVector<double> v = qbVector<double>::cross(upVec, normal);
        v.Normalize();
        qbVector<double> u = qbVector<double>::cross(normal, v);
        u.Normalize();

        qbVector<double> res = normal + perturbation.GetElement(0) * u + perturbation.GetElement(1) * v + perturbation.GetElement(2) * normal;
        res.Normalize();

        return res;
    }

    void NormalBase::SetAmplitude(double in_amp)
    {
        amplitude = in_amp;
    }

    qbVector<double> NormalBase::ApplyTransform(const qbVector<double>& inputVec)
    {
        qbVector<double> adjInput{3};
        adjInput.SetElement(0, inputVec.GetElement(0));
        adjInput.SetElement(1, inputVec.GetElement(1));
        qbVector<double> res = transMat * adjInput;

        return qbVector{std::vector{res.GetElement(0), res.GetElement(1)}};
    }

    void NormalBase::SetTransform(const qbVector<double>& translation, const double rotation, const qbVector<double>& scale)
    {
        qbMatrix2 rotationMatrix = {3, 3, std::vector {
            cos(rotation), -sin(rotation), 0.0,
            sin(rotation), cos(rotation), 0.0,
            0.0, 0.0, 1.0}};

        qbMatrix2 scaleMatrix = {3, 3, std::vector {
            scale.GetElement(0), 0.0, 0.0,
            0.0, scale.GetElement(1), 0.0,
            0.0, 0.0, 1.0}};

        qbMatrix2 translationMatrix = {3, 3, std::vector {
            1.0, 0.0, translation.GetElement(0),
            0.0, 1.0, translation.GetElement(1),
            0.0, 0.0, 1.0}};

        transMat = translationMatrix * rotationMatrix * scaleMatrix;
    }
}
