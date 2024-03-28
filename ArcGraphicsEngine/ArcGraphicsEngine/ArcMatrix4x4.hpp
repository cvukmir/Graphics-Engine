#pragma once

#ifndef ARCMATRIX4X4_H
#define ARCMATRIX4X4_H

#include "Arc3DPointH.h"

struct ArcMatrix4x4
{
public: // Constructor/Destructor(s) //

	ArcMatrix4x4()
		: matrix{0.0}
	{
	}

	ArcMatrix4x4(const double (m)[4][4])
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int col = 0; col < 4; ++col)
			{
				matrix[row][col] = m[row][col];
			}
		}
	}

	ArcMatrix4x4(const double(&m)[4][4])
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int col = 0; col < 4; ++col)
			{
				matrix[row][col] = m[row][col];
			}
		}
	}




public: // Static Variables //

	static constexpr const double IDENTITY_MATRIX[4][4] =
		{{ 1.0, 0.0, 0.0, 0.0 },
		 { 0.0, 1.0, 0.0, 0.0 },
		 { 0.0, 0.0, 1.0, 0.0 },
		 { 0.0, 0.0, 0.0, 1.0 }};




public: // Operator Overload //

	void operator=(const ArcMatrix4x4& m)
	{
		for (int rowIndex = 0; rowIndex < 4; ++rowIndex)
		{
			for (int columnIndex = 0; columnIndex < 4; ++columnIndex)
			{
				this->matrix[rowIndex][columnIndex] = m.matrix[rowIndex][columnIndex];
			}
		}
	}

	/* In-place matrix multiplication with a 4x4 matrix. */
	ArcMatrix4x4 operator*(const ArcMatrix4x4& m)
	{
		ArcMatrix4x4 newMatrix;

		for (int rowIndex = 0; rowIndex < 4; ++rowIndex)
		{
			for (int columnIndex = 0; columnIndex < 4; ++columnIndex)
			{
				newMatrix.matrix[rowIndex][columnIndex] = dotProduct4x4(this->matrix, m.matrix, rowIndex, columnIndex);
			}
		}

		return newMatrix;
	}

	/* Out-of-place matrix multiplication with a homogenous point, returns a homogenous point. */
	Arc3DPointH operator*(const Arc3DPointH& point)
	{
		return Arc3DPointH(dotProduct4x1(this->matrix, point, 0),  // x
			               dotProduct4x1(this->matrix, point, 1),  // y
			               dotProduct4x1(this->matrix, point, 2),  // z
			               dotProduct4x1(this->matrix, point, 3)); // w
	}





public: // Variables //
	
	double matrix[4][4];




private: // Methods //

	/* The dot product for a single row and column on two 4x4 transformation matrices. */
	double dotProduct4x4(const double pMatrix1[4][4], const double pMatrix2[4][4], const int rowIndex, const int columnIndex)
	{
		double total = 0.0;

		for (int i = 0; i < 4; ++i)
		{
			total += pMatrix1[rowIndex][i] * pMatrix2[i][columnIndex];
		}

		return total;
	}

	/* The dot product for a single row and column on a 4x4 transformation matrix and a 4x1 homogenous point. */
	double dotProduct4x1(const double pMatrix1[4][4], const Arc3DPointH point, const int rowIndex)
	{
		double total = 0.0;

		total += pMatrix1[rowIndex][0] * point.x();
		total += pMatrix1[rowIndex][1] * point.y();
		total += pMatrix1[rowIndex][2] * point.z();
		total += pMatrix1[rowIndex][3] * point.w();

		return total;
	}
};

#endif // !ARCMATRIX4X4_H