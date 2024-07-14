//
// Created by Aman's Laptop on 13-07-2024.
//

#include "../include/imgText.h"

namespace qbRT::TextureBase
{
    Image::Image()
    = default;

    Image::~Image()
    {
        if(imageLoaded)
        {
            SDL_FreeSurface(imageSurface);
            imageLoaded = false;
        }
    }

    qbVector<double> Image::GetColor(const qbVector<double>& uv)
    {
        qbVector<double> res{4};

        if(!imageLoaded)
        {
            res = qbVector{std::vector{1.0, 0.0, 1.0, 1.0}};
        } else
        {
            qbVector<double> convCoord = ApplyTransform(uv);
            double u = convCoord.GetElement(0);
            double v = convCoord.GetElement(1);

            int x = static_cast<int>(round(((u + 1.0) / 2.0) * static_cast<double>(xSize)));
            int y = ySize - (static_cast<int>(round(((v + 1.0) / 2.0) * static_cast<double>(ySize))));

            x = ((x % xSize) + xSize) % xSize;
            y = ((y % ySize) + ySize) % ySize;

            int pixelInd = x + (y * (pitch / bytesPerPixel));
            auto *pixels = (uint32_t *) imageSurface->pixels;

            uint32_t pixel = pixels[pixelInd];

            uint8_t r, g, b, a;
            SDL_GetRGBA(pixel, imageSurface->format, &r, &g, &b, &a);

            res.SetElement(0, static_cast<double>(r) / 255.0);
            res.SetElement(1, static_cast<double>(g) / 255.0);
            res.SetElement(2, static_cast<double>(b) / 255.0);
            res.SetElement(3, static_cast<double>(a) / 255.0);
        }

        return res;
    }

    bool Image::LoadImage(const std::string& path)
    {
        if(imageLoaded)
        {
            SDL_FreeSurface(imageSurface);
        }

        filename = path;
        imageSurface = SDL_LoadBMP(path.c_str());

        if(!imageSurface)
        {
            std::cerr << "Error loading image: " << SDL_GetError() << std::endl;
            imageLoaded = false;
            return false;
        }

        xSize = imageSurface->w;
        ySize = imageSurface->h;
        pitch = imageSurface->pitch;
        bytesPerPixel = imageSurface->format->BytesPerPixel;
        rMask = imageSurface->format->Rmask;
        gMask = imageSurface->format->Gmask;
        bMask = imageSurface->format->Bmask;
        aMask = imageSurface->format->Amask;

        imageLoaded = true;
        return true;
    }



}