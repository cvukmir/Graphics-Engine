#pragma once

#ifndef ARCRDPARSER_H
#define ARCRDPARSER_H

// Stdlib
#include <string>
#include <fstream>
#include <ios>
#include <queue>

// ArcIO
#include "ArcRdCommand.hpp"
#include "ArcRdObject.hpp"
#include "ArcEnums.h"


class ArcRdParser
{
public: // Constructor/Destructor(s) //

	ArcRdParser();

	~ArcRdParser();


public: // Properties //

	const ArcRdDisplayMode displayMode() const; // Gets this .rd files display mode.
	const std::string      displayName() const; // Gets this .rd files display name.
	const ArcRdDisplayType displayType() const; // Gets this .rd files display type.
	const int              height()      const; // Gets this .rd files display height.
	const int              width()       const; // Gets this .rd files display width.


public: // Methods //


	// Opens and reads the input from the give .rd file name.
	bool openAndReadFile(const std::string fileName);

	// Exectues all commands read from the .rd file.
	const bool executeCommands(ArcWindow* pWindow);


private: // Methods //

	// Closes the .rd file (if open).
	void closeFile();

	// Gets the command type enum from the given string.
	const ArcRdCommandType commandTypeFromString(std::string value);

	// Gets the display type enum from the given string.
	const ArcRdDisplayType displayTypeFromString(std::string value);

	// Gets the display mode enum from the given string.
	const ArcRdDisplayMode displayModeFromString(std::string value);

	const uint getVertexTypes(std::string& value);

	// Checks whether the current .rd file is open.
	const bool isFileOpen() const;

	// Reads the .rd file.
	bool readFile();



private: // Variables //

	std::deque<ArcRdCommand> _commandQueue; // The queue of commands read from the .rd file.
	std::vector<ArcRdObject*> _objectList;
	ArcRdDisplayMode         _displayMode;  // The display mode.
	std::string              _displayName;  // The display name.
	ArcRdDisplayType         _displayType;  // The display type.
	int                      _height;       // The display height.
	std::ifstream            _stream;       // The input file stream.
	int                      _width;        // The display width.
};


#endif // !ARCRDPARSER_H
