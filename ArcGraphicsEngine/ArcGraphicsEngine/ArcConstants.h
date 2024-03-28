#pragma once

#ifndef ARCCONSTANTS_H
#define ARCCONSTANTS_H

// Windows
#include <windows.h>

// Stdlib
#include <string>


// Windows Window
const LPCWSTR WINDOW_CLASS = L"ArcEngineClass";
const LPCWSTR WINDOW_TITLE = L"ArcEngine";

// PNM File
const std::string PNM_HEADER        = "P6";
const int         PNM_MAX_INTENSITY = 255;

// RD File Parameter Strings
const std::string RD_PARAM_DISPLAY_TYPE_SCREEN     = "Screen";
const std::string RD_PARAM_DISPLAY_TYPE_PNM        = "PNM";
const std::string RD_PARAM_DISPLAY_TYPE_RGB        = "rgb";
const std::string RD_PARAM_DISPLAY_MODE_RGB_SINGLE = "rgbsingle";
const std::string RD_PARAM_DISPLAY_MODE_RGB_OBJECT = "rgbobject";
const std::string RD_PARAM_DISPLAY_MODE_RGB_DOUBLE = "rgbdouble";

// RD File Commands
const std::string RD_CMD_DISPLAY         = "Display";
const std::string RD_CMD_FORMAT          = "Format";
const std::string RD_CMD_FRAME_BEGIN     = "FrameBegin";
const std::string RD_CMD_FRAME_END       = "FrameEnd";
const std::string RD_CMD_WORLD_BEGIN     = "WorldBegin";
const std::string RD_CMD_WORLD_END       = "WorldEnd";
const std::string RD_CMD_OBJECT_BEGIN    = "ObjectBegin";
const std::string RD_CMD_OBJECT_END      = "ObjectEnd";
const std::string RD_CMD_OBJECT_INSTANCE = "ObjectInstance";
const std::string RD_CMD_BACKGROUND      = "Background";
const std::string RD_CMD_COLOR           = "Color";
const std::string RD_CMD_OPACITY         = "Opacity";
const std::string RD_CMD_OPTION_ARRAY    = "OptionArray";
const std::string RD_CMD_OPTION_BOOL     = "OptionBool";
const std::string RD_CMD_OPTION_LIST     = "OptionList";
const std::string RD_CMD_OPTION_REAL     = "OptionReal";
const std::string RD_CMD_OPTION_STRING   = "OptionString";
const std::string RD_CMD_CAMERA_AT       = "CameraAt";
const std::string RD_CMD_CAMERA_EYE      = "CameraEye";
const std::string RD_CMD_CAMERA_FOV      = "CameraFOV";
const std::string RD_CMD_CAMERA_UP       = "CameraUp";
const std::string RD_CMD_CLIPPING        = "Clipping";
const std::string RD_CMD_POINT           = "Point";
const std::string RD_CMD_POINT_SET       = "PointSet";
const std::string RD_CMD_LINE            = "Line";
const std::string RD_CMD_LINE_SET        = "LineSet";
const std::string RD_CMD_CIRCLE          = "Circle";
const std::string RD_CMD_FILL            = "Fill";
const std::string RD_CMD_CONE            = "Cone";
const std::string RD_CMD_CUBE            = "Cube";
const std::string RD_CMD_CURVE           = "Curve";
const std::string RD_CMD_CYLINDER        = "Cylinder";
const std::string RD_CMD_DISK            = "Disk";
const std::string RD_CMD_HYPERBOLOID     = "Hyperboloid";
const std::string RD_CMD_PARABOLOID      = "Paraboloid";
const std::string RD_CMD_PATCH           = "Patch";
const std::string RD_CMD_POLYSET         = "PolySet";
const std::string RD_CMD_SPHERE          = "Sphere";
const std::string RD_CMD_SQ_SPHERE       = "SqSphere";
const std::string RD_CMD_SQ_TORUS        = "SqTorus";
const std::string RD_CMD_SUBDIVISION     = "Subdivision";
const std::string RD_CMD_TORUS           = "Torus";
const std::string RD_CMD_TUBE            = "Tube";
const std::string RD_CMD_ROTATE          = "Rotate";
const std::string RD_CMD_SCALE           = "Scale";
const std::string RD_CMD_TRANSLATE       = "Translate";
const std::string RD_CMD_XFORM_PUSH      = "XformPush";
const std::string RD_CMD_XFORM_POP       = "XformPop";
const std::string RD_CMD_AMBIENT_LIGHT   = "AmbientLight";
const std::string RD_CMD_FAR_LIGHT       = "FarLight";
const std::string RD_CMD_POINT_LIGHT     = "PointLight";
const std::string RD_CMD_CONE_LIGHT      = "ConeLight";
const std::string RD_CMD_KA              = "Ka";
const std::string RD_CMD_KD              = "Kd";
const std::string RD_CMD_KS              = "Ks";
const std::string RD_CMD_SPECULAR        = "Specular";
const std::string RD_CMD_SURFACE         = "Surface";
const std::string RD_CMD_MAP_LOAD        = "MapLoad";
const std::string RD_CMD_MAP             = "Map";
const std::string RD_CMD_MAP_SAMPLE      = "MapSample";
const std::string RD_CMD_MAP_BOUND       = "MapBound";
const std::string RD_CMD_MAP_BORDER      = "MapBorder";


































#endif // !ARCCONSTANTS_H