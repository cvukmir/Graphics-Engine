#pragma once

#ifndef ARCENUMS_H
#define ARCENUMS_H

// Which PNM file magic that is being read/wrote.
enum class ArcPnmType
{
	Invalid = -1,
	P1      =  1, // ASCII  Black and White
	P2      =  2, // Binary Grayscale
	P3      =  3, // ASCII  Color
	P4      =  4, // Binary Black and White
	P5      =  5, // ASCII  Grayscale
	P6      =  6, // Binary Color
};

// The display the rd file is targeting.
enum class ArcRdDisplayType
{
	Invalid = -1,
	Screen  =  0,
	Pnm     =  1,
};

// The mode the rd file is targeting.
enum class ArcRdDisplayMode
{
	Invalid   = -1,
	RGBSingle =  0, // Screen
	RGBObject =  1, // Screen
	RGBDouble =  2, // Screen
	RGB       =  3, // PNM
};

//
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

enum class VertexTypes
{
	Position  = 0b00000001,
	Direction = 0b00000010,
	Normal    = 0b00000100,
	Color     = 0b00001000,
	Weight    = 0b00010000,
	Texture   = 0b00100000,
	Opacity   = 0b01000000,
	Last      = 0b10000000,
};

enum class PlaneType
{
	XY = 0,
	YZ = 1,
	ZX = 2,
};

enum class BoundaryType
{
	First = 0,
	Left = 0,
	Right,
	Top,
	Bottom,
	Front,
	Back,
	Last = Back,
};

#endif // !ARCENUMS_H