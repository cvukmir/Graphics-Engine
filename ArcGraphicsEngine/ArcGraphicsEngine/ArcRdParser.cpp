// Stdlib
#include <string>
#include <fstream>
#include <ios>
#include <sstream>
#include <vector>
#include <queue>

// Windows
#include <Windows.h>

// ArcMain
#include "ArcWindow.h"
#include "ArcRdParser.h"
#include "ArcConstants.h"
#include "ArcEnums.h"
#include "ArcRdCommand.hpp"
#include "Arc2DPoint.h"
#include "Arc2DLine.h"
#include "Arc3DLine.h"


// Public Constructor/Destructor(s) //

ArcRdParser::ArcRdParser()
	: _displayType(ArcRdDisplayType::Invalid)
	, _displayMode(ArcRdDisplayMode::Invalid)
	, _height     (512)
	, _width      (512)
{
}

ArcRdParser::~ArcRdParser()
{
	if (isFileOpen())
	{
		closeFile();
	}

	for (std::vector<ArcRdObject*>::iterator it = _objectList.begin(); it != _objectList.end(); ++it)
	{
		delete(*it);
	}
}


// Public Properties //

const ArcRdDisplayMode ArcRdParser::displayMode() const { return _displayMode; }
const std::string      ArcRdParser::displayName() const { return _displayName; }
const ArcRdDisplayType ArcRdParser::displayType() const { return _displayType; }
const int              ArcRdParser::width()       const { return _width;       }
const int              ArcRdParser::height()      const { return _height;      }


// Public Methods //

