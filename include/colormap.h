//
// Created by Aman's Laptop on 18-07-2024.
//

#ifndef COLORMAP_H
#define COLORMAP_H
#include "qbLinAlg/qbVector.h"
#include "qbLinAlg/qbVector4.hpp"


namespace qbRT::TextureBase
{
    class Colormap {
        public:
            Colormap();
            ~Colormap();

            void SetStop(double stop, const qbVector4<double> &color);
            qbVector4<double> GetColor(double stop);

        private:
            std::vector<double> stops;
            std::vector<qbVector4<double>> colors;
    };
}



#endif //COLORMAP_H
