#pragma once

#ifndef ARCENUMS_H
#define ARCENUMS_H


enum class ArcIOState
{
	Read  =  0,
	Write =  1,
};

enum class ArcPnmType
{
	Invalid = -1,
	P1      =  1,
	P2      =  2,
	P3      =  3,
	P4      =  4,
	P5      =  5,
	P6      =  6,
};

enum class ArcRdDisplayType
{
	Invalid = -1,
	Screen  =  0,
	Pnm     =  1
};

enum class ArcRdDisplayMode
{
	Invalid   = -1,
	RGBSingle =  0,
	RGBObject =  1,
	RGBDouble =  2,
	RGB       =  3
};

enum class ArcRdCommandType
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