const bool ArcRdParser::executeCommands(ArcWindow* pWindow)
{
	bool isInWorldBlock  = false;
	bool isInFrameBlock  = false;
	bool isInObjectBlock = false;

	while (!_commandQueue.empty())
	{
		const ArcRdCommandType        command = _commandQueue.front().commandType();
		std::vector<std::string> argumentList = _commandQueue.front().argumentList;
		const uint argumentSize = static_cast<uint>(argumentList.size());

		try
		{
			switch (command)
			{
				//////////////////////
				// File Structuring //
				//////////////////////

				case ArcRdCommandType::FrameBegin:
					if (isInObjectBlock)
					{
						return false; // Cannot be within an object block.
					}

					if (argumentSize == 1U)
					{
						pWindow->frameNumber(std::stoi(argumentList[0]));

						isInFrameBlock = true;
					}

					break;
				case ArcRdCommandType::FrameEnd:
					// Not failing if was not in a frame block before, this can be just an extraneous tag.
					// TODO: Log it.

					pWindow->initializeNewFrame();

					isInFrameBlock = false;

					break;
				case ArcRdCommandType::WorldBegin:
					if (isInObjectBlock)
					{
						return false; 
					}

					isInWorldBlock = true;

					break;
				case ArcRdCommandType::WorldEnd:
					// Not failing if was not in a world block before, this can be just an extraneous tag.
					// TODO: Log it.

					isInWorldBlock = false;

					break;
				case ArcRdCommandType::ObjectBegin:
					if (isInFrameBlock)
					{
						return false; // Objects CANNOT be defined within frames. 
					}

					if (argumentSize == 1U)
					{
						// No parameters.
						_objectList.push_back(new ArcRdObject(argumentList[0]));
					}
					else if (argumentSize == 2U)
					{
						// Has Parameters.
						_objectList.push_back(new ArcRdObject(argumentList[0], std::stoi(argumentList[1])));
					}
					else
					{
						// Erroring here because this can have bad ramifications if the arguments are wrong.
						return false;
					}

					isInObjectBlock = true;

					break;
				case ArcRdCommandType::ObjectEnd:
					// Not failing if was not in an object block before, this can be just an extraneous tag.
					// TODO: Log it.
					isInObjectBlock = false;
					break;
				case ArcRdCommandType::ObjectInstance: break;

				////////////////////////
				// Drawing Attributes //
				////////////////////////

				case ArcRdCommandType::Background:
					if (argumentSize == 3U)
					{
						pWindow->fillBackground(ArcColor(std::stof(argumentList[0]),   // Red
							                             std::stof(argumentList[1]),   // Blue
							                             std::stof(argumentList[2]))); // Green
					}

					break;
				case ArcRdCommandType::Color:
					if (argumentSize == 3U)
					{
						pWindow->currentColor(ArcColor(std::stof(argumentList[0]),   // Red
							                           std::stof(argumentList[1]),   // Blue
							                           std::stof(argumentList[2]))); // Green
					}
					break;
				case ArcRdCommandType::Opacity: break;

				/////////////
				// Options //
				/////////////

				case ArcRdCommandType::OptionArray: break;
				case ArcRdCommandType::OptionBool: break;
				case ArcRdCommandType::OptionList: break;
				case ArcRdCommandType::OptionReal: break;
				case ArcRdCommandType::OptionString: break;

				//////////////////////////
				// Camera Specification //
				//////////////////////////

				case ArcRdCommandType::CameraAt:
					if (argumentSize == 3U)
					{
						pWindow->cameraAt(Arc3DPoint(std::stod(argumentList[0]),   // x
							                         std::stod(argumentList[1]),   // y
							                         std::stod(argumentList[2]))); // z
					}
					break;
				case ArcRdCommandType::CameraEye:
					if (argumentSize == 3U)
					{
						pWindow->cameraEyePoint(Arc3DPoint(std::stod(argumentList[0]),   // x
							                               std::stod(argumentList[1]),   // y
							                               std::stod(argumentList[2]))); // z
					}
					break;
				case ArcRdCommandType::CameraFOV:
					if (argumentSize == 1U)
					{
						pWindow->cameraFov(std::stod(argumentList[0]));
					}
					break;
				case ArcRdCommandType::CameraUp:
					if (argumentSize == 3U)
					{
						pWindow->cameraUpVector(ArcVector(std::stod(argumentList[0]),   // x
							                              std::stod(argumentList[1]),   // y
							                              std::stod(argumentList[2]))); // z
					}
					break;
				case ArcRdCommandType::Clipping:
					if (argumentSize == 2U)
					{
						pWindow->clippingNear(std::stod(argumentList[0]));
						pWindow->clippingFar (std::stod(argumentList[1]));
					}
					break;

				////////////////////////
				// Geometric Commands //
				////////////////////////

				case ArcRdCommandType::Point:
					if (argumentSize == 3U)
					{
						if (isInObjectBlock)
						{
							_objectList.back()->commandQueue.push(ArcRdCommand(command, argumentList));
						}
						else if (isInWorldBlock)
						{
							pWindow->draw3DPoint(Arc3DPoint(std::stod(argumentList[0]),   // x
							                                std::stod(argumentList[1]),   // y
							                                std::stod(argumentList[2]))); // z
						}
					}
					break;
				case ArcRdCommandType::PointSet:
					if (argumentSize > 2U)
					{
						if (isInObjectBlock)
						{
							_objectList.back()->commandQueue.push(ArcRdCommand(command, argumentList));
						}
						else if (isInWorldBlock)
						{
							const ArcColor& currentColor = pWindow->currentColor();

							uint argumentIndex = 0;

							const uint flags = getVertexTypes(argumentList[argumentIndex]);
							if (!(flags & static_cast<uint>(VertexTypes::Position)))
							{
								break;
							}

							const int numPoints = std::stoi(argumentList[++argumentIndex]);

							Arc3DPoint newPoint;

							while (argumentIndex < argumentSize)
							{
								if (argumentIndex + 3U >= argumentSize)
								{
									// Not enough arguments to finish.
									break;
								}

								Arc3DPoint newPoint(std::stod(argumentList[++argumentIndex]),
													std::stod(argumentList[++argumentIndex]),
													std::stod(argumentList[++argumentIndex]));

								if (flags & static_cast<uint>(VertexTypes::Color))
								{
									if (argumentIndex + 3U >= argumentSize)
									{
										// Not enough arguments to finish.
										break;
									}

									pWindow->currentColor(ArcColor(std::stof(argumentList[++argumentIndex]),   // Red
																   std::stof(argumentList[++argumentIndex]),   // Blue
																   std::stof(argumentList[++argumentIndex]))); // Green
								}
								///////////////////////////
								// TODO: Rest of the cases.
								///////////////////////////

								pWindow->draw3DPoint(newPoint);
							}

							pWindow->currentColor(currentColor);
						}
					}

					break;
				case ArcRdCommandType::Line:
					if (argumentSize == 6U)
					{
						if (isInObjectBlock)
						{
							_objectList.back()->commandQueue.push(ArcRdCommand(command, argumentList));
						}
						else if (isInWorldBlock)
						{
							pWindow->draw3DLine(Arc3DLine(Arc3DPoint(std::stod(argumentList[0]),    // Start x
								                                     std::stod(argumentList[1]),    // Start y
								                                     std::stod(argumentList[2])),   // Start z
								                          Arc3DPoint(std::stod(argumentList[3]),    // End x
								                                     std::stod(argumentList[4]),    // End y
								                                     std::stod(argumentList[5])))); // End z
						}
					}
					break;
				case ArcRdCommandType::LineSet:
					if (argumentSize > 3U)
					{
						if (isInObjectBlock)
						{
							_objectList.back()->commandQueue.push(ArcRdCommand(command, argumentList));
							break;
						}
						else if (isInWorldBlock)
						{
							const ArcColor& currentColor = pWindow->currentColor();

							uint argumentIndex = 0;

							const uint flags     = getVertexTypes(argumentList[  argumentIndex]);
							const int  numPoints =      std::stoi(argumentList[++argumentIndex]);
							const int  numLines  =      std::stoi(argumentList[++argumentIndex]);

							std::vector<Arc3DPoint> pointVector;
							std::vector<ArcColor>   colorVector;

							for (int i = 0; i < numPoints; ++i)
							{
								if (flags & static_cast<uint>(VertexTypes::Position))
								{
									if (argumentIndex + 6U >= argumentSize)
									{
										// Not enough arguments to finish.
										break;
									}
									
									pointVector.push_back(Arc3DPoint(std::stod(argumentList[++argumentIndex]),
										                             std::stod(argumentList[++argumentIndex]),
										                             std::stod(argumentList[++argumentIndex])));
								}

								if (flags & static_cast<uint>(VertexTypes::Color))
								{
									if (argumentIndex + 3U >= argumentSize)
									{
										// Not enough arguments to finish.
										break;
									}

									colorVector.push_back(ArcColor(std::stof(argumentList[++argumentIndex]),   // Red
										                           std::stof(argumentList[++argumentIndex]),   // Blue
										                           std::stof(argumentList[++argumentIndex]))); // Green
								}
								///////////////////////////
								// TODO: Rest of the cases.
								///////////////////////////
							}

							if (pointVector.size() != numPoints || ((flags & static_cast<uint>(VertexTypes::Color) && colorVector.size() != numPoints)))
							{
								// We didn't find the correct number of points specified for this object.
								break;
							}

							int prevVertex = -1;
							int currentVertex = -1;

							for (int i = 0; i < numLines; ++i)
							{
								if (++argumentIndex > argumentSize)
								{
									break;
								}

								while (currentVertex = std::stoi(argumentList[argumentIndex]) != -1)
								{
									if (prevVertex == -1)
									{
										prevVertex = currentVertex;
									}

									if (currentVertex != prevVertex)
									{
										if (flags & static_cast<uint>(VertexTypes::Color))
										{
											pWindow->currentColor(colorVector[i]);
										}

										pWindow->draw3DLine(Arc3DLine(pointVector[prevVertex], pointVector[currentVertex]));
									}
								}
							}

							pWindow->currentColor(currentColor);
						}
					}
					
					break;
				case ArcRdCommandType::Circle:
					pWindow->draw3DCircle();
					break;
				case ArcRdCommandType::Fill:
					if (isInWorldBlock && argumentSize == 2U)
					{
						pWindow->fill(Arc2DPoint(std::stod(argumentList[0]), std::stod(argumentList[1])));
					}
					break;
				case ArcRdCommandType::Cone:
					pWindow->drawCone();
					break;
				case ArcRdCommandType::Cube:
					pWindow->drawCube();
					break;
				case ArcRdCommandType::Curve: break;
				case ArcRdCommandType::Cylinder:
					pWindow->drawCylinder();
					break;
				case ArcRdCommandType::Disk:
					pWindow->drawDisk();
					break;
				case ArcRdCommandType::Hyperboloid: break;
				case ArcRdCommandType::Paraboloid: break;
				case ArcRdCommandType::Patch: break;
				case ArcRdCommandType::PolySet:
					
					break;
				case ArcRdCommandType::Sphere:
					pWindow->drawSphere();
					break;
				case ArcRdCommandType::SqSphere: break;
				case ArcRdCommandType::SqTorus: break;
				case ArcRdCommandType::Subdivision: break;
				case ArcRdCommandType::Torus: break;
				case ArcRdCommandType::Tube: break;

				///////////////////////////////
				// Geometric Transformations //
				///////////////////////////////

				case ArcRdCommandType::Rotate:
					if (argumentSize == 2U)
					{
						switch (argumentList[0][0])
						{
							case ('X'):
								pWindow->rotateTransformationYZ(std::stod(argumentList[1]));
								break;
							case ('Y'):
								pWindow->rotateTransformationZX(std::stod(argumentList[1]));
								break;
							case ('Z'):pWindow->rotateTransformationXY(std::stod(argumentList[1]));
								break;
							default:
								break;
						}
					}
					break;
				case ArcRdCommandType::Scale:
					if (argumentSize == 3U)
					{
						pWindow->scaleTransformation(std::stod(argumentList[0]), std::stod(argumentList[1]), std::stod(argumentList[2]));
					}
					break;
				case ArcRdCommandType::Translate:
					if (argumentSize == 3U)
					{
						pWindow->translateTransformation(std::stod(argumentList[0]), std::stod(argumentList[1]), std::stod(argumentList[2]));
					}
					break;
				case ArcRdCommandType::XformPush:
					pWindow->pushTransformation();
					break;
				case ArcRdCommandType::XformPop:
					pWindow->popTransformation();
					break;

				//////////////
				// Lighting //
				//////////////

				case ArcRdCommandType::AmbientLight: break;
				case ArcRdCommandType::FarLight: break;
				case ArcRdCommandType::PointLight: break;
				case ArcRdCommandType::ConeLight: break;

				////////////////////////
				// Surface Attributes //
				////////////////////////

				case ArcRdCommandType::Ka: break;
				case ArcRdCommandType::Kd: break;
				case ArcRdCommandType::Ks: break;
				case ArcRdCommandType::Specular: break;
				case ArcRdCommandType::Surface: break;

				///////////////////////
				// Attribute Mapping //
				///////////////////////

				case ArcRdCommandType::MapLoad: break;
				case ArcRdCommandType::Map: break;
				case ArcRdCommandType::MapSample: break;
				case ArcRdCommandType::MapBound: break;
				case ArcRdCommandType::MapBorder: break;

				/////////////
				// Invalid //
				/////////////

				case ArcRdCommandType::Invalid:
				default:
					break;
			}
		}
		catch (std::invalid_argument)
		{
			// TODO: Error logging here...
			return false;
		}
		_commandQueue.pop();
	}

	return true;
}

