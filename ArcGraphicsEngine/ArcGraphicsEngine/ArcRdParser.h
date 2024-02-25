#pragma once

#ifndef ARCRDPARSER_H
#define ARCRDPARSER_H

#include <string>
#include <fstream>
#include <ios>
#include <queue>
#include "ArcRdCommand.h"

class ArcRdParser
{
public:

	ArcRdParser();

	~ArcRdParser();

	bool openFile(const std::string fileName);

	const bool executeCommands(ArcWindow* pWindow);

	const std::string      displayName() const;
	const ArcRdDisplayType displayType() const;
	const ArcRdDisplayMode displayMode() const;
	const int              width()       const;
	const int              height()      const;

private:

	void closeFile();

	bool readFile();

	const bool isFileOpen() const;

	const ArcRdCommandType commandTypeFromString(std::string value);
	const ArcRdDisplayType displayTypeFromString(std::string value);
	const ArcRdDisplayMode displayModeFromString(std::string value);



private:

	std::string              _fileName;
	std::ifstream            _stream;
	std::string              _displayName;
	ArcRdDisplayType         _displayType;
	ArcRdDisplayMode         _displayMode;
	int                      _width;
	int                      _height;
	std::queue<ArcRdCommand> _commandQueue;
};


#endif // !ARCRDPARSER_H
