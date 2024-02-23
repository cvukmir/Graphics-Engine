#pragma once

#ifndef ARCENUMS_H
#define ARCENUMS_H


enum ArcIOState
{
	Read  =  0,
	Write =  1,
};

enum ArcPnmType
{
	P1    = 0,
	P2    = 0,
	P3    = 0,
	P4    = 0,
	P5    = 0,
	P6    = 0,
};

enum ArcRdDisplayType
{
	Screen = 0,
	Pnm    = 1
};

enum ArcRdDisplayMode
{
	RGBSingle = 0,
	RGBObject = 1,
	RGBDouble = 2
};

enum ArcRdCommandType
{
	Invalid = -1,
	Display,
	Format,
	FrameBegin,
	FrameEnd,
	WorldBegin,
	WorldEnd,
	ObjectBegin,
	ObjectEnd,
	ObjectInstance,
	Background,
	Color,
	Opacity,
	OptionArray,
	OptionBool,
	Interpolate,
	Wireframe,
	OptionList,
	OptionReal,
	Sides,
	OptionString,
	CameraAt,
	CameraEye,
	CameraFOV,
	CameraUp,
	Clipping,
	// VERTEX TYPES???
	Point,
	PointSet,
	Line,
	LineSet,
	Circle,
	Fill,
	Cone,
	Cube,
	Curve,
	Cylinder,
	Disk,
	Hyperboloid,
	Paraboloid,
	Patch,
	PolySet,
	Sphere,
	SqSphere,
	SqTorus,
	Subdivision,
	Torus,
	Tube,
	Rotate,
	Scale,
	Translate,
	XformPush,
	XformPop,
	AmbientLight,
	FarLight,
	PointLight,
	ConeLight,
	Ka,
	Kd,
	Ks,
	Specular,
	Surface,
	MapLoad,
	Map,
	MapSample,
	MapBound,
	MapBorder,
};

#endif // !ARCENUMS_H
