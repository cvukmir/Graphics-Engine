
#include <string>

#include "ArcWindow.h"
#include "ArcRdParser.h"
#include "ArcConstants.h"
#include "ArcEnums.h"
#include "ArcRdCommand.h"
#include "Arc2DPoint.h"
#include "Arc2DLine.h"

#include <string>
#include <fstream>
#include <ios>
#include <sstream>
#include <vector>
#include <queue>

#include <Windows.h>

ArcRdParser::ArcRdParser()
	: _displayType(ArcRdDisplayType::Invalid)
	, _displayMode(ArcRdDisplayMode::Invalid)
	, _width (512)
	, _height(512)
{
}

ArcRdParser::~ArcRdParser()
{
	if (isFileOpen())
	{
		closeFile();
	}
}

const ArcRdDisplayMode ArcRdParser::displayMode() const { return _displayMode; }
const std::string      ArcRdParser::displayName() const { return _displayName; }
const ArcRdDisplayType ArcRdParser::displayType() const { return _displayType; }
const int              ArcRdParser::width()       const { return _width;       }
const int              ArcRdParser::height()      const { return _height;      }


const bool ArcRdParser::executeCommands(ArcWindow* pWindow)
{
	while (!_commandQueue.empty())
	{
		ArcRdCommand command = _commandQueue.front();
		switch (command.commandType())
		{
			case ArcRdCommandType::FrameBegin:
				pWindow->frameNumber(std::stoi(command.argumentList().at(0)));
				break;
			case ArcRdCommandType::FrameEnd: break;
			case ArcRdCommandType::WorldBegin: break;
			case ArcRdCommandType::WorldEnd: break;
			case ArcRdCommandType::ObjectBegin: break;
			case ArcRdCommandType::ObjectEnd: break;
			case ArcRdCommandType::ObjectInstance: break;
			case ArcRdCommandType::Background:
				pWindow->fillBackground(ArcColor(std::stof(command.argumentList().at(0)), std::stof(command.argumentList().at(1)), std::stof(command.argumentList().at(2))));
				break;
			case ArcRdCommandType::Color:
				pWindow->currentColor(ArcColor(std::stof(command.argumentList().at(0)), std::stof(command.argumentList().at(1)), std::stof(command.argumentList().at(2))));
				break;
			case ArcRdCommandType::Opacity: break;
			case ArcRdCommandType::OptionArray: break;
			case ArcRdCommandType::OptionBool: break;
			case ArcRdCommandType::Interpolate: break;
			case ArcRdCommandType::Wireframe: break;
			case ArcRdCommandType::OptionList: break;
			case ArcRdCommandType::OptionReal: break;
			case ArcRdCommandType::Sides: break;
			case ArcRdCommandType::OptionString: break;
			case ArcRdCommandType::CameraAt: break;
			case ArcRdCommandType::CameraEye: break;
			case ArcRdCommandType::CameraFOV: break;
			case ArcRdCommandType::CameraUp: break;
			case ArcRdCommandType::Clipping: break;
			case ArcRdCommandType::Point:
				pWindow->drawPoint(Arc2DPoint(std::stoi(command.argumentList().at(0)), std::stoi(command.argumentList().at(1))));
				break;
			case ArcRdCommandType::PointSet: break;
			case ArcRdCommandType::Line:
				pWindow->drawLine(Arc2DPoint(std::stoi(command.argumentList().at(0)), std::stoi(command.argumentList().at(1))), Arc2DPoint(std::stoi(command.argumentList().at(3)), std::stoi(command.argumentList().at(4))));
				break;
			case ArcRdCommandType::LineSet: break;
			case ArcRdCommandType::Circle:
				pWindow->drawCircle(Arc2DPoint(std::stoi(command.argumentList().at(0)), std::stoi(command.argumentList().at(1))), std::stoi(command.argumentList().at(3)));
				break;
			case ArcRdCommandType::Fill:
				pWindow->fill(Arc2DPoint(std::stoi(command.argumentList().at(0)), std::stoi(command.argumentList().at(1))));
				break;
			case ArcRdCommandType::Cone: break;
			case ArcRdCommandType::Cube: break;
			case ArcRdCommandType::Curve: break;
			case ArcRdCommandType::Cylinder: break;
			case ArcRdCommandType::Disk: break;
			case ArcRdCommandType::Hyperboloid: break;
			case ArcRdCommandType::Paraboloid: break;
			case ArcRdCommandType::Patch: break;
			case ArcRdCommandType::PolySet: break;
			case ArcRdCommandType::Sphere: break;
			case ArcRdCommandType::SqSphere: break;
			case ArcRdCommandType::SqTorus: break;
			case ArcRdCommandType::Subdivision: break;
			case ArcRdCommandType::Torus: break;
			case ArcRdCommandType::Tube: break;
			case ArcRdCommandType::Rotate: break;
			case ArcRdCommandType::Scale: break;
			case ArcRdCommandType::Translate: break;
			case ArcRdCommandType::XformPush: break;
			case ArcRdCommandType::XformPop: break;
			case ArcRdCommandType::AmbientLight: break;
			case ArcRdCommandType::FarLight: break;
			case ArcRdCommandType::PointLight: break;
			case ArcRdCommandType::ConeLight: break;
			case ArcRdCommandType::Ka: break;
			case ArcRdCommandType::Kd: break;
			case ArcRdCommandType::Ks: break;
			case ArcRdCommandType::Specular: break;
			case ArcRdCommandType::Surface: break;
			case ArcRdCommandType::MapLoad: break;
			case ArcRdCommandType::Map: break;
			case ArcRdCommandType::MapSample: break;
			case ArcRdCommandType::MapBound: break;
			case ArcRdCommandType::MapBorder: break;

			case ArcRdCommandType::Invalid:
			default:
				continue;
		}

		_commandQueue.pop();
	}

	return true;
}

