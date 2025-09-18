#pragma once
#include "commands.h"
#include <unordered_map>

class Node;
using command_ptr = std::shared_ptr<ICommand>;

class CommandFabric
{
	static unsigned int m_gen_value_chance;
	static unsigned int m_sub_chance;
	static unsigned int m_unsub_chance;
	static unsigned int m_create_sub_chance;
	static unsigned int m_nothing_chance;

	enum ECommandType
	{
		CREATE_VALUE,
		SUBSCRIBE,
		UNSUBSCRIBE,
		CREATE_SUB_NODE
	};
public:
	using command_creater_ptr = command_ptr(*)(node_weak_ptr);
	using commands_map = std::unordered_map<ECommandType, command_creater_ptr>;

	static command_ptr create_random_command(node_weak_ptr sender);
private:
	static int get_int_command_distribution();

	static command_ptr create_command(ECommandType type, node_weak_ptr sender);

	static commands_map& get_creators_map();
	static commands_map init_creators_map();

	static command_ptr create_gen_value_command(node_weak_ptr sender);
	static command_ptr create_subscribe_command(node_weak_ptr sender);
	static command_ptr create_unsubscribe_command(node_weak_ptr sender);
	static command_ptr create_cr_and_sub_command(node_weak_ptr sender);
};