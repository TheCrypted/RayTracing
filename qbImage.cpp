//
// Created by Aman's Laptop on 30-06-2024.
//

#include "include/qbImage.h"

qbImage::qbImage()
{
    m_xSize = 0;
    m_ySize = 0;
    m_texture = NULL;
}

qbImage::~qbImage()
{
    if(m_texture != NULL) SDL_DestroyTexture(m_texture);
}

void qbImage::Initialize(const int xSize, const int ySize, SDL_Renderer *renderer)
{
    m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));

    m_xSize = xSize;
    m_ySize = ySize;

    m_renderer = renderer;

    InitTexture();
}

void qbImage::SetPixel(const int x, const int y, const double red, const double green, const double blue)
{
    m_rChannel[x][y] = red;
    m_gChannel[x][y] = green;
    m_bChannel[x][y] = blue;
}