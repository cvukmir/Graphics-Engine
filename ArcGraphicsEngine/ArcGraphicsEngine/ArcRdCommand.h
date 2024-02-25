#pragma once

#ifndef ARCRDCOMMAND_H
#define ARCRDCOMMAND_H

#include <vector>
#include <string>
#include "ArcConstants.h"
#include "ArcEnums.h"

struct ArcRdCommand
{
public:

	ArcRdCommand(ArcRdCommandType type, std::vector<std::string>& list)
	{
		_commandType  = type;
		_argumentList = std::move(list);
	}

	const ArcRdCommandType          commandType() const { return _commandType;  }
	const std::vector<std::string> argumentList() const { return _argumentList; }

public: // Virtual methods

private:

	ArcRdCommandType         _commandType;
	std::vector<std::string> _argumentList;
};

#endif // !ARCRDCOMMAND_H