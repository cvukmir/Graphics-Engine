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

	void closeFile();
	
	bool readFile();

	const bool isFileOpen() const;

	const std::string displayName() const;
	const int displayType() const;
	const int displayMode() const;


private:

	std::string              _fileName;
	std::ifstream            _stream;
	std::string              _displayName;
	int                      _displayType;
	int                      _displayMode;
	std::queue<ArcRdCommand> _commandQueue;
};


#endif // !ARCRDPARSER_H