bool ArcRdParser::openAndReadFile(const std::string fileName)
{
	if (!fileName.ends_with(".rd"))
	{
		return false;
	}

	_stream.open(fileName);

	if (!isFileOpen() || !readFile())
	{
		return false;
	}

	return true;
}




// Private Methods //

void ArcRdParser::closeFile()
{
	_stream.close();
}

const ArcRdCommandType ArcRdParser::commandTypeFromString(std::string value)
{
	if      (value == RD_CMD_DISPLAY)         { return ArcRdCommandType::Display;         }
	else if (value == RD_CMD_FORMAT)          { return ArcRdCommandType::Format;          }
	else if (value == RD_CMD_FRAME_BEGIN)     { return ArcRdCommandType::FrameBegin;      }
	else if (value == RD_CMD_FRAME_END)       { return ArcRdCommandType::FrameEnd;        }
	else if (value == RD_CMD_WORLD_BEGIN)     { return ArcRdCommandType::WorldBegin;      }
	else if (value == RD_CMD_WORLD_END)       { return ArcRdCommandType::WorldEnd;        }
	else if (value == RD_CMD_OBJECT_BEGIN)    { return ArcRdCommandType::ObjectBegin;     }
	else if (value == RD_CMD_OBJECT_END)      { return ArcRdCommandType::ObjectEnd;       }
	else if (value == RD_CMD_OBJECT_INSTANCE) { return ArcRdCommandType::ObjectInstance;  }
	else if (value == RD_CMD_BACKGROUND)      { return ArcRdCommandType::Background;      }
	else if (value == RD_CMD_COLOR)           { return ArcRdCommandType::Color;           }
	else if (value == RD_CMD_OPACITY)         { return ArcRdCommandType::Opacity;         }
	else if (value == RD_CMD_OPTION_ARRAY)    { return ArcRdCommandType::OptionArray;     }
	else if (value == RD_CMD_OPTION_BOOL)     { return ArcRdCommandType::OptionBool;      }
	else if (value == RD_CMD_OPTION_LIST)     { return ArcRdCommandType::OptionList;      }
	else if (value == RD_CMD_OPTION_REAL)     { return ArcRdCommandType::OptionReal;      }
	else if (value == RD_CMD_OPTION_STRING)   { return ArcRdCommandType::OptionString;    }
	else if (value == RD_CMD_CAMERA_AT)       { return ArcRdCommandType::CameraAt;        }
	else if (value == RD_CMD_CAMERA_EYE)      { return ArcRdCommandType::CameraEye;       }
	else if (value == RD_CMD_CAMERA_FOV)      { return ArcRdCommandType::CameraFOV;       }
	else if (value == RD_CMD_CAMERA_UP)       { return ArcRdCommandType::CameraUp;        }
	else if (value == RD_CMD_CLIPPING)        { return ArcRdCommandType::Clipping;        }
	else if (value == RD_CMD_POINT)           { return ArcRdCommandType::Point;           }
	else if (value == RD_CMD_POINT_SET)       { return ArcRdCommandType::PointSet;        }
	else if (value == RD_CMD_LINE)            { return ArcRdCommandType::Line;            }
	else if (value == RD_CMD_LINE_SET)        { return ArcRdCommandType::LineSet;         }
	else if (value == RD_CMD_CIRCLE)          { return ArcRdCommandType::Circle;          }
	else if (value == RD_CMD_FILL)            { return ArcRdCommandType::Fill;            }
	else if (value == RD_CMD_CONE)            { return ArcRdCommandType::Cone;            }
	else if (value == RD_CMD_CUBE)            { return ArcRdCommandType::Cube;            }
	else if (value == RD_CMD_CURVE)           { return ArcRdCommandType::Curve;           }
	else if (value == RD_CMD_CYLINDER)        { return ArcRdCommandType::Cylinder;        }
	else if (value == RD_CMD_DISK)            { return ArcRdCommandType::Disk;            }
	else if (value == RD_CMD_HYPERBOLOID)     { return ArcRdCommandType::Hyperboloid;     }
	else if (value == RD_CMD_PARABOLOID)      { return ArcRdCommandType::Paraboloid;      }
	else if (value == RD_CMD_PATCH)           { return ArcRdCommandType::Patch;           }
	else if (value == RD_CMD_POLYSET)         { return ArcRdCommandType::PolySet;         }
	else if (value == RD_CMD_SPHERE)          { return ArcRdCommandType::Sphere;          }
	else if (value == RD_CMD_SQ_SPHERE)       { return ArcRdCommandType::SqSphere;        }
	else if (value == RD_CMD_SQ_TORUS)        { return ArcRdCommandType::SqTorus;         }
	else if (value == RD_CMD_SUBDIVISION)     { return ArcRdCommandType::Subdivision;     }
	else if (value == RD_CMD_TORUS)           { return ArcRdCommandType::Torus;           }
	else if (value == RD_CMD_TUBE)            { return ArcRdCommandType::Tube;            }
	else if (value == RD_CMD_ROTATE)          { return ArcRdCommandType::Rotate;          }
	else if (value == RD_CMD_SCALE)           { return ArcRdCommandType::Scale;           }
	else if (value == RD_CMD_TRANSLATE)       { return ArcRdCommandType::Translate;       }
	else if (value == RD_CMD_XFORM_PUSH)      { return ArcRdCommandType::XformPush;       }
	else if (value == RD_CMD_XFORM_POP)       { return ArcRdCommandType::XformPop;        }
	else if (value == RD_CMD_AMBIENT_LIGHT)   { return ArcRdCommandType::AmbientLight;    }
	else if (value == RD_CMD_FAR_LIGHT)       { return ArcRdCommandType::FarLight;        }
	else if (value == RD_CMD_POINT_LIGHT)     { return ArcRdCommandType::PointLight;      }
	else if (value == RD_CMD_CONE_LIGHT)      { return ArcRdCommandType::ConeLight;       }
	else if (value == RD_CMD_KA)              { return ArcRdCommandType::Ka;              }
	else if (value == RD_CMD_KD)              { return ArcRdCommandType::Kd;              }
	else if (value == RD_CMD_KS)              { return ArcRdCommandType::Ks;              }
	else if (value == RD_CMD_SPECULAR)        { return ArcRdCommandType::Specular;        }
	else if (value == RD_CMD_SURFACE)         { return ArcRdCommandType::Surface;         }
	else if (value == RD_CMD_MAP_LOAD)        { return ArcRdCommandType::MapLoad;         }
	else if (value == RD_CMD_MAP)             { return ArcRdCommandType::Map;             }
	else if (value == RD_CMD_MAP_SAMPLE)      { return ArcRdCommandType::MapSample;       }
	else if (value == RD_CMD_MAP_BOUND)       { return ArcRdCommandType::MapBound;        }
	else if (value == RD_CMD_MAP_BORDER)      { return ArcRdCommandType::MapBorder;       }
	else                                      { return ArcRdCommandType::Invalid;         }
}

