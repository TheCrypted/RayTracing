//
// Created by Aman's Laptop on 18-07-2024.
//

#ifndef COLORMAP_H
#define COLORMAP_H
#include "qbLinAlg/qbVector.h"


namespace qbRT::Textures
{
    class Colormap {
        public:
            Colormap();
            ~Colormap();

            void SetStop(double stop, const qbVector<double> &color);
            qbVector<double> GetColor(double stop);

        private:
            std::vector<double> stops;
            std::vector<qbVector<double>> colors;
    };
}



#endif //COLORMAP_H
