#pragma once

#ifndef ARCLOGGINGMACROS_H
#define ARCLOGGINGMACROS_H


#if COMPILING_DLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif

#include "ArcLogger.h"


#define ARC_LOG(message) ArcLogger::writeLog(message)


#endif // !ARCLOGGINGMACROS_H