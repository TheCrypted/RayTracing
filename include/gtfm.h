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

            void SetTransform(const qbVector<double> &translate, const qbVector<double> &rotate, const qbVector<double> &scale);

            Ray Apply(const Ray &ray, bool fwd);
            qbVector<double> Apply(const qbVector<double> &vec, bool fwd);

            friend GTform operator*(const qbRT::GTform &lhs, const qbRT::GTform &rhs);
            GTform operator=(const GTform &rhs);

            void PrintMatrix(bool dir);
            static void PrintVector(const qbVector<double> &vec);

            qbMatrix2<double> GetMatrix(bool dir);

        private:
            static void Print(const qbMatrix2<double> &matrix);

        private:
            qbMatrix2<double> m_fwd {4, 4};
            qbMatrix2<double> m_bck {4, 4};
    };
}



#endif //GTFM_H
