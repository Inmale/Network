#include "commands.h"
#include "node.h"
#include "random_generator.h" 
#include "network.h"

void GenerateValueCommand::execute()
{
	if (!m_sender.expired())
		m_sender.lock()->handle(generate_value());
}

int GenerateValueCommand::generate_value()
{
	std::uniform_int_distribution<int> int_dist(0, g_max_gen_value);
	return int_dist(RandomGenerator::get_rn_generator());
}

void SubscribeCommand::execute()
{
	if (!m_sender.expired())
		m_sender.lock()->sub_from_random_node();
}

void UnsubscribeCommand::execute()
{
	if (!m_sender.expired())
		m_sender.lock()->unsub_from_random_node();
}

void CreateAndSubcribeCommand::execute()
{
	auto new_node{ create_subscription() };
	m_sender.lock()->subscribe(new_node);
}

node_weak_ptr CreateAndSubcribeCommand::create_subscription()
{
	auto new_node{ Network::create_node_from_command() };
	if (!new_node.expired())
		return new_node;
	return node_weak_ptr();
}
