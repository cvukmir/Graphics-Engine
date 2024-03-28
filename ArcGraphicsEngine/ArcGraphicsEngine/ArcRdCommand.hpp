#pragma once

#ifndef ARCRDCOMMAND_H
#define ARCRDCOMMAND_H

// Stdlib
#include <vector>
#include <string>

// ArcFramework
#include "ArcConstants.h"
#include "ArcEnums.h"


struct ArcRdCommand
{
public: // Constructor(s) //

	ArcRdCommand(const ArcRdCommandType type)
	{
		_commandType  = type;
	}

	ArcRdCommand(const ArcRdCommandType type, std::vector<std::string>& list)
	{
		_commandType = type;
		argumentList = list;
	}


public: // Properties //

	const ArcRdCommandType commandType() const { return _commandType;  } // Gets the command type


public: // Variables //

	std::vector<std::string> argumentList; // The arguments for the command.



private: // Variables //

	ArcRdCommandType _commandType;  // The command type.
};

#endif // !ARCRDCOMMAND_H