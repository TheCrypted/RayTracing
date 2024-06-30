//
// Created by Aman's Laptop on 30-06-2024.
//

#ifndef QBIMAGE_H
#define QBIMAGE_H

#include <SDL.h>
#include <string>
#include <vector>

class qbImage
{
    public:
        qbImage();
        ~qbImage();

        void Initialize(int xSize, int ySize, SDL_Renderer *renderer);
        void SetPixel(int x, int y, double red, double green, double blue);
        void Display();

    private:
        Uint32 ConvertColor(double red, double green, double blue);

        void InitTexture();

    private:
        std::vector<std::vector<double>> m_rChannel;
        std::vector<std::vector<double>> m_gChannel;
        std::vector<std::vector<double>> m_bChannel;

        int m_xSize, m_ySize;
        SDL_Renderer *m_renderer;
        SDL_Texture *m_texture;

};

#endif //QBIMAGE_H
