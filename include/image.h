//
// Created by Aman's Laptop on 27-07-2024.
//

#ifndef IMAGE_H
#define IMAGE_H

#include <random>

#include "normal.h"
#include <SDL.h>
#include <array>


namespace qbRT::Normal
{
    class Image : public NormalBase {
        public:
            Image();
            ~Image() override;

            qbVector3<double> CompPerturbation(const qbVector3<double>& normal, const qbVector2<double>& uvCoords) override;
            bool LoadImage(std::string filename);

        private:
            double LinInterpolate(const double& x0, const double& y0, const double& x1, const double& y1, const double& x);
            double BilinearInterpolate(const double& x0, const double& y0, const double& v0,
                const double& x1, const double& y1, const double& v1,
                const double& x2, const double& y2, const double& v2,
                const double& x3, const double& y3, const double& v3, const double& x, const double& y);

            void GetPixelVal(const double& x, const double& y, double& r, double& g, double& b, double& a);

        public:
            bool reverse = false;

        private:
            qbMatrix33<double> transMat{std::vector{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};
            std::shared_ptr<std::mt19937> randGen;

            bool hasImage = false;
            std::string filename;
            SDL_Surface *imageSurface;
            SDL_PixelFormat *pixelFormat;
            int xSize, ySize, pitch;
            uint8_t bytesPerPixel;
    };
}



#endif //IMAGE_H
