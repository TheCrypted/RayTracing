//
// Created by Aman's Laptop on 16-07-2024.
//

#ifndef MARCHTORUS_H
#define MARCHTORUS_H
#include "rayMarchBase.h"


namespace qbRT::RM
{
    class MarchTorus : public RayMarchBase{
        public:
            MarchTorus();
            ~MarchTorus() override;

            void SetRadii(double r1, double r2);

        private:
            double ObjectFcn(const qbVector3<double>* p, const qbVector3<double>* params);
            void UpdateBounds();

        private:
            double r1 = 1.0;
            double r2 = 0.25;
    };
}



#endif //MARCHTORUS_H
