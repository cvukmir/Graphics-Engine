#pragma once

#ifndef ARCLOGGER_H
#define ARCLOGGER_H


#if COMPILING_DLL
	#define DLLEXPORT __declspec(dllexport)
#else
	#define DLLEXPORT __declspec(dllimport)
#endif

#include <string>


class DLLEXPORT ArcLogger
{
public:

	ArcLogger();
	~ArcLogger();


public: // Static Methods (Singleton) //

	// Creates the one and only instance of this object.
	static ArcLogger* logger();


public: // Methods //

	/* Delete copy constructor */
	ArcLogger(const ArcLogger& value) = delete;

	static void writeLog(const std::string& message);


private: // Static Variables //

	static ArcLogger* _pInstancePtr; // The only and only instance of this object.


private: // Instance Variables //
};

#endif // !ARCLOGGER_H