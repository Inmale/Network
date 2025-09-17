#pragma once
#include "commands.h"

class CommandFabric
{
	enum ECommandType
	{
		CREATE_VALUE,
		SUBSCRIBE,
		UNSUBSCRIBE,
		CREATE_SUB_NODE
	};
public:
	using command_ptr = std::shared_ptr<ICommand>;

	static command_ptr create_random_command();
};