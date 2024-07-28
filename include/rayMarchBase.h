//
// Created by Aman's Laptop on 16-07-2024.
//

#ifndef RAYMARCHBASE_H
#define RAYMARCHBASE_H

#include <functional>
#include "object.h"
#include "objCube.h"
#include "distFunc.h"


namespace qbRT::RM
{
    class RayMarchBase : public Object {
    public:
        RayMarchBase();
        ~RayMarchBase() override;

        bool TestIntersections(const Ray& ray, Data::HitData& hitData) override;

        void SetObjectFunction(std::function<double(qbVector<double>*, qbVector<double>*)> objFunc);
        double EvaluateSDF(qbVector<double>* location, qbVector<double>* params);

        public:
            ObjCube boundingBox = ObjCube();
            qbVector<double> params{3};

        private:
            std::function<double(qbVector<double>*, qbVector<double>*)> objectFunction;

            bool hasObjectFunction = false;
            double epsilon;
            int maxIterations;

            const double m_h = 0.001;
            qbVector<double> m_xDisp {std::vector{m_h, 0.0, 0.0}};
            qbVector<double> m_yDisp {std::vector{0.0, m_h, 0.0}};
            qbVector<double> m_zDisp {std::vector{0.0, 0.0, m_h}};
    };
}



#endif //RAYMARCHBASE_H
