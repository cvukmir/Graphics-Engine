#pragma once

#ifndef ARCRDCOMMAND_H
#define ARCRDCOMMAND_H

#include <vector>
#include <string>
#include "ArcConstants.h"
#include "ArcEnums.h"

struct ArcRdCommand
{
public:

	ArcRdCommand(std::string type, std::vector<std::string>& list)
	{
		_commandType  = commandTypeFromString(type);
		_argumentList = std::move(list);
	}

	const int                       commandType() const { return _commandType;  }
	const std::vector<std::string> argumentList() const { return _argumentList; }

public: // Virtual methods
	const int commandTypeFromString(std::string command)
	{
		if      (command == "Display")         { _commandType = ArcRdCommandType::Display;         }
		else if (command == "Format")          { _commandType = ArcRdCommandType::Format;          }
		else if (command == "FrameBegin")      { _commandType = ArcRdCommandType::FrameBegin;      }
		else if (command == "FrameEnd")        { _commandType = ArcRdCommandType::FrameEnd;        }
		else if (command == "WorldBegin")      { _commandType = ArcRdCommandType::WorldBegin;      }
		else if (command == "WorldEnd")        { _commandType = ArcRdCommandType::WorldEnd;        }
		else if (command == "ObjectBegin")     { _commandType = ArcRdCommandType::ObjectBegin;     }
		else if (command == "ObjectEnd")       { _commandType = ArcRdCommandType::ObjectEnd;       }
		else if (command == "ObjectInstance")  { _commandType = ArcRdCommandType::ObjectInstance;  }
		else if (command == "Background")      { _commandType = ArcRdCommandType::Background;      }
		else if (command == "Color")           { _commandType = ArcRdCommandType::Color;           }
		else if (command == "Opacity")         { _commandType = ArcRdCommandType::Opacity;         }
		else if (command == "OptionArray")     { _commandType = ArcRdCommandType::OptionArray;     }
		else if (command == "OptionBool")      { _commandType = ArcRdCommandType::OptionBool;      }
		else if (command == "Interpolate")     { _commandType = ArcRdCommandType::Interpolate;     }
		else if (command == "Wireframe")       { _commandType = ArcRdCommandType::Wireframe;       }
		else if (command == "OptionList")      { _commandType = ArcRdCommandType::OptionList;      }
		else if (command == "OptionReal")      { _commandType = ArcRdCommandType::OptionReal;      }
		else if (command == "Sides")           { _commandType = ArcRdCommandType::Sides;           }
		else if (command == "OptionString")    { _commandType = ArcRdCommandType::OptionString;    }
		else if (command == "CameraAt")        { _commandType = ArcRdCommandType::CameraAt;        }
		else if (command == "CameraEye")       { _commandType = ArcRdCommandType::CameraEye;       }
		else if (command == "CameraFOV")       { _commandType = ArcRdCommandType::CameraFOV;       }
		else if (command == "CameraUp")        { _commandType = ArcRdCommandType::CameraUp;        }
		else if (command == "Clipping")        { _commandType = ArcRdCommandType::Clipping;        }
		else if (command == "Point")           { _commandType = ArcRdCommandType::Point;           }
		else if (command == "PointSet")        { _commandType = ArcRdCommandType::PointSet;        }
		else if (command == "Line")            { _commandType = ArcRdCommandType::Line;            }
		else if (command == "LineSet")         { _commandType = ArcRdCommandType::LineSet;         }
		else if (command == "Circle")          { _commandType = ArcRdCommandType::Circle;          }
		else if (command == "Fill")            { _commandType = ArcRdCommandType::Fill;            }
		else if (command == "Cone")            { _commandType = ArcRdCommandType::Cone;            }
		else if (command == "Cube")            { _commandType = ArcRdCommandType::Cube;            }
		else if (command == "Curve")           { _commandType = ArcRdCommandType::Curve;           }
		else if (command == "Cylinder")        { _commandType = ArcRdCommandType::Cylinder;        }
		else if (command == "Disk")            { _commandType = ArcRdCommandType::Disk;            }
		else if (command == "Hyperboloid")     { _commandType = ArcRdCommandType::Hyperboloid;     }
		else if (command == "Paraboloid")      { _commandType = ArcRdCommandType::Paraboloid;      }
		else if (command == "Patch")           { _commandType = ArcRdCommandType::Patch;           }
		else if (command == "PolySet")         { _commandType = ArcRdCommandType::PolySet;         }
		else if (command == "Sphere")          { _commandType = ArcRdCommandType::Sphere;          }
		else if (command == "SqSphere")        { _commandType = ArcRdCommandType::SqSphere;        }
		else if (command == "SqTorus")         { _commandType = ArcRdCommandType::SqTorus;         }
		else if (command == "Subdivision")     { _commandType = ArcRdCommandType::Subdivision;     }
		else if (command == "Torus")           { _commandType = ArcRdCommandType::Torus;           }
		else if (command == "Tube")            { _commandType = ArcRdCommandType::Tube;            }
		else if (command == "Rotate")          { _commandType = ArcRdCommandType::Rotate;          }
		else if (command == "Scale")           { _commandType = ArcRdCommandType::Scale;           }
		else if (command == "Translate")       { _commandType = ArcRdCommandType::Translate;       }
		else if (command == "XformPush")       { _commandType = ArcRdCommandType::XformPush;       }
		else if (command == "XformPop")        { _commandType = ArcRdCommandType::XformPop;        }
		else if (command == "AmbientLight")    { _commandType = ArcRdCommandType::AmbientLight;    }
		else if (command == "FarLight")        { _commandType = ArcRdCommandType::FarLight;        }
		else if (command == "PointLight")      { _commandType = ArcRdCommandType::PointLight;      }
		else if (command == "ConeLight")       { _commandType = ArcRdCommandType::ConeLight;       }
		else if (command == "Ka")              { _commandType = ArcRdCommandType::Ka;              }
		else if (command == "Kd")              { _commandType = ArcRdCommandType::Kd;              }
		else if (command == "Ks")              { _commandType = ArcRdCommandType::Ks;              }
		else if (command == "Specular")        { _commandType = ArcRdCommandType::Specular;        }
		else if (command == "Surface")         { _commandType = ArcRdCommandType::Surface;         }
		else if (command == "MapLoad")         { _commandType = ArcRdCommandType::MapLoad;         }
		else if (command == "Map")             { _commandType = ArcRdCommandType::Map;             }
		else if (command == "MapSample")       { _commandType = ArcRdCommandType::MapSample;       }
		else if (command == "MapBound")        { _commandType = ArcRdCommandType::MapBound;        }
		else if (command == "MapBorder")       { _commandType = ArcRdCommandType::MapBorder;       }
		else                                   { _commandType = ArcRdCommandType::Invalid;         }
	}

private:

	int                      _commandType;
	std::vector<std::string> _argumentList;
};

#endif // !ARCRDCOMMAND_H