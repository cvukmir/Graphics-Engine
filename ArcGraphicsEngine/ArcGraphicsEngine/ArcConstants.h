#pragma once

#include <windows.h>
#include <string>

// Windows Window
const LPCWSTR WINDOW_CLASS = L"ArcEngineClass";
const LPCWSTR WINDOW_TITLE = L"ArcEngine";

const bool PARSE_COMMAND_LINE = true;



const int INITIAL_WIDTH = 1920;
const int INITIAL_HEIGHT = 1080;

// PNM File
const std::string PNM_HEADER        = "P6";
const int         PNM_MAX_INTENSITY = 255;

// RD File Parameter Strings
const std::string RD_PARAM_DISPLAY_TYPE_SCREEN     = "Screen";
const std::string RD_PARAM_DISPLAY_TYPE_PNM        = "PNM";
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
//const std::string RD_CMD_
//const std::string RD_CMD_
//const std::string RD_CMD_
//const std::string RD_CMD_