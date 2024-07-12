//
// Created by Aman's Laptop on 12-07-2024.
//

#ifndef OBJECTCYLINDER_H
#define OBJECTCYLINDER_H

#include "object.h"
#include "gtfm.h"
#include <array>

namespace qbRT
{
    class ObjCylinder : public Object {
        public:
            ObjCylinder();
            ~ObjCylinder() override;

            bool TestIntersections(const Ray& ray, qbVector<double>& intPoint, qbVector<double>& normal,
                qbVector<double>& color) override;


    };
}



#endif //OBJECTCYLINDER_H
