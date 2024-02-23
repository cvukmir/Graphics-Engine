
#include <string>

#include "ArcWindow.h"
#include "ArcRdParser.h"
#include "ArcConstants.h"
#include "ArcEnums.h"
#include "ArcRdCommand.h"

#include <string>
#include <fstream>
#include <ios>
#include <sstream>
#include <vector>
#include <queue>

#include <Windows.h>

ArcRdParser::ArcRdParser()
{
}

ArcRdParser::~ArcRdParser()
{
	if (isFileOpen())
	{
		closeFile();
	}
}

const int         ArcRdParser::displayMode() const { return _displayMode; }
const std::string ArcRdParser::displayName() const { return _displayName; }
const int         ArcRdParser::displayType() const { return _displayType; }


bool ArcRdParser::readFile()
{
	std::string              buffer;
	std::string              headerLine;
	std::istringstream       tokenizer;
	std::vector<std::string> tokens;
	std::string              commandName;

	while (!_stream.eof())
	{
		std::getline(_stream, headerLine);
		if (IsCharAlphaNumericA(headerLine[0]))
		{
			tokenizer = std::istringstream(headerLine);

			tokenizer >> buffer;
			commandName = buffer;

			while (!buffer.empty())
			{
				tokens.push_back(buffer);
			}

			_commandQueue.push(ArcRdCommand(commandName, tokens));
		}
	}

	closeFile();

	ArcRdCommand firstCommand = _commandQueue.front();

	if (firstCommand.commandType() != ArcRdCommandType::Display || firstCommand.argumentList().size() != 4)
	{
		return false;
	}

	_displayName = tokens[1];

	if (tokens[2] == RD_PARAM_DISPLAY_TYPE_PNM)
	{
		_displayType = ArcRdDisplayType::Pnm;
	}
	else if (tokens[2] == RD_PARAM_DISPLAY_TYPE_SCREEN)
	{
		_displayType = ArcRdDisplayType::Screen;
	}
	else
	{
		return false;
	}

	if (tokens[3] == RD_PARAM_DISPLAY_MODE_RGB_SINGLE)
	{
		_displayMode == ArcRdDisplayMode::RGBSingle;
	}
	else if (tokens[3] == RD_PARAM_DISPLAY_MODE_RGB_DOUBLE)
	{
		_displayMode == ArcRdDisplayMode::RGBDouble;
	}
	else if (tokens[3] == RD_PARAM_DISPLAY_MODE_RGB_OBJECT)
	{
		_displayMode == ArcRdDisplayMode::RGBObject;
	}
	else
	{
		return false;
	}

	_commandQueue.pop();

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
}

void ArcRdParser::closeFile()
{
	_stream.close();
}