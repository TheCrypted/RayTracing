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

        void SetObjectFunction(std::function<double(qbVector3<double>*, qbVector3<double>*)> objFunc);
        double EvaluateSDF(qbVector3<double>* location, qbVector3<double>* params);

        public:
            ObjCube boundingBox = ObjCube();
            qbVector3<double> params;

        private:
            std::function<double(qbVector3<double>*, qbVector3<double>*)> objectFunction;

            bool hasObjectFunction = false;
            double epsilon;
            int maxIterations;

            const double m_h = 0.001;
            qbVector3<double> m_xDisp {m_h, 0.0, 0.0};
            qbVector3<double> m_yDisp {0.0, m_h, 0.0};
            qbVector3<double> m_zDisp {0.0, 0.0, m_h};
    };
}



#endif //RAYMARCHBASE_H
