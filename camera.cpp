//
// Created by Aman's Laptop on 30-06-2024.
//

#include "include/camera.h"

namespace qbRT
{
    Camera::Camera()
    {
        cameraPosition = qbVector<double> {std::vector<double> {0.0, -10.0, 0.0}};
        cameraLookAt = qbVector<double> {std::vector<double> {0.0, 0.0, 0.0}};
        cameraUp = qbVector<double> {std::vector<double> {0.0, 0.0, 1.0}};
        cameraLen = 1.0;
        cameraHorLen = 1.0;
        cameraAspRatio = 1.0;
    }


}