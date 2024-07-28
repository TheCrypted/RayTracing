//
// Created by Aman's Laptop on 15-07-2024.
//

#ifndef OBJCUBE_H
#define OBJCUBE_H

#include "object.h"
#include "gtfm.h"
#include <array>


namespace qbRT
{
    class ObjCube : public Object {
        public:
            ObjCube();
            ~ObjCube() override;

            bool TestIntersections(const Ray& ray, Data::HitData& hitData) override;

        private:
            std::array<double, 6>  t;
            std::array<double, 6>  u;
            std::array<double, 6>  v;
    };
}



#endif //OBJCUBE_H
