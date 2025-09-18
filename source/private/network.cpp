#include "network.h"

void Network::init()
{
	create_nodes_from_num();
	create_nodes_sub();
}

void Network::create_nodes_from_num()
{
	for (size_t i = 0; i < m_num_nodes; i++)
	{
		create_node();
	}
}

void Network::create_nodes_sub()
{

}

void Network::update()
{

}

node_weak_ptr Network::create_node()
{
	return node_weak_ptr();
}

size_t Network::get_new_id()
{
	return size_t();
}

void Network::forming_handles_queue()
{

}

void Network::update_nodes_state()
{

}

size_t Network::m_num_nodes = 10;

typename Network::nodes_map Network::m_nodes = typename Network::nodes_map{};
typename Network::nodes_map Network::m_new_nodes = typename Network::nodes_map{};