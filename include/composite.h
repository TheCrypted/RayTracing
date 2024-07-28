//
// Created by Aman's Laptop on 28-07-2024.
//

#ifndef COMPOSITE_H
#define COMPOSITE_H
#include "objCube.h"
#include "object.h"


namespace qbRT::Shape
{
    class Composite : public Object{
        public:
            Composite();
            ~Composite() override;

            void AddSubShape(std::shared_ptr<Object> obj);
            void GetExtents(qbVector<double>& x, qbVector<double>& y, qbVector<double>& z) override;
            bool TestIntersections(const Ray& ray, Data::HitData& hitData) override;
            void UpdateExtents();

        private:
            int TestIntersections(const Ray& castRay, const Ray& bckRay, qbVector<double>& intPoint,
                double currDist, Data::HitData& hitData);

        public:
            ObjCube boundingBox = ObjCube();
            bool useBoundingBox = true;
            std::vector<std::shared_ptr<Object>> shapes;
            qbVector<double> xLim{2};
            qbVector<double> yLim{2};
            qbVector<double> zLim{2};
    };
}



#endif //COMPOSITE_H
