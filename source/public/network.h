#pragma once
#include <unordered_map>
#include <memory>

class ICommand;
class Node;

using node_weak_ptr = std::weak_ptr<Node>;
using node_ptr = std::shared_ptr<Node>;
using weights_vector = std::vector<float>;

class Network
{
public:
	using nodes_map = std::unordered_map<size_t, node_ptr>;
	using commands_v = std::vector<std::shared_ptr<ICommand>>;
private:
	static size_t m_num_nodes;
	static size_t m_min_start_nodes;
	static size_t m_max_start_nodes;

	static size_t m_current_id;

	static nodes_map m_nodes;
	static nodes_map m_new_nodes;

	static commands_v m_commands;
public:
	static void init(const weights_vector& weights, size_t num_nodes = 0);
private:
	static size_t get_random_num_nodes();
	static void create_nodes_from_num();
	static void create_start_node();
	static void create_nodes_sub();
public:
	static node_weak_ptr create_node_from_command();
	static void start_simulation();
private:
	static void update();
	static void forming_commands_queue();
	static void update_nodes_state();
	static void remove_single_nodes();
	static void copy_new_nodes();

	static size_t get_new_id();
public:
	static void set_max_start_num_nodes(size_t num);
};