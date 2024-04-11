#pragma once

#ifndef ARCRDOBJECT_HPP
#define ARCRDOBJECT_HPP

#include "ArcRdCommand.hpp"
#include "ArcTypedefs.h"

#include <deque>
#include <string>


struct ArcRdObject
{
public: // Constructor(s) //

	ArcRdObject(const std::string& name, std::vector<std::string> params = std::vector<std::string>())
	{
		objectName = name;
		parameters = std::move(params);
	}




public: // Variables

	std::deque<ArcRdCommand> commandQueue; // The queue of commands read from the .rd file.
	std::string              objectName;
	std::vector<std::string> parameters;
};

#endif // !ARCRDOBJECT_HPP