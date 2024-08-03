//
// Created by Aman's Laptop on 30-06-2024.
//

#include "include/camera.h"

namespace qbRT
{
    Camera::Camera()
    {
        cameraPosition = qbVector3 (std::vector {0.0, -10.0, 0.0});
        cameraLookAt = qbVector3 (std::vector {0.0, 0.0, 0.0});
        cameraUp = qbVector3 (std::vector {0.0, 0.0, 1.0});
        cameraLen = 1.0;
        cameraHorLen = 1.0;
        cameraAspRatio = 1.0;
    }

    void Camera::UpdateCameraGeometry()
    {
        alignmentVector = cameraLookAt - cameraPosition;
        alignmentVector.Normalize();

        screenU = qbVector3<double>::cross(alignmentVector, cameraUp);
        screenU.Normalize();
        screenV = qbVector3<double>::cross(screenU, alignmentVector);
        screenV.Normalize();

        screenCentre = cameraPosition + alignmentVector * cameraLen;

        screenU = screenU * cameraHorLen;
        screenV = screenV * (cameraHorLen / cameraAspRatio);
    }

    bool Camera::GenerateRay(float x, float y, Ray &ray)
    {
        qbVector3<double> point = screenCentre + screenU * x + screenV * y;

        ray.m_point1 = cameraPosition;
        ray.m_point2 = point;
        ray.m_lab = point - cameraPosition;

        return true;
    }



}