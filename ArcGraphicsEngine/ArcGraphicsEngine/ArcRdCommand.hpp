#pragma once

#ifndef ARCRDCOMMAND_H
#define ARCRDCOMMAND_H

// Stdlib
#include <vector>
#include <string>

// ArcMain
#include "ArcConstants.h"
#include "ArcEnums.h"


struct ArcRdCommand
{
public: // Constructor(s) //

	ArcRdCommand(ArcRdCommandType type, std::vector<std::string>& list)
	{
		_commandType  = type;
		_argumentList = std::move(list);
	}


public: // Properties //

	const ArcRdCommandType          commandType() const { return _commandType;  } // Gets the command type
	const std::vector<std::string> argumentList() const { return _argumentList; } // Gets the argument list.


private: // Variables //

	ArcRdCommandType         _commandType;  // The command type.
	std::vector<std::string> _argumentList; // The arguments for the command.
};

#endif // !ARCRDCOMMAND_H