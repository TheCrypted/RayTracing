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
    m_rChannel.resize(xSize, std::vector(ySize, 0.0));
    m_gChannel.resize(xSize, std::vector(ySize, 0.0));
    m_bChannel.resize(xSize, std::vector(ySize, 0.0));

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

int qbImage::GetXSize() const {return m_xSize;}
int qbImage::GetYSize() const {return m_ySize;}

void qbImage::Display()
{
    ComputeMaxValues();

    auto *tempPixels = new Uint32[m_xSize * m_ySize];
    memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));

    for (int i = 0; i < m_xSize; ++i)
    {
        for (int j = 0; j < m_ySize; ++j)
        {
            tempPixels[j * m_xSize + i] = ConvertColor(m_rChannel[i][j], m_gChannel[i][j], m_bChannel[i][j]);
        }
    }

    SDL_UpdateTexture(m_texture, NULL, tempPixels, m_xSize * sizeof(Uint32));

    delete[] tempPixels;

    SDL_Rect srcRect, bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_xSize;
    srcRect.h = m_ySize;
    bounds = srcRect;

    SDL_RenderCopy(m_renderer, m_texture, &srcRect, &bounds);
}

void qbImage::InitTexture()
{
    Uint32 rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        int shift = 8;
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    if(m_texture != nullptr) SDL_DestroyTexture(m_texture);
    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
    m_texture = SDL_CreateTextureFromSurface(m_renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

void qbImage::ComputeMaxValues()
{
    max_red = 0.0;
    max_green = 0.0;
    max_blue = 0.0;
    max_net = 0.0;
    for(int x = 0; x < m_xSize; ++x)
    {
        for(int y = 0; y < m_ySize; ++y)
        {
            if(m_rChannel[x][y] > max_red) max_red = m_rChannel[x][y];
            if(m_gChannel[x][y] > max_green) max_green = m_gChannel[x][y];
            if(m_bChannel[x][y] > max_blue) max_blue = m_bChannel[x][y];

            max_net = std::max(max_net, max_red);
            max_net = std::max(max_net, max_green);
            max_net = std::max(max_net, max_blue);
        }
    }
}


Uint32 qbImage::ConvertColor(const double red, const double green, const double blue)
{
    auto r = static_cast<unsigned char>((red / max_net) * 255.0);
    auto g = static_cast<unsigned char>((green / max_net) * 255.0);
    auto b = static_cast<unsigned char>((blue / max_net) * 255.0);

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
    #else
        Uint32 pixelColor = (255 << 24) + (r << 16) + (g << 8) + b;
    #endif

    return pixelColor;
}

