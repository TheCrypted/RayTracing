//
// Created by Aman's Laptop on 25-07-2024.
//

#ifndef VALNOISE_H
#define VALNOISE_H

#include <vector>
#include "noise.h"


namespace qbRT::Noise
{
    class ValNoise : public NoiseBase {

        public:
            ValNoise();
            ~ValNoise() override;

            double GetValue(double u, double v) override;
            void SetGrid(int scale) override;

        public:
            std::vector<std::vector<double>> valGrid;
            bool wrap = false;

    };
}



#endif //VALNOISE_H
