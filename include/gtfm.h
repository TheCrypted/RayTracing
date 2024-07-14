//
// Created by Aman's Laptop on 07-07-2024.
//

#ifndef GTFM_H
#define GTFM_H

#include "qbLinAlg/qbMatrix.h"
#include "qbLinAlg/qbVector.h"
#include "ray.h"


namespace qbRT
{
    constexpr bool FWDTFORM = true;
    constexpr bool BCKTFORM = false;

    class GTform {
        public:
            GTform();
            ~GTform();
            GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck);
            GTform(const qbVector<double> &translate, const qbVector<double> &rotate, const qbVector<double> &scale);

            void SetTransform(const qbVector<double> &translate, const qbVector<double> &rotate, const qbVector<double> &scale);

            Ray Apply(const Ray &ray, bool fwd);
            qbVector<double> Apply(const qbVector<double> &vec, bool fwd);
            qbVector<double> ApplyNormal(const qbVector<double> normal);

            friend GTform operator*(const qbRT::GTform &lhs, const qbRT::GTform &rhs);
            GTform operator=(const GTform &rhs);

            void PrintMatrix(bool dir);
            static void PrintVector(const qbVector<double> &vec);

            qbMatrix2<double> GetMatrix(bool dir);
            qbMatrix2<double> GetNormalTrans();

        private:
            static void Print(const qbMatrix2<double> &matrix);
            void UpdateLinTfm();

        private:
            qbMatrix2<double> m_fwd {4, 4};
            qbMatrix2<double> m_bck {4, 4};
            qbMatrix2<double> m_lintfm {3, 3};
    };
}



#endif //GTFM_H
