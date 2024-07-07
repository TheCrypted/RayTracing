//
// Created by Aman's Laptop on 07-07-2024.
//

#ifndef OBJECTPLANE_H
#define OBJECTPLANE_H

#include "object.h"
#include "gtfm.h"

namespace qbRT
{
    class ObjPlane : public Object {
        public:
            ObjPlane();
            ~ObjPlane() override;

            bool TestIntersections(const Ray &rayOrig, qbVector<double> &intPoint, qbVector<double> &normal, qbVector<double> &color) override;
        private:
    };
}



#endif //OBJECTPLANE_H