bool ArcRdParser::readFile()
{
	std::string              buffer;
	std::string              headerLine;
	std::istringstream       tokenizer;
	std::vector<std::string> tokens;
	std::string              commandName;
	int tokenNum = 0;
	std::string hold;
	bool hasHeader = false;

	// Read header
	while (!_stream.eof() && !hasHeader)
	{
		std::getline(_stream, headerLine);
		if (headerLine.starts_with(RD_CMD_DISPLAY))
		{
			for (size_t i = RD_CMD_DISPLAY.length(); i < headerLine.length(); ++i)
			{
				char c = headerLine[i];
				if (c == '\"')
				{
					++i;
					for (;i < headerLine.length() && headerLine[i] != '\"'; ++i)
					{
						hold += headerLine[i];
					}

					switch (tokenNum)
					{
						case 0:
							_displayName = hold;
							break;
						case 1:
							_displayType = displayTypeFromString(hold);
							break;
						case 2:
							_displayMode = displayModeFromString(hold);
							hasHeader = true;
							break;
					}

					++tokenNum;
					hold.clear();
				}
			}
		}
	}

	if (_displayName.empty() || _displayType == ArcRdDisplayType::Invalid || _displayMode == ArcRdDisplayMode::Invalid)
	{
		return false;
	}

	// Read body
	while (!_stream.eof())
	{
		std::getline(_stream, headerLine);
		if (isalnum(headerLine[0]))
		{
			tokenizer = std::istringstream(headerLine);

			tokenizer >> buffer;
			commandName = buffer;

			while (tokenizer >> buffer)
			{
				tokens.push_back(buffer);
			}

			_commandQueue.push(ArcRdCommand(commandTypeFromString(commandName), tokens));
		}
	}

	if (_commandQueue.front().commandType() == ArcRdCommandType::Format)
	{
		if (_commandQueue.front().argumentList().size() != 2)
		{
			return false;
		}

		_width  = std::stoi(_commandQueue.front().argumentList().at(0));
		_height = std::stoi(_commandQueue.front().argumentList().at(1));

		_commandQueue.pop();
	}

	closeFile();

	return true;
}

const bool ArcRdParser::isFileOpen() const
{
	return _stream.is_open();
}

bool ArcRdParser::openFile(const std::string fileName)
{
	if (_fileName.ends_with(".rd"))
	{
		return false;
	}

	_fileName = fileName;

	_stream.open(_fileName);

	if (!isFileOpen() || !readFile())
	{
		return false;
	}

	return true;
}

void ArcRdParser::closeFile()
{
	_stream.close();
}


