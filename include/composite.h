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
            void GetExtents(qbVector2<double>& x, qbVector2<double>& y, qbVector2<double>& z) override;
            bool TestIntersections(const Ray& ray, Data::HitData& hitData) override;
            void UpdateExtents();

        private:
            int TestIntersections(const Ray& castRay, const Ray& bckRay, qbVector3<double>& intPoint,
                double& currDist, Data::HitData& hitData);

        public:
            ObjCube boundingBox = ObjCube();
            bool useBoundingBox = true;
            std::vector<std::shared_ptr<Object>> shapes;
            qbVector2<double> xLim;
            qbVector2<double> yLim;
            qbVector2<double> zLim;
    };
}



#endif //COMPOSITE_H
