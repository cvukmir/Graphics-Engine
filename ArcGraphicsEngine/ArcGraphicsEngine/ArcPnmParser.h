#pragma once

#ifndef ARCPNMPARSER_H
#define ARCPNMPARSER_H

#include <string>

class ArcPnmParser
{
public:
	ArcPnmParser();
	~ArcPnmParser();

	static bool readPnmAndDraw(const std::string fileName);

	static bool writeToPnmFile(const std::string fileName);
};



#endif // !ARCPNMPARSER_H