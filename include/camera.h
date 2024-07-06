//
// Created by Aman's Laptop on 30-06-2024.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "./qbLinAlg/qbVector.h"
#include "ray.h"
#include <cmath>

namespace qbRT
{
    class Camera {
    public:
        // Constructor
        Camera();

        //Setters for camera parameters
        void set_camera_position(const qbVector<double>& camera_position)
        {
            cameraPosition = camera_position;
        }

        void set_camera_look_at(const qbVector<double>& camera_look_at)
        {
            cameraLookAt = camera_look_at;
        }

        void set_camera_up(const qbVector<double>& camera_up)
        {
            cameraUp = camera_up;
        }

        void set_camera_len(double camera_len)
        {
            cameraLen = camera_len;
        }

        void set_camera_hor_len(double camera_hor_len)
        {
            cameraHorLen = camera_hor_len;
        }

        void set_camera_asp_ratio(double camera_asp_ratio)
        {
            cameraAspRatio = camera_asp_ratio;
        }


        // Getters for camera parameters
        [[nodiscard]] qbVector<double> camera_position() const
        {
            return cameraPosition;
        }

        [[nodiscard]] qbVector<double> camera_look_at() const
        {
            return cameraLookAt;
        }

        [[nodiscard]] qbVector<double> camera_up() const
        {
            return cameraUp;
        }

        [[nodiscard]] double camera_len() const
        {
            return cameraLen;
        }

        [[nodiscard]] double camera_hor_len() const
        {
            return cameraHorLen;
        }

        [[nodiscard]] double camera_asp_ratio() const
        {
            return cameraAspRatio;
        }

        [[nodiscard]] qbVector<double> alignment_vector() const
        {
            return alignmentVector;
        }

        [[nodiscard]] qbVector<double> screen_u() const
        {
            return screenU;
        }

        [[nodiscard]] qbVector<double> screen_v() const
        {
            return screenV;
        }

        [[nodiscard]] qbVector<double> screen_centre() const
        {
            return screenCentre;
        }

        //Function to generate ray from camera
        bool GenerateRay(float x, float y, Ray &ray);

        // Update camera params
        void UpdateCameraGeometry();

    private:
        qbVector<double> cameraPosition;
        qbVector<double> cameraLookAt;
        qbVector<double> cameraUp;
        double cameraLen;
        double cameraHorLen;
        double cameraAspRatio;

        qbVector<double> alignmentVector;
        qbVector<double> screenU;
        qbVector<double> screenV;
        qbVector<double> screenCentre;
    };
}



#endif //CAMERA_H
