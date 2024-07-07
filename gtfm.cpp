//
// Created by Aman's Laptop on 07-07-2024.
//

#include "include/gtfm.h"

namespace qbRT
{
    GTform::GTform()
    {
        m_fwd.SetToIdentity();
        m_bck.SetToIdentity();
    }

    GTform::~GTform()
    = default;

    GTform::GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck)
    {
        if(fwd.GetNumCols() != 4 || fwd.GetNumRows() != 4 || bck.GetNumCols() != 4 || bck.GetNumRows() != 4)
        {
            throw std::invalid_argument("Invalid matrix size for GTform");
        }
        m_fwd = fwd;
        m_bck = bck;
    }

    void GTform::SetTransform(qbVector<double>& translate, qbVector<double>& scale, qbVector<double>& rotate)
    {
        qbMatrix2<double> transMat{4, 4};
        qbMatrix2<double> scaleMat{4, 4};
        qbMatrix2<double> rotMatX{4, 4};
        qbMatrix2<double> rotMatY{4, 4};
        qbMatrix2<double> rotMatZ{4, 4};

        transMat.SetToIdentity();
        scaleMat.SetToIdentity();
        rotMatX.SetToIdentity();
        rotMatY.SetToIdentity();
        rotMatZ.SetToIdentity();

        transMat.SetElement(0, 3, translate.GetElement(0));
        transMat.SetElement(1, 3, translate.GetElement(1));
        transMat.SetElement(2, 3, translate.GetElement(2));

        scaleMat.SetElement(0, 0, scale.GetElement(0));
        scaleMat.SetElement(1, 1, scale.GetElement(1));
        scaleMat.SetElement(2, 2, scale.GetElement(2));

        rotMatX.SetElement(1, 1, std::cos(rotate.GetElement(0)));
        rotMatX.SetElement(1, 2, -std::sin(rotate.GetElement(0)));
        rotMatX.SetElement(2, 1, std::sin(rotate.GetElement(0)));

        rotMatY.SetElement(0, 0, std::cos(rotate.GetElement(1)));
        rotMatY.SetElement(0, 2, std::sin(rotate.GetElement(1)));
        rotMatY.SetElement(2, 0, -std::sin(rotate.GetElement(1)));

        rotMatZ.SetElement(0, 0, std::cos(rotate.GetElement(2)));
        rotMatZ.SetElement(0, 1, -std::sin(rotate.GetElement(2)));
        rotMatZ.SetElement(1, 0, std::sin(rotate.GetElement(2)));

        m_fwd = transMat * scaleMat * rotMatX * rotMatY * rotMatZ;
        m_bck = m_fwd;
        m_bck.Inverse();
    }

    qbMatrix2<double> GTform::GetMatrix(bool dir)
    {
        if(dir) return m_fwd;
        else return m_bck;
    }


    Ray GTform::Apply(Ray& ray, bool fwd)
    {
        Ray retRay;
        if(fwd)
        {
            retRay.m_point1 = Apply(ray.m_point1, FWDTFORM);
            retRay.m_point2 = Apply(ray.m_point2, FWDTFORM);
            retRay.m_lab = retRay.m_point2 - retRay.m_point1;
        } else
        {
            retRay.m_point1 = Apply(ray.m_point1, BCKTFORM);
            retRay.m_point2 = Apply(ray.m_point2, BCKTFORM);
            retRay.m_lab = retRay.m_point2 - retRay.m_point1;
        }
        return ray;
    }

    qbVector<double> GTform::Apply(qbVector<double>& vec, bool fwd)
    {
        std::vector<double> temp{vec.GetElement(0), vec.GetElement(1), vec.GetElement(2), 1.0};
        qbVector<double> calcVec{temp};

        qbVector<double> retVec;

        if(fwd)
        {
            retVec = m_fwd * vec;
        } else
        {
            retVec = m_bck * vec;
        }

        qbVector<double> outputVector {std::vector<double> {retVec.GetElement(0), retVec.GetElement(1),
            retVec.GetElement(2) }};

        return outputVector;
    }

    GTform operator*(const GTform& lhs, const GTform& rhs)
    {
        qbMatrix2<double> fwd = lhs.m_fwd * rhs.m_fwd;
        qbMatrix2<double> bck = fwd;
        bck.Inverse();
        return GTform{fwd, bck};
    }

    GTform GTform::operator=(const GTform& rhs)
    {
        if(this != &rhs) {
            m_fwd = rhs.m_fwd;
            m_bck = rhs.m_bck;
        }
        return *this;
    }

    void GTform::PrintMatrix(bool dirFlag)
    {
        if (dirFlag)
        {
            Print(m_fwd);
        }
        else
        {
            Print(m_bck);
        }
    }

    void GTform::Print(const qbMatrix2<double> &matrix)
    {
        int nRows = matrix.GetNumRows();
        int nCols = matrix.GetNumCols();
        for (int row = 0; row<nRows; ++row)
        {
            for (int col = 0; col<nCols; ++col)
            {
                std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(row, col) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Function to print vectors.
    void GTform::PrintVector(const qbVector<double> &inputVector)
    {
        int nRows = inputVector.GetNumDims();
        for (int row = 0; row < nRows; ++row)
        {
            std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
        }
    }


}