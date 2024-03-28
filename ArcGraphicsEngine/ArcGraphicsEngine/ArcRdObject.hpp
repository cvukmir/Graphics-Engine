#include "ArcRdCommand.hpp"
#include "ArcTypedefs.h"

#include <queue>
#include <string>


struct ArcRdObject
{
public: // Constructor(s) //

	ArcRdObject(const std::string& name, const uint count = 0U)
	{
		objectName = name;
		parameters = count;
	}




public: // Variables

	std::queue<ArcRdCommand> commandQueue; // The queue of commands read from the .rd file.
	std::string objectName;
	uint parameters;
};