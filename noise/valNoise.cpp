//
// Created by Aman's Laptop on 25-07-2024.
//

#include "../include/valNoise.h"

#include <bits/random.h>

namespace qbRT::Noise
{
    ValNoise::ValNoise()
    {
        SetGrid(2);
    }

    ValNoise::~ValNoise()
    = default;

    double ValNoise::GetValue(double u, double v)
    {
        u = fmod(u, 1.0);
        v = fmod(v, 1.0);

        u = (u + 1.0) / 2.0;
        v = (v + 1.0) / 2.0;

        double gridSpacing = 1.0 / static_cast<double>(scale);

        double localX = fmod(u, gridSpacing);
        double localY = fmod(v, gridSpacing);

        int minX = static_cast<int>((u - localX) * scale);
        int minY = static_cast<int>((v - localY) * scale);

        int c1Xi = std::max(minX, 0);
        int c1Yi = std::max(minY, 0);
        int c2Xi = std::min(minX + 1, scale);
        int c2Yi = std::max(minY, 0);

        int c3Xi = std::max(minX, 0);
        int c3Yi = std::min(minY + 1, scale);
        int c4Xi = std::min(minX + 1, scale);
        int c4Yi = std::min(minY + 1, scale);

        double v1 = valGrid[c1Xi][c1Yi];
        double v2 = valGrid[c2Xi][c2Yi];
        double v3 = valGrid[c3Xi][c3Yi];
        double v4 = valGrid[c4Xi][c4Yi];

        double xWeight = localX * static_cast<double>(scale);
        double yWeight = localY * static_cast<double>(scale);
        double t1 = CalcInterpolation(v1, v3, yWeight);
        double t2 = CalcInterpolation(v2, v4, yWeight);
        return CalcInterpolation(t1, t2, xWeight);
    }

    void ValNoise::SetGrid(int in_scale)
    {
        scale = in_scale;

        std::random_device rd;
        std::seed_seq seed{rd(), rd(), rd(), rd()};
        std::mt19937 randGen;

        std::uniform_real_distribution<double> randDist(0.0, 1.0);

        valGrid.clear();
        valGrid.resize(scale+1, std::vector(scale+1, 0.0));

        for (int i = 0; i <= scale; ++i)
        {
            for (int j = 0; j <= scale; ++j)
            {
                valGrid[i][j] = randDist(randGen);
            }
        }

        if(wrap)
        {
            for (int i = 0; i <= scale; ++i)
            {
                valGrid[i][scale] = valGrid[i][0];
            }

            for (int j = 0; j <= scale; ++j)
            {
                valGrid[scale][j] = valGrid[0][j];
            }
        }
    }

}
