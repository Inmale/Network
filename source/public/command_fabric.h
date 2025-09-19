#pragma once
#include "commands.h"
#include <unordered_map>
#include <vector>

class Node;
using command_ptr = std::shared_ptr<ICommand>;

class CommandFabric
{
	using weights_vector = std::vector<float>;

	static weights_vector m_weights;

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
	static int get_random_command_index();
	static float get_random_float_zero_one();

	static command_ptr create_command(ECommandType type, node_weak_ptr sender);

	static commands_map& get_creators_map();
	static commands_map init_creators_map();

	static command_ptr create_gen_value_command(node_weak_ptr sender);
	static command_ptr create_subscribe_command(node_weak_ptr sender);
	static command_ptr create_unsubscribe_command(node_weak_ptr sender);
	static command_ptr create_cr_and_sub_command(node_weak_ptr sender);
public:
	static void init_weights(const weights_vector& in);
private:
	static weights_vector validate_weights_v(const weights_vector& in);
	static void weights_normalization(weights_vector& in);
};