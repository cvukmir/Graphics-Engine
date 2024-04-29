#pragma once

#ifndef ARCTRANSFORMMATRIXH_H
#define ARCTRANSFORMMATRIXH_H

#include "Arc3DPointH.h"
#include "Arc3DPoint.h"
#include "ArcVector.h"

#include "ArcMatrix4x4.hpp"

class ArcTransformMatrixH
{
public: // Constructor/Destructor(s) //

	ArcTransformMatrixH();
	ArcTransformMatrixH(const double matrix[4][4]);
	ArcTransformMatrixH(const ArcMatrix4x4& matrix);

	~ArcTransformMatrixH();


public: // Overload(s) //

	void operator*(const ArcTransformMatrixH& matrix);
	Arc3DPointH operator*(const Arc3DPointH& point);
	ArcVector operator*(const ArcVector& vector);

public: // Methods - Static //

	/* Transforms this matrix using the camera to clip transformation. */
	static Arc3DPointH camera_to_clip(const Arc3DPointH& point, const double fov, const double nearDis, const double farDis, const double aspect);

	/* Transforms this matrix using the clip to device transformation. */
	static Arc3DPointH clip_to_device(const Arc3DPointH& point, const int width, const int height);

	/* Transforms this matrix using the world to camera transformation. */
	static Arc3DPointH world_to_camera(const Arc3DPointH& point, const Arc3DPoint& eye, const Arc3DPoint& at, const ArcVector& up);

	/* Rotates this matrix on the xy plane. */
	static ArcTransformMatrixH rotateXYMatrix(const double theta);

	/* Rotates this matrix on the xy plane. */
	static ArcTransformMatrixH rotateXYInverseMatrix(const double theta);

	/* Rotates this matrix on the yz plane. */
	static ArcTransformMatrixH rotateYZMatrix(const double theta);

	/* Rotates this matrix on the yz plane. */
	static ArcTransformMatrixH rotateYZInverseMatrix(const double theta);

	/* Rotates this matrix on the zx plane. */
	static ArcTransformMatrixH rotateZXMatrix(const double theta);

	/* Rotates this matrix on the zx plane. */
	static ArcTransformMatrixH rotateZXInverseMatrix(const double theta);

	/* Scales this matrix by the given values. */
	static ArcTransformMatrixH scaleMatrix(const double sx, const double sy, const double sz);

	/* Scales this matrix by the given values. */
	static ArcTransformMatrixH scaleInverseMatrix(const double sx, const double sy, const double sz);

	/* Translates this matrix by the given values. */
	static ArcTransformMatrixH translateMatrix(const double tx, const double ty, const double tz);

	/* Translates this matrix by the given values. */
	static ArcTransformMatrixH translateInverseMatrix(const double tx, const double ty, const double tz);


public: // Methods - Instance//

	/* Rotates this matrix on the xy plane. */
	void rotateXY(const double theta);

	/* Rotates this matrix on the xy plane. */
	void rotateXYInverse(const double theta);

	/* Rotates this matrix on the yz plane. */
	void rotateYZ(const double theta);

	/* Rotates this matrix on the yz plane. */
	void rotateYZInverse(const double theta);

	/* Rotates this matrix on the zx plane. */
	void rotateZX(const double theta);

	/* Rotates this matrix on the zx plane. */
	void rotateZXInverse(const double theta);

	/* Scales this matrix by the given values. */
	void scale(const double sx, const double sy, const double sz);

	/* Scales this matrix by the given values. */
	void scaleInverse(const double sx, const double sy, const double sz);

	/* Translates this matrix by the given values. */
	void translate(const double tx, const double ty, const double tz);

	/* Translates this matrix by the given values. */
	void translateInverse(const double tx, const double ty, const double tz);


private: // Variables //

	ArcMatrix4x4 _matrix; // A 4x4 transformation matrix
};

#endif // !ARCTRANSFORMMATRIXH_H