const ArcRdCommandType ArcRdParser::commandTypeFromString(std::string value)
{
	if      (value == "Display")         { return ArcRdCommandType::Display;         }
	else if (value == "Format")          { return ArcRdCommandType::Format;          }
	else if (value == "FrameBegin")      { return ArcRdCommandType::FrameBegin;      }
	else if (value == "FrameEnd")        { return ArcRdCommandType::FrameEnd;        }
	else if (value == "WorldBegin")      { return ArcRdCommandType::WorldBegin;      }
	else if (value == "WorldEnd")        { return ArcRdCommandType::WorldEnd;        }
	else if (value == "ObjectBegin")     { return ArcRdCommandType::ObjectBegin;     }
	else if (value == "ObjectEnd")       { return ArcRdCommandType::ObjectEnd;       }
	else if (value == "ObjectInstance")  { return ArcRdCommandType::ObjectInstance;  }
	else if (value == "Background")      { return ArcRdCommandType::Background;      }
	else if (value == "Color")           { return ArcRdCommandType::Color;           }
	else if (value == "Opacity")         { return ArcRdCommandType::Opacity;         }
	else if (value == "OptionArray")     { return ArcRdCommandType::OptionArray;     }
	else if (value == "OptionBool")      { return ArcRdCommandType::OptionBool;      }
	else if (value == "Interpolate")     { return ArcRdCommandType::Interpolate;     }
	else if (value == "Wireframe")       { return ArcRdCommandType::Wireframe;       }
	else if (value == "OptionList")      { return ArcRdCommandType::OptionList;      }
	else if (value == "OptionReal")      { return ArcRdCommandType::OptionReal;      }
	else if (value == "Sides")           { return ArcRdCommandType::Sides;           }
	else if (value == "OptionString")    { return ArcRdCommandType::OptionString;    }
	else if (value == "CameraAt")        { return ArcRdCommandType::CameraAt;        }
	else if (value == "CameraEye")       { return ArcRdCommandType::CameraEye;       }
	else if (value == "CameraFOV")       { return ArcRdCommandType::CameraFOV;       }
	else if (value == "CameraUp")        { return ArcRdCommandType::CameraUp;        }
	else if (value == "Clipping")        { return ArcRdCommandType::Clipping;        }
	else if (value == "Point")           { return ArcRdCommandType::Point;           }
	else if (value == "PointSet")        { return ArcRdCommandType::PointSet;        }
	else if (value == "Line")            { return ArcRdCommandType::Line;            }
	else if (value == "LineSet")         { return ArcRdCommandType::LineSet;         }
	else if (value == "Circle")          { return ArcRdCommandType::Circle;          }
	else if (value == "Fill")            { return ArcRdCommandType::Fill;            }
	else if (value == "Cone")            { return ArcRdCommandType::Cone;            }
	else if (value == "Cube")            { return ArcRdCommandType::Cube;            }
	else if (value == "Curve")           { return ArcRdCommandType::Curve;           }
	else if (value == "Cylinder")        { return ArcRdCommandType::Cylinder;        }
	else if (value == "Disk")            { return ArcRdCommandType::Disk;            }
	else if (value == "Hyperboloid")     { return ArcRdCommandType::Hyperboloid;     }
	else if (value == "Paraboloid")      { return ArcRdCommandType::Paraboloid;      }
	else if (value == "Patch")           { return ArcRdCommandType::Patch;           }
	else if (value == "PolySet")         { return ArcRdCommandType::PolySet;         }
	else if (value == "Sphere")          { return ArcRdCommandType::Sphere;          }
	else if (value == "SqSphere")        { return ArcRdCommandType::SqSphere;        }
	else if (value == "SqTorus")         { return ArcRdCommandType::SqTorus;         }
	else if (value == "Subdivision")     { return ArcRdCommandType::Subdivision;     }
	else if (value == "Torus")           { return ArcRdCommandType::Torus;           }
	else if (value == "Tube")            { return ArcRdCommandType::Tube;            }
	else if (value == "Rotate")          { return ArcRdCommandType::Rotate;          }
	else if (value == "Scale")           { return ArcRdCommandType::Scale;           }
	else if (value == "Translate")       { return ArcRdCommandType::Translate;       }
	else if (value == "XformPush")       { return ArcRdCommandType::XformPush;       }
	else if (value == "XformPop")        { return ArcRdCommandType::XformPop;        }
	else if (value == "AmbientLight")    { return ArcRdCommandType::AmbientLight;    }
	else if (value == "FarLight")        { return ArcRdCommandType::FarLight;        }
	else if (value == "PointLight")      { return ArcRdCommandType::PointLight;      }
	else if (value == "ConeLight")       { return ArcRdCommandType::ConeLight;       }
	else if (value == "Ka")              { return ArcRdCommandType::Ka;              }
	else if (value == "Kd")              { return ArcRdCommandType::Kd;              }
	else if (value == "Ks")              { return ArcRdCommandType::Ks;              }
	else if (value == "Specular")        { return ArcRdCommandType::Specular;        }
	else if (value == "Surface")         { return ArcRdCommandType::Surface;         }
	else if (value == "MapLoad")         { return ArcRdCommandType::MapLoad;         }
	else if (value == "Map")             { return ArcRdCommandType::Map;             }
	else if (value == "MapSample")       { return ArcRdCommandType::MapSample;       }
	else if (value == "MapBound")        { return ArcRdCommandType::MapBound;        }
	else if (value == "MapBorder")       { return ArcRdCommandType::MapBorder;       }
	else                                 { return ArcRdCommandType::Invalid;         }
}

const ArcRdDisplayType ArcRdParser::displayTypeFromString(std::string value)
{
	if      (value == "PNM")    { return ArcRdDisplayType::Pnm;     }
	else if (value == "Screen") { return ArcRdDisplayType::Screen;  }
	else                        { return ArcRdDisplayType::Invalid; }
}

const ArcRdDisplayMode ArcRdParser::displayModeFromString(std::string value)
{
	if      (value == "rgbsingle") { return ArcRdDisplayMode::RGBSingle; }
	else if (value == "rgbobject") { return ArcRdDisplayMode::RGBObject; }
	else if (value == "rgbdouble") { return ArcRdDisplayMode::RGBDouble; }
	else if (value == "rgb")       { return ArcRdDisplayMode::RGB;       }
	else                           { return ArcRdDisplayMode::Invalid;   }
}