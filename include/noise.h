//
// Created by Aman's Laptop on 25-07-2024.
//

#ifndef NOISE_H
#define NOISE_H

#include <cmath>

namespace qbRT::Noise
{
    class NoiseBase {
        public:
            NoiseBase();
            virtual ~NoiseBase();

            virtual double GetValue(double u, double v);
            double CalcInterpolation(double a, double b, double pos);

            virtual void SetGrid(int scale);

        public:
            int scale;
    };
}



#endif //NOISE_H