const ArcRdDisplayMode ArcRdParser::displayModeFromString(std::string value)
{
	if      (value == RD_PARAM_DISPLAY_MODE_RGB_SINGLE) { return ArcRdDisplayMode::RGBSingle; }
	else if (value == RD_PARAM_DISPLAY_MODE_RGB_OBJECT) { return ArcRdDisplayMode::RGBObject; }
	else if (value == RD_PARAM_DISPLAY_MODE_RGB_DOUBLE) { return ArcRdDisplayMode::RGBDouble; }
	else if (value == RD_PARAM_DISPLAY_TYPE_RGB)        { return ArcRdDisplayMode::RGB;       }
	else                                                { return ArcRdDisplayMode::Invalid;   }
}

const uint ArcRdParser::getVertexTypes(std::string& value)
{
	int flags = 0;

	for (int i = 0; i < value.size(); ++i)
	{
		switch (value[i])
		{
		case ('P'):
			flags |= static_cast<uint>(VertexTypes::Position);
			break;
		case ('D'):
			flags |= static_cast<uint>(VertexTypes::Direction);
			break;
		case ('N'):
			flags |= static_cast<uint>(VertexTypes::Normal);
			break;
		case ('C'):
			flags |= static_cast<uint>(VertexTypes::Color);
			break;
		case ('W'):
			flags |= static_cast<uint>(VertexTypes::Weight);
			break;
		case ('T'):
			flags |= static_cast<uint>(VertexTypes::Texture);
			break;
		case ('O'):
			flags |= static_cast<uint>(VertexTypes::Opacity);
			break;
		default:
			break;
		}
	}

	return flags;
}

