//
// Created by Aman's Laptop on 07-07-2024.
//

#ifndef GTFM_H
#define GTFM_H

#include "qbLinAlg/qbMatrix.h"
#include "qbLinAlg/qbVector.h"
#include "qbLinAlg/qbVector2.hpp"
#include "qbLinAlg/qbVector3.hpp"
#include "qbLinAlg/qbVector4.hpp"
#include "ray.h"
#include "qbLinAlg/qbMatrix44.hpp"


namespace qbRT
{
    constexpr bool FWDTFORM = true;
    constexpr bool BCKTFORM = false;

    class GTform {
        public:
            GTform();
            ~GTform();
            GTform(const qbMatrix44<double> &fwd, const qbMatrix44<double> &bck);
            GTform(const qbVector3<double> &translate, const qbVector3<double> &rotate, const qbVector3<double> &scale);

            void SetTransform(const qbVector3<double> &translate, const qbVector3<double> &rotate, const qbVector3<double> &scale);

            Ray Apply(const Ray &ray, bool fwd);
            qbVector3<double> Apply(const qbVector3<double> &vec, bool fwd);
            qbVector3<double> ApplyNormal(const qbVector3<double> normal);

            friend GTform operator*(const qbRT::GTform &lhs, const qbRT::GTform &rhs);
            GTform operator=(const GTform &rhs);

            void PrintMatrix(bool dir);
            static void PrintVector(const qbVector3<double> &vec);

            qbMatrix44<double> GetMatrix(bool dir);
            qbMatrix33<double> GetNormalTrans();

        private:
            static void Print(const qbMatrix44<double> &matrix);
            void UpdateLinTfm();

        private:
            qbMatrix44<double> m_fwd;
            qbMatrix44<double> m_bck;
            qbMatrix33<double> m_lintfm;
    };
}



#endif //GTFM_H
