//
// Created by Aman's Laptop on 26-07-2024.
//

#ifndef NORMAL_H
#define NORMAL_H
#include "qbLinAlg/qbMatrix.h"
#include "qbLinAlg/qbVector.h"


namespace qbRT::Normal
{
    class NormalBase {
        public:
            NormalBase();
            virtual ~NormalBase();

            virtual qbVector<double> CompPerturbation(const qbVector<double>& normal, const qbVector<double>& uvCoords);
            qbVector<double> PerturbNormal(const qbVector<double>& normal, const qbVector<double>& perturbation);

            void SetAmplitude(double in_amp);
            void SetTransform(const qbVector<double>& translation, const double rotation, const qbVector<double>& scale);
            qbVector<double> ApplyTransform(const qbVector<double>& inputVec);

        public:
            double amplitude = 1.0;

        private:
            qbMatrix2<double> transMat{3, 3, std::vector{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};

    };
}



#endif //NORMAL_H