const ArcRdDisplayType ArcRdParser::displayTypeFromString(std::string value)
{
	if      (value == RD_PARAM_DISPLAY_TYPE_PNM)    { return ArcRdDisplayType::Pnm;     }
	else if (value == RD_PARAM_DISPLAY_TYPE_SCREEN) { return ArcRdDisplayType::Screen;  }
	else                                            { return ArcRdDisplayType::Invalid; }
}

const bool ArcRdParser::isFileOpen() const
{
	return _stream.is_open();
}

bool ArcRdParser::readFile()
{
	int                      argumentNumber = 0;
	std::string              buffer;
	std::string              commandName;
	ArcRdCommandType         commandType;
	bool                     hasHeader = false;
	bool                     hasFormat = false;
	std::string              line;
	std::istringstream       tokenizer;
	std::vector<std::string> tokens;

	// Read the "Display" header of the .rd file.
	while (!_stream.eof() && !hasHeader)
	{
		std::getline(_stream, line);
		if (line.starts_with(RD_CMD_DISPLAY))
		{
			// Loop through the rest of the line and get the three command parameters.
			for (size_t characterIndex = RD_CMD_DISPLAY.length(); characterIndex < line.length(); ++characterIndex)
			{
				char character = line[characterIndex];
				if (character == '\"')
				{
					++characterIndex;
					for (;characterIndex < line.length() && line[characterIndex] != '\"'; ++characterIndex)
					{
						buffer += line[characterIndex];
					}

					switch (argumentNumber)
					{
						case 0: // The display name.
							_displayName = buffer;
							break;
						case 1: // The display type.
							_displayType = displayTypeFromString(buffer);
							break;
						case 2: // The display mode.
							_displayMode = displayModeFromString(buffer);
							hasHeader = true;
							break;
					}

					++argumentNumber;
					buffer.clear();
				}
			}
		}
	}

	// Verify we found all necessary header pieces.
	if (_displayName.empty() || _displayType == ArcRdDisplayType::Invalid || _displayMode == ArcRdDisplayMode::Invalid)
	{
		return false;
	}

	// Read the "Format" command for the width and height for the display (should be the very first command after display).
	while (!_stream.eof() && !hasFormat)
	{
		std::getline(_stream, line);
		if (line.starts_with(RD_CMD_FORMAT))
		{
			tokenizer = std::istringstream(line);
			tokenizer >> buffer; // Command
			try
			{
				if (tokenizer >> buffer)
				{
					// Width
					_width = std::stoi(buffer);
				}
				else
				{
					return false;
				}

				if (tokenizer >> buffer)
				{
					// Height
					_height = std::stoi(buffer);
				}
				else
				{
					return false;
				}

				hasFormat = true;
			}
			catch (std::invalid_argument)
			{
				// Invalid argument conversion.
				return false;
			}
		}
	}

	// Verify we found all necessary format pieces.
	if (!hasFormat)
	{
		return false;
	}

	size_t index = std::string::npos;
	bool foundComment = false;

	// Read body of the .rd file
	while (!_stream.eof())
	{
		foundComment = false;
		std::getline(_stream, line);
		tokenizer = std::istringstream(line);

		if (!(tokenizer >> buffer))
		{
			// Blank line.
			continue;
		}

		if ((index = buffer.find_first_of('#')) != std::string::npos)
		{
			if (index == 0)
			{
				// First character is a '#'
				continue;
			}

			// Everything after this character is a comment.
			buffer = buffer.substr(0, index);
			foundComment = true;
		}

		// Check if the first string is a command or part of the previous commands arguments.
		if ((commandType = commandTypeFromString(buffer)) != ArcRdCommandType::Invalid)
		{
			_commandQueue.push(ArcRdCommand(commandType));
		}

		if (_commandQueue.empty())
		{
			// We are inbetween the format command and body of the .rd file.
			continue;
		}

		// Add arguments to the previously added command.
		ArcRdCommand& command = _commandQueue.back();

		while (!foundComment && tokenizer >> buffer)
		{
			if ((index = buffer.find_first_of('#')) != std::string::npos)
			{
				if (index == 0)
				{
					// First character is a '#'
					continue;
				}

				// Everything after this character is a comment.
				buffer = buffer.substr(0, index);
				foundComment = true;
			}

			command.argumentList.push_back(buffer);
		}
	}

	closeFile();

	return true;
}