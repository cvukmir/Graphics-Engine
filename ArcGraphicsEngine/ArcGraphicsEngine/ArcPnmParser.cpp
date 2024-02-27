#include "ArcPnmParser.h"
#include "ArcConstants.h"
#include "ArcWindow.h"

#include <string>
#include <fstream>
#include <ios>

#include <Windows.h>


// Constructor/Destructor(s) //

ArcPnmParser::ArcPnmParser()
{
}

ArcPnmParser::~ArcPnmParser()
{
}


// Static Methods //

bool ArcPnmParser::readPnmAndDraw(std::string fileName)
{
	std::ifstream inputStream(fileName, std::ios::binary);

	if (!inputStream.is_open())
	{
		return false;
	}

	inputStream.close();

	return true;
}

bool ArcPnmParser::writeToPnmFile(std::string fileName)
{
	ArcWindow*    pWindow = ArcWindow::window();
	const int      height = pWindow->windowHeight();
	const int       width = pWindow->windowWidth();
	const UINT32* pMemory = pWindow->memory();

	std::ofstream outputStream(fileName, std::ios::binary);

	if (!outputStream.is_open())
	{
		return false;
	}

	outputStream << PNM_HEADER        << '\n'
	             << width             << ' '
	             << height            << '\n'
	             << PNM_MAX_INTENSITY << '\n';

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			UINT32 value = *(pMemory + (i * width) + j);
			outputStream.put(ArcColor::getRedComponent(value));
			outputStream.put(ArcColor::getGreenComponent(value));
			outputStream.put(ArcColor::getBlueComponent(value));
		}
	}

	outputStream.close();

	return true;
}