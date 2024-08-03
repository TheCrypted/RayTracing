//
// Created by Aman's Laptop on 13-07-2024.
//

#ifndef IMGTEXT_H
#define IMGTEXT_H

#include <SDL.h>
#include "texture.h"
#include <array>


namespace qbRT::TextureBase
{
    class Image : public Texture
    {
    public:
		Image();
		~Image() override;

		qbVector4<double> GetColor(const qbVector2<double> &uvCoords) override;

		bool LoadImage(std::string fileName);

	private:
		double LinearInterp(const double &x0, const double &y0, const double &x1, const double &y1, const double &x);
		double BilinearInterp(	const double &x0, const double &y0, const double &v0,
			const double &x1, const double &y1, const double &v1,
			const double &x2, const double &y2, const double &v2,
			const double &x3, const double &y3, const double &v3,
			const double &x, const double &y);

		void GetPixelValue(int x, int y, double &red, double &green, double &blue, double &alpha);

		private:
			std::string m_fileName;
			SDL_Surface *m_imageSurface;
			SDL_PixelFormat *m_pixelFormat;
			bool m_imageLoaded = false;
			int m_xSize, m_ySize, m_pitch;
			uint8_t m_bytesPerPixel;
			uint32_t m_rMask, m_gMask, m_bMask, m_aMask;
	};
}




#endif //IMGTEXT_H
