//
// Created by Aman's Laptop on 07-07-2024.
//

#ifndef OBJECTPLANE_H
#define OBJECTPLANE_H

#include "object.h"
#include "gtfm.h"
#include <cmath>

namespace qbRT
{
    class ObjPlane : public Object {
        public:
            ObjPlane();
            ~ObjPlane() override;

            bool TestIntersections(const Ray &rayOrig, Data::HitData& hitData) override;
        private:
    };
}



#endif //OBJECTPLANE_H
