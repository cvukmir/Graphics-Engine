
#include <comdef.h>
#include <SDKDDKVer.h> // Including SDKDDKVer.h defines the highest available Windows platform.
#include <windows.h>

#include "ArcLogger.h"

#include <iostream>

ArcLogger* ArcLogger::_pInstancePtr = nullptr; // = nullptr;

ArcLogger::ArcLogger()
{
	#if _DEBUG
		AllocConsole();
	#endif // !_DEBUG
}

ArcLogger::~ArcLogger()
{
	#if _DEBUG
		FreeConsole();
	#endif // !_DEBUG
}

ArcLogger* ArcLogger::logger()
{
	if (!_pInstancePtr)
	{
		_pInstancePtr = new ArcLogger();
	}

	return _pInstancePtr;
}

void ArcLogger::writeLog(const std::string& message)
{
	#if !_DEBUG
		return;
	#endif // !_DEBUG

	HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (stdOut != NULL && stdOut != INVALID_HANDLE_VALUE)
	{
		DWORD written = 0;
		WriteConsoleA(stdOut, message.c_str(), message.length(), &written, NULL);
	}

	std::cout << "HELLO WORLD!" << std::endl;

}
