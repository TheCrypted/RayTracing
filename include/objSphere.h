//
// Created by Aman's Laptop on 06-07-2024.
//

#ifndef OBJSPHERE_H
#define OBJSPHERE_H

#include "object.h"
#include "gtfm.h"

namespace qbRT
{
    class ObjSphere : public Object
    {
        public:
            ObjSphere();
            // ObjSphere(qbVector<double> center, double radius, qbVector<double> color);
            ~ObjSphere() override;

            bool TestIntersections(const Ray &rayOrig, qbVector<double> &intPoint, qbVector<double> &normal, qbVector<double> &color) override;
        private:

    };
}



#endif //OBJSPHERE_H
