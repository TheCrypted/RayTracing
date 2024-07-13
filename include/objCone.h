//
// Created by Aman's Laptop on 13-07-2024.
//

#ifndef OBJCONE_H
#define OBJCONE_H

#include "object.h"
#include "gtfm.h"
#include <array>

namespace qbRT
{
    class ObjCone : public Object{
        public:
            ObjCone();
            ~ObjCone();

            bool TestIntersections(const Ray& ray, qbVector<double>& intPoint, qbVector<double>& normal,
                qbVector<double>& color) override;
    };
}



#endif //OBJCONE_H
