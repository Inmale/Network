#include "network.h"
#include "node.h"
#include "command_fabric.h"
#include "random_generator.h"

void Network::init(const weights_vector& weights, size_t num_nodes)
{
	if (num_nodes == 0)
		m_num_nodes = get_random_num_nodes();
	else
		m_num_nodes = num_nodes;
	CommandFabric::init_weights(weights);
	create_nodes_from_num();
	create_nodes_sub();
}

size_t Network::get_random_num_nodes()
{
	std::uniform_int_distribution<size_t> num(m_min_start_nodes, m_max_start_nodes);
	return num(RandomGenerator::get_rn_generator());
}

void Network::create_nodes_from_num()
{
	for (size_t i = 0; i < m_num_nodes; i++)
		create_start_node();
}

void Network::create_start_node()
{
	auto node{ std::make_shared<Node>(get_new_id()) };
	auto w = node->weak_from_this();
	m_nodes.insert({ node->get_id(), node });
}

void Network::create_nodes_sub()
{
	if (!m_nodes.empty())
	{
		auto it{ m_nodes.begin() };
		auto prev{ it };

		++it;
		while (it != m_nodes.end())
		{
			prev->second->subscribe(it->second);
			prev = it;
			++it;
		}
		prev->second->subscribe(m_nodes.begin()->second);
	}
}

node_weak_ptr Network::create_node_from_command()
{
	auto node{ std::make_shared<Node>(get_new_id()) };
	m_new_nodes.insert({ node->get_id(), node });
	return node;
}

void Network::start_simulation()
{
	while(!m_nodes.empty())
	{
		update();
	}
}

void Network::update()
{
	forming_commands_queue();
	update_nodes_state();
	remove_single_nodes();
	copy_new_nodes();
}

void Network::forming_commands_queue()
{
	for (auto& node : m_nodes)
	{
		node_ptr df = node.second;
		auto command_ptr{ node.second->create_random_command() };
		if (command_ptr)
			m_commands.push_back(command_ptr);
	}
}

void Network::update_nodes_state()
{
	for (auto& command : m_commands)
		command->execute();
	m_commands.clear();
}

void Network::remove_single_nodes()
{
	for (auto it = m_nodes.begin(); it != m_nodes.end(); )
	{
		if (it->second && !it->second->is_valid()) {
			it = m_nodes.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Network::copy_new_nodes()
{
	if (!m_new_nodes.empty())
		for (auto& new_node : m_new_nodes)
			m_nodes.insert(new_node);
	m_new_nodes.clear();
}

size_t Network::get_new_id()
{
	return m_current_id++;
}

void Network::set_max_start_num_nodes(size_t num)
{
	if (num < m_min_start_nodes)
		m_max_start_nodes = m_min_start_nodes;
	else
		m_max_start_nodes = num;
}

size_t Network::m_num_nodes = 10;
size_t Network::m_max_start_nodes = 50;
size_t Network::m_min_start_nodes = 10;
size_t Network::m_current_id = 0;

Network::nodes_map Network::m_nodes = Network::nodes_map{};
Network::nodes_map Network::m_new_nodes = Network::nodes_map{};
Network::commands_v Network::m_commands = Network::commands_v{};
