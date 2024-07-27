//
// Created by Aman's Laptop on 27-07-2024.
//

#include "../include/stone.h"

namespace qbRT::TextureBase
{
	Stone::Stone()
	{
		amp1 = 1.0;
		amp2 = 1.0;
		scale1 = 32;
		scale2 = 64;
		minVal = -2.0;
		maxVal = 2.0;

		noiseGen1.SetGrid(scale1);
		noiseGen2.SetGrid(scale2);

		auto stoneMap = std::make_shared<Colormap> (Colormap());
		stoneMap -> SetStop(0.0, qbVector{std::vector{0.2, 0.2, 0.2, 1.0}});
		stoneMap -> SetStop(0.25, qbVector{std::vector{0.8, 0.8, 0.8, 1.0}});
		stoneMap -> SetStop(0.5, qbVector{std::vector{0.5, 0.5, 0.5, 1.0}});
		stoneMap -> SetStop(0.75, qbVector{std::vector{0.1, 0.1, 0.1, 1.0}});
		stoneMap -> SetStop(1.0, qbVector{std::vector{0.2, 0.2, 0.2, 1.0}});
		SetColorMap(stoneMap);
	}

	Stone::~Stone()
	= default;

	qbVector<double> Stone::GetColor(const qbVector<double> &uvCoords)
	{
		qbVector inputLoc = uvCoords;
		qbVector newLoc = ApplyTransform(inputLoc);
		double newU = newLoc.GetElement(0);
		double newV = newLoc.GetElement(1);

		qbVector<double> localColor{4};
		if (!hasColormap)
		{
			localColor = qbVector{std::vector{1.0, 0.0, 1.0, 1.0}};
		}
		else
		{
			double mapPosition = noiseGen1.GetValue(newU, newV) * amp1 +
				noiseGen2.GetValue(newU, newV) * amp2;

			mapPosition = std::clamp((mapPosition - minVal) / (maxVal - minVal), 0.0, 1.0);
			localColor = colormap -> GetColor(mapPosition);
		}

		return localColor;
	}

	double Stone::GetValue(const qbVector<double> &uvCoords)
	{
		qbVector inputLoc = uvCoords;
		qbVector newLoc = ApplyTransform(inputLoc);
		double newU = newLoc.GetElement(0);
		double newV = newLoc.GetElement(1);

		double mapPosition = noiseGen1.GetValue(newU, newV) * amp1 +
				noiseGen2.GetValue(newU, newV) * amp2;

		mapPosition = std::clamp((mapPosition - minVal) / (maxVal - minVal), 0.0, 1.0);
		return mapPosition;
	}

	void Stone::SetColorMap(const std::shared_ptr<Colormap> &colorMap)
	{
		colormap = colorMap;
		hasColormap = true;
	}

	void Stone::SetAmplitude(double amplitude)
	{
		amp1 = amplitude;
	}

	void Stone::SetScale(int scale)
	{
		scale1 = scale;
		noiseGen1.SetGrid(scale1);
	}
}