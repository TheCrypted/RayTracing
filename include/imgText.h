//
// Created by Aman's Laptop on 13-07-2024.
//

#ifndef IMGTEXT_H
#define IMGTEXT_H

#include <SDL.h>
#include "texture.h"


namespace qbRT::TextureBase
{
    class Image : public Texture {
        public:
            Image();
            ~Image() override;

            qbVector<double> GetColor(const qbVector<double>& uv) override;
            bool LoadImage(const std::string& path);

        private:
            std::string filename;
            SDL_Surface *imageSurface;
            SDL_PixelFormat *pixelFormat;
            bool imageLoaded = false;
            int xSize, ySize, pitch;
            uint8_t bytesPerPixel;
            uint32_t rMask, gMask, bMask, aMask;
    };
}




#endif //IMGTEXT_H
