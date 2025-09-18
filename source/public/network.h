#pragma once
#include <unordered_map>
#include <memory>

class Node;

using node_weak_ptr = std::weak_ptr<Node>;
using node_ptr = std::shared_ptr<Node>;

class Network
{
public:
	using nodes_map = std::unordered_map<size_t, node_ptr>;
private:
	static size_t m_num_nodes;

	static nodes_map m_nodes;
	static nodes_map m_new_nodes;

	static void init();
	static void create_nodes_from_num();
	static void create_nodes_sub();
	static void update();

public:
	static node_weak_ptr create_node();
	static size_t get_new_id();

	static void forming_handles_queue();
	static void update_nodes_state();
};