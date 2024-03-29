// ArcGeometry
#include "ArcTransformMatrixH.h"
#include "Arc3DPointH.h"
#include <numbers>

#include "ArcMatrix4x4.hpp"

#include <math.h>


// Constructor/Destructor(s) //

ArcTransformMatrixH::ArcTransformMatrixH()
{
}

ArcTransformMatrixH::ArcTransformMatrixH(const double matrix[4][4])
	: _matrix(matrix)
{
}

ArcTransformMatrixH::ArcTransformMatrixH(const ArcMatrix4x4& matrix)
	: _matrix(matrix)
{
}

ArcTransformMatrixH::~ArcTransformMatrixH()
{
}


// Overload(s) //

void ArcTransformMatrixH::operator*(const ArcTransformMatrixH& transform)
{
	this->_matrix = this->_matrix * transform._matrix;
}

Arc3DPointH ArcTransformMatrixH::operator*(const Arc3DPointH& point)
{
	return this->_matrix * point;
}




// Public Methods - Static //

Arc3DPointH ArcTransformMatrixH::camera_to_clip(const Arc3DPointH& point, const double fov, const double nearDis, const double farDis, const double aspect)
{
	///////////////////////////////////////////////////////////////////////////////////
	// 1/(2*aspect*tan(theta/2))         0            1/2                0           //
	//           0               1/(2*tan(theta/2))   1/2                0           // * this
	//           0                       0          far/near  -(far*near)/(far-near) //
	//           0                       0             1                 0           //
	///////////////////////////////////////////////////////////////////////////////////

	const double thetaRad = (fov * std::numbers::pi) / 180;

	ArcMatrix4x4 cameraToClipMatrix(
		{{ 1.0 / (2.0 * aspect * tan(thetaRad / 2.0)),           0.0,                      0.5,                          0.0},
		 {           0.0,                         1.0 / (2.0 * tan(thetaRad / 2.0)),       0.5,                          0.0                  },
		 {           0.0,                                   0.0,                farDis / (farDis - nearDis), -(farDis * nearDis) / (farDis - nearDis)},
		 {           0.0,                                   0.0,                      1.0,                          0.0                  }});

	return cameraToClipMatrix * point;
}

Arc3DPointH ArcTransformMatrixH::clip_to_device(const Arc3DPointH& point, const int width, const int height)
{
	//////////////////////////////////////
	// Width - e       0       0   0    //
	//   0       -(Height - e) 0 Height // * this
	//   0             0       1   0    //
	//   0             0       0   1    //
	//////////////////////////////////////

	const double e = 0.00001;

	ArcMatrix4x4 clipToDeviceMatrix(
		{{ (double)width - e,              0.0,      0.0,          0.0   },
		 {          0.0,      -(double)(height - e), 0.0, (double)height },
		 {          0.0,                   0.0,      1.0,          0.0   },
		 {          0.0,                   0.0,      0.0,          1.0   }});

	return clipToDeviceMatrix * point;
}

Arc3DPointH ArcTransformMatrixH::world_to_camera(const Arc3DPointH& point, const Arc3DPoint& eye, const Arc3DPoint& at, const ArcVector& up)
{
	////////////////   ///////////////
	// Ux Uy Uz 0 //   // 1 0 0 -Ex //
	// Vx Vy Vz 0 // * // 0 1 0 -Ey // * this
	// Ax Ay Az 0 //   // 0 0 1 -Ez //
	// 0  0  0  1 //   // 0 0 0  1  //
	////////////////   ///////////////

	// Step 1 -> Get vector from eye to look point
	ArcVector A(at, eye);

	// Step 2 -> Normalize to scale of 1
	A.normalize();

	// Step 3 -> Cross product A and up direction
	ArcVector U = A.crossProduct(up);

	// Step 4 -> Normalize U
	U.normalize();

	// Step 5 -> Cross product A with U
	ArcVector V = U.crossProduct(A);

	// Step 6 -> Normalize V (OPTIONAL)
	V.normalize();

	ArcMatrix4x4 worldToCameraRotation(
		{{ U.x(), U.y(), U.z(), 0.0 },
		 { V.x(), V.y(), V.z(), 0.0 },
		 { A.x(), A.y(), A.z(), 0.0 },
		 { 0.0,   0.0,   0.0,   1.0 }});

	ArcMatrix4x4 worldToCameraTranslation(
		{{ 1.0, 0.0, 0.0, -eye.x() },
		 { 0.0, 1.0, 0.0, -eye.y() },
		 { 0.0, 0.0, 1.0, -eye.z() },
		 { 0.0, 0.0, 0.0,     1.0  }});

	return (worldToCameraRotation * worldToCameraTranslation) * point;
}




// Public Methods - Instance //

void ArcTransformMatrixH::rotate_xy(const double theta)
{
	//////////////////////////////////////
	// cos(theta) | -sin(theta) | 0 | 0 //
	// sin(theta) |  cos(theta) | 0 | 0 // * this
	//      0     |       0     | 1 | 0 //
	//      0     |       0     | 0 | 1 //
	//////////////////////////////////////

	const double thetaRad = (theta * std::numbers::pi) / 180;

	ArcMatrix4x4 rotationMatrixXY(
		{{ cos(thetaRad), -(sin(thetaRad)), 0.0, 0.0 },
		 { sin(thetaRad),   cos(thetaRad),  0.0, 0.0 },
		 {    0.0,          0.0,      1.0, 0.0 },
		 {    0.0,          0.0,      0.0, 1.0 }});

	_matrix = _matrix * rotationMatrixXY;
}

void ArcTransformMatrixH::rotate_yz(const double theta)
{
	//////////////////////////////////////
	// 1 |      0     |      0      | 0 //
	// 0 | cos(theta) | -sin(theta) | 0 // * this
	// 0 | sin(theta) |  cos(theta) | 0 //
	// 0 |      0     |      0      | 1 //
	//////////////////////////////////////

	const double thetaRad = (theta * std::numbers::pi) / 180;

	ArcMatrix4x4 rotationMatrixYZ(
		{{ 1.0,    0.0,          0.0,      0.0 },
		 { 0.0, cos(thetaRad), -(sin(thetaRad)), 0.0 },
		 { 0.0, sin(thetaRad),   cos(thetaRad),  0.0 },
		 { 0.0,    0.0,          0.0,      1.0 }});

	_matrix = _matrix * rotationMatrixYZ;
}

void ArcTransformMatrixH::rotate_zx(const double theta)
{
	//////////////////////////////////////
	//  cos(theta) | 0 | sin(theta) | 0 //
	//       0     | 1 |      0     | 0 // * this
	// -sin(theta) | 0 | cos(theta) | 0 //
	//       0     | 0 |      0     | 1 //
	//////////////////////////////////////

	const double thetaRad = (theta * std::numbers::pi) / 180;

	ArcMatrix4x4 rotationMatrixZX(
		{{   cos(thetaRad),  0.0, sin(thetaRad), 0.0 },
		 {      0.0,      1.0,    0.0,     0.0 },
		 { -(sin(thetaRad)), 0.0, cos(thetaRad), 0.0 },
		 {      0.0,      0.0,    0.0,     1.0 }});

	_matrix = _matrix * rotationMatrixZX;
}

void ArcTransformMatrixH::scale(const double sx, const double sy, const double sz)
{
	////////////////
	// Sx 0  0  0 //
	// 0  Sy 0  0 // * this
	// 0  0  Sz 0 //
	// 0  0  0  1 //
	////////////////

	ArcMatrix4x4 rotationMatrixZX(
		{{ sx,  0.0, 0.0, 0.0 },
		 { 0.0, sy,  0.0, 0.0 },
		 { 0.0, 0.0, sz,  0.0 },
		 { 0.0, 0.0, 0.0, 1.0 }});

	_matrix = _matrix * rotationMatrixZX;
}

void ArcTransformMatrixH::translate(const double tx, const double ty, const double tz)
{
	//////////////
	// 1 0 0 Tx //
	// 0 1 0 Ty // * this
	// 0 0 1 Tz //
	// 0 0 0 1  //
	//////////////

	ArcMatrix4x4 translationMatrix(
		{{ 1.0, 0.0, 0.0, tx  },
		 { 0.0, 1.0, 0.0, ty  },
		 { 0.0, 0.0, 1.0, tz  },
		 { 0.0, 0.0, 0.0, 1.0 }});

	_matrix = _matrix * translationMatrix;
}