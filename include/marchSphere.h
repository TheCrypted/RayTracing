//
// Created by Aman's Laptop on 16-07-2024.
//

#ifndef MARCHSPHERE_H
#define MARCHSPHERE_H

#include "rayMarchBase.h"


namespace qbRT::RM
{
    class MarchSphere : public RayMarchBase{
        public:
            MarchSphere();
            ~MarchSphere() override;

        private:
            double ObjectFcn(const qbVector<double>* p, const qbVector<double>* params);

    };
}



#endif //MARCHSPHERE_H
