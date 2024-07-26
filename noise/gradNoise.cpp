//
// Created by Aman's Laptop on 26-07-2024.
//

#include "../include/gradNoise.h"

#include "../include/qbLinAlg/qbVector.h"

namespace qbRT::Noise
{
    GradNoise::GradNoise()
    {
        SetGrid(2);
    }

    GradNoise::~GradNoise()
    = default;

    double GradNoise::GetValue(double u, double v)
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

        std::vector v1 = std::vector{vectorGridX[c1Xi][c1Yi], vectorGridY[c1Xi][c1Yi]};
        std::vector v2 = std::vector{vectorGridX[c2Xi][c2Yi], vectorGridY[c2Xi][c2Yi]};
        std::vector v3 = std::vector{vectorGridX[c3Xi][c3Yi], vectorGridY[c3Xi][c3Yi]};
        std::vector v4 = std::vector{vectorGridX[c4Xi][c4Yi], vectorGridY[c4Xi][c4Yi]};

        double c1X = static_cast<double>(c1Xi) * gridSpacing;
        double c1Y = static_cast<double>(c1Yi) * gridSpacing;
        double c2X = static_cast<double>(c2Xi) * gridSpacing;
        double c2Y = static_cast<double>(c2Yi) * gridSpacing;
        double c3X = static_cast<double>(c3Xi) * gridSpacing;
        double c3Y = static_cast<double>(c3Yi) * gridSpacing;
        double c4X = static_cast<double>(c4Xi) * gridSpacing;
        double c4Y = static_cast<double>(c4Yi) * gridSpacing;

        std::vector d1 = ComputeNormDisp(u, v, c1X, c1Y);
        std::vector d2 = ComputeNormDisp(u, v, c2X, c2Y);
        std::vector d3 = ComputeNormDisp(u, v, c3X, c3Y);
        std::vector d4 = ComputeNormDisp(u, v, c4X, c4Y);

        double dp1 = v1[0] * d1[0] + v1[1] * d1[1];
        double dp2 = v2[0] * d2[0] + v2[1] * d2[1];
        double dp3 = v3[0] * d3[0] + v3[1] * d3[1];
        double dp4 = v4[0] * d4[0] + v4[1] * d4[1];

        double xWeight = localX * static_cast<double>(scale);
        double yWeight = localY * static_cast<double>(scale);
        double t1 = CalcInterpolation(dp1, dp3, yWeight);
        double t2 = CalcInterpolation(dp2, dp4, yWeight);

        return CalcInterpolation(t1, t2, xWeight);
    }

    void GradNoise::SetGrid(int in_scale)
    {
        scale = in_scale;

        std::random_device rd;
        std::seed_seq seed{rd(), rd(), rd(), rd()};
        std::mt19937 randGen;

        std::uniform_real_distribution<double> randDist(0.0, 1.0);

        vectorGridX.clear();
        vectorGridY.clear();
        vectorGridX.resize(scale+1, std::vector(scale+1, 0.0));
        vectorGridY.resize(scale+1, std::vector(scale+1, 0.0));

        for (int i = 0; i <= scale; ++i)
        {
            for (int j = 0; j <= scale; ++j)
            {
                double angle = 2.0 * M_PI * randDist(randGen);
                vectorGridX[i][j] = cos(angle);
                vectorGridY[i][j] = sin(angle);
            }
        }

        if(wrap)
        {
            for (int i = 0; i <= scale; ++i)
            {
                vectorGridX[i][scale] = vectorGridX[i][0];
                vectorGridY[i][scale] = vectorGridY[i][0];
            }

            for (int j = 0; j <= scale; ++j)
            {
                vectorGridX[scale][j] = vectorGridX[0][j];
                vectorGridY[scale][j] = vectorGridY[0][j];
            }
        }
    }

    std::vector<double> GradNoise::ComputeNormDisp(double x1, double y1, double x2, double y2)
    {
        return std::vector{x1 - x2, y1 - y2};
    }





}
