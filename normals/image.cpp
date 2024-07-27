//
// Created by Aman's Laptop on 27-07-2024.
//

#include "../include/image.h"


namespace qbRT::Normal
{
    Image::Image()
    = default;

    Image::~Image()
    = default;

    bool Image::LoadImage(std::string in_filename)
    {
        if(hasImage) SDL_FreeSurface(imageSurface);

        filename = in_filename;
        imageSurface = SDL_LoadBMP(filename.c_str());

        if(!imageSurface)
        {
            std::cout << "Error loading image: " << filename << std::endl;
            hasImage = false;
            return false;
        }

        xSize = imageSurface->w;
        ySize = imageSurface->h;
        pitch = imageSurface->pitch;
        bytesPerPixel = imageSurface->format->BytesPerPixel;
        pixelFormat = imageSurface->format;

        hasImage = true;
        return true;
    }

    qbVector<double> Image::CompPerturbation(const qbVector<double>& normal, const qbVector<double>& uvCoords)
    {
        double xD = 0.0;
        double yD = 0.0;
        double zD = 0.0;
        if (hasImage)
        {
            qbVector<double> inputLoc = uvCoords;
            qbVector<double> newLoc = ApplyTransform(inputLoc);
            double u = newLoc.GetElement(0);
            double v = newLoc.GetElement(1);

            u = fmod(u, 1.0);
            v = fmod(v, 1.0);

            auto xsd = static_cast<double>(xSize);
            auto ysd = static_cast<double>(ySize);
            double xF = ((u + 1.0) / 2.0) * xsd;
            double yF = ysd - (((v + 1.0) / 2.0) * ysd);
            int x = static_cast<int>(round(xF));
            int y = static_cast<int>(round(yF));
            int xMin = static_cast<int>(floor(xF));
            int yMin = static_cast<int>(floor(yF));
            int xMax = static_cast<int>(ceil(xF));
            int yMax = static_cast<int>(ceil(yF));

            double r0, g0, b0, a0;
            double r1, g1, b1, a1;
            double r2, g2, b2, a2;
            double r3, g3, b3, a3;
            GetPixelVal(xMin, yMin, r0, g0, b0, a0);
            GetPixelVal(xMax, yMin, r1, g1, b1, a1);
            GetPixelVal(xMin, yMax, r2, g2, b2, a2);
            GetPixelVal(xMax, yMax, r3, g3, b3, a3);
            double interpR = BilinearInterpolate(xMin, yMin, r0, xMax, yMin, r1, xMin, yMax, r2, xMax, yMax, r3, xF, yF);
            double interpG = BilinearInterpolate(xMin, yMin, g0, xMax, yMin, g1, xMin, yMax, g2, xMax, yMax, g3, xF, yF);
            double interpB = BilinearInterpolate(xMin, yMin, b0, xMax, yMin, b1, xMin, yMax, b2, xMax, yMax, b3, xF, yF);

            xD = interpR;
            yD = interpG;
            zD = interpB;
        }

        if (reverse)
        {
            xD = -xD;
            yD = -yD;
        }

        qbVector perturbation = std::vector {xD, yD, zD};
        return PerturbNormal(normal, perturbation);
    }

    void Image::GetPixelVal(const double& x, const double& y, double& r, double& g, double& b, double& a)
    {
        int pixelInd = (x * bytesPerPixel) + (y * pitch);
        uint8_t *pixels = (uint8_t *) imageSurface->pixels;

        std::array<uint8_t, 4> byteVals;
        uint32_t currPixel = 0;
        for (int i = 0; i < bytesPerPixel; ++i)
        {
            byteVals[i] = pixels[pixelInd + i];
        }

        if(bytesPerPixel == 3)
        {
            currPixel = byteVals[0] | (byteVals[1] << 8) | (byteVals[2] << 16);
        } else if (bytesPerPixel == 4)
        {
            currPixel = byteVals[0] | (byteVals[1] << 8) | (byteVals[2] << 16) | (byteVals[3] << 24);
        }

        uint8_t r_, g_, b_, a_;
        SDL_GetRGBA(currPixel, imageSurface->format, &r_, &g_, &b_, &a_);

        r = static_cast<double>(r_ - 128) / 128.0;
        g = static_cast<double>(g_ - 128) / 128.0;
        b = static_cast<double>(b_ - 128) / 128.0;
    }

    double Image::LinInterpolate(const double& x0, const double& y0, const double& x1, const double& y1, const double& x)
    {
        double output;
        if((x1 - x0) == 0) output = y0;
        else output = y0 + ((x - x0) * (y1 - y0) / (x1 - x0));

        return output;
    }

    double Image::BilinearInterpolate(const double& x0, const double& y0, const double& v0, const double& x1,
        const double& y1, const double& v1, const double& x2, const double& y2, const double& v2, const double& x3,
        const double& y3, const double& v3, const double& x, const double& y)
    {
        double p1 = LinInterpolate(x0, v0, x1, v1, x);
        double p2 = LinInterpolate(x2, v2, x3, v3, x);
        double p3 = LinInterpolate(y0, p1, y2, p2, y);
        return p3;
    }
}