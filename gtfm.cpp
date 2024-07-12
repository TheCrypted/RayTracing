//
// Created by Aman's Laptop on 07-07-2024.
//

#include "include/gtfm.h"
#include "include/ray.h"

qbRT::GTform::GTform()
{
	m_fwd.SetToIdentity();
	m_bck.SetToIdentity();
}

qbRT::GTform::~GTform()
{

}

qbRT::GTform::GTform(const qbVector<double> &translate, const qbVector<double> &rotate, const qbVector<double> &scale)
{
	SetTransform(translate, rotate, scale);
}


qbRT::GTform::GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck)
{
	if (	(fwd.GetNumRows() != 4) || (fwd.GetNumCols() != 4) ||
		(bck.GetNumRows() != 4) || (bck.GetNumCols() != 4))
	{
		throw std::invalid_argument("Cannot construct GTform, inputs are not all 4x4.");
	}

	m_fwd = fwd;
	m_bck = bck;
}

void qbRT::GTform::SetTransform(const qbVector<double> &translation, const qbVector<double> &rotation,
	const qbVector<double> &scale)
{
	qbMatrix2<double> translationMatrix	{4, 4};
	qbMatrix2<double> rotationMatrixX	{4, 4};
	qbMatrix2<double>	rotationMatrixY	{4, 4};
	qbMatrix2<double> rotationMatrixZ	{4, 4};
	qbMatrix2<double>	scaleMatrix	{4, 4};

	translationMatrix.SetToIdentity();
	rotationMatrixX.SetToIdentity();
	rotationMatrixY.SetToIdentity();
	rotationMatrixZ.SetToIdentity();
	scaleMatrix.SetToIdentity();

	translationMatrix.SetElement(0, 3, translation.GetElement(0));
	translationMatrix.SetElement(1, 3, translation.GetElement(1));
	translationMatrix.SetElement(2, 3, translation.GetElement(2));

	rotationMatrixZ.SetElement(0, 0, cos(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(0, 1, -sin(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(1, 0, sin(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(1, 1, cos(rotation.GetElement(2)));

	rotationMatrixY.SetElement(0, 0, cos(rotation.GetElement(1)));
	rotationMatrixY.SetElement(0, 2, sin(rotation.GetElement(1)));
	rotationMatrixY.SetElement(2, 0, -sin(rotation.GetElement(1)));
	rotationMatrixY.SetElement(2, 2, cos(rotation.GetElement(1)));

	rotationMatrixX.SetElement(1, 1, cos(rotation.GetElement(0)));
	rotationMatrixX.SetElement(1, 2, -sin(rotation.GetElement(0)));
	rotationMatrixX.SetElement(2, 1, sin(rotation.GetElement(0)));
	rotationMatrixX.SetElement(2, 2, cos(rotation.GetElement(0)));

	scaleMatrix.SetElement(0, 0, scale.GetElement(0));
	scaleMatrix.SetElement(1, 1, scale.GetElement(1));
	scaleMatrix.SetElement(2, 2, scale.GetElement(2));

	m_fwd =	translationMatrix *
			rotationMatrixX *
			rotationMatrixY *
			rotationMatrixZ *
			scaleMatrix;

	m_bck = m_fwd;
	m_bck.Inverse();

}

qbMatrix2<double> qbRT::GTform::GetMatrix(bool dir)
{
	if(dir)
	{
		return m_fwd;
	} else
	{
		return m_bck;
	}
}


qbRT::Ray qbRT::GTform::Apply(const qbRT::Ray &inputRay, bool dirFlag)
{
	qbRT::Ray outputRay;

	if (dirFlag)
	{
		outputRay.m_point1 = this -> Apply(inputRay.m_point1, qbRT::FWDTFORM);
		outputRay.m_point2 = this -> Apply(inputRay.m_point2, qbRT::FWDTFORM);
		outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
	}
	else
	{
		outputRay.m_point1 = this -> Apply(inputRay.m_point1, qbRT::BCKTFORM);
		outputRay.m_point2 = this -> Apply(inputRay.m_point2, qbRT::BCKTFORM);
		outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
	}

	return outputRay;
}

qbVector<double> qbRT::GTform::Apply(const qbVector<double> &inputVector, bool dirFlag)
{
	std::vector<double> tempData {	inputVector.GetElement(0),
					inputVector.GetElement(1),
					inputVector.GetElement(2),
					1.0 };
	qbVector<double> tempVector {tempData};

	qbVector<double> resultVector;

	if (dirFlag)
	{
		resultVector = m_fwd * tempVector;
	}
	else
	{
		resultVector = m_bck * tempVector;
	}

	qbVector<double> outputVector {std::vector<double> {	resultVector.GetElement(0),
								resultVector.GetElement(1),
								resultVector.GetElement(2) }};

	return outputVector;
}

// Overload operators.
namespace qbRT
{
	qbRT::GTform operator* (const qbRT::GTform &lhs, const qbRT::GTform &rhs)
	{
		qbMatrix2<double> fwdResult = lhs.m_fwd * rhs.m_fwd;

		qbMatrix2<double> bckResult = fwdResult;
		bckResult.Inverse();

		qbRT::GTform finalResult (fwdResult, bckResult);

		return finalResult;
	}
}

qbRT::GTform qbRT::GTform::operator= (const qbRT::GTform &rhs)
{
	if (this != &rhs)
	{
		m_fwd = rhs.m_fwd;
		m_bck = rhs.m_bck;
	}

	return *this;
}

void qbRT::GTform::PrintMatrix(bool dirFlag)
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

void qbRT::GTform::Print(const qbMatrix2<double> &matrix)
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

void qbRT::GTform::PrintVector(const qbVector<double> &inputVector)
{
	int nRows = inputVector.GetNumDims();
	for (int row = 0; row < nRows; ++row)
	{
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
	}
}