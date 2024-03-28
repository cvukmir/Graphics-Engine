#pragma once

#ifndef ARCPNMPARSER_H
#define ARCPNMPARSER_H

// Stdlib
#include <string>

class ArcPnmParser
{
public: // Constructor/Destructor(s) //
	ArcPnmParser();
	~ArcPnmParser();


public: // Static Methods //

	static bool readPnmAndDraw(const std::string fileName);

	static bool writeToPnmFile(const std::string fileName);
};



#endif // !ARCPNMPARSER_H