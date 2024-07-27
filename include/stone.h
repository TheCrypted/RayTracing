//
// Created by Aman's Laptop on 27-07-2024.
//

#ifndef STONE_H
#define STONE_H

#include <algorithm>
#include "colormap.h"
#include "texture.h"
#include "noise.h"
#include "valNoise.h"


namespace qbRT::TextureBase
{
    class Stone : public Texture{
		public:
			Stone();
			~Stone() override;

			qbVector<double> GetColor(const qbVector<double> &uvCoords) override;

			double GetValue(const qbVector<double> &uvCoords) override;

			void SetColorMap(const std::shared_ptr<Colormap> &colorMap);

			void SetAmplitude(double amplitude);

			void SetScale(int scale);

        public:
			std::shared_ptr<Colormap> colormap;
			bool hasColormap = false;
			Noise::ValNoise noiseGen1;
			Noise::ValNoise noiseGen2;

			double amp1 = 8.0;
			double amp2 = 4.0;

			int scale1 = 6;
			int scale2 = 30;

			double minVal, maxVal;
    };
}



#endif //STONE_H
