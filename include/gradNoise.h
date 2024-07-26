//
// Created by Aman's Laptop on 26-07-2024.
//

#ifndef GRADNOISE_H
#define GRADNOISE_H
#include <vector>
#include <random>
#include "noise.h"


namespace qbRT::Noise
{
    class GradNoise : public NoiseBase{
        public:
            GradNoise();
            ~GradNoise() override;

            double GetValue(double u, double v) override;
            void SetGrid(int scale) override;

        private:
            std::vector<double> ComputeNormDisp(double x1, double y1, double x2, double y2);

        public:
            std::vector<std::vector<double>> vectorGridX;
            std::vector<std::vector<double>> vectorGridY;
            bool wrap = false;

    };
}



#endif //GRADNOISE_H
