#include "node.h"
#include "handler_fabric.h"
#include "random_generator.h"
#include "command_fabric.h"

command_ptr Node::create_random_command()
{
	return CommandFabric::create_random_command(weak_from_this());
}

void Node::handle(int value)
{
	for (auto& sub : m_subscribers)
		if (sub.second.lock())
			sub.second.lock()->execute_handler(m_id, value);
}

void Node::execute_handler(size_t subscription_id, int value)
{
	auto handler_it{ m_handlers.find(subscription_id) };
	if (handler_it != m_handlers.end())
		handler_it->second->handle(value);
}

void Node::sub_from_random_node()
{
	if (!m_subscribers.empty())
	{
		std::uniform_int_distribution<int> int_dist(0, (int)(m_subscribers.size() - 1));
		auto value{ int_dist(RandomGenerator::get_rn_generator()) };
		auto it{ m_subscribers.begin() };
		if (it != m_subscribers.end())
			subscribe((*it).second);
	}
}

void Node::subscribe(node_weak_ptr subscription)
{
	if (!subscription.expired())
		if (subscription.lock()->m_subscribers.insert({ get_id(), weak_from_this()}).second)
		{
			m_subscriptions.insert({ subscription.lock()->get_id(), subscription });
			m_handlers.insert({ subscription.lock()->get_id(), HandlerFabric::create_random_handler(subscription, get_id())});
		}
}

void Node::unsub_from_random_node()
{
	if (!m_subscriptions.empty())
	{
		std::uniform_int_distribution<int> int_dist(0, (int)(m_subscriptions.size() - 1));
		auto value{ int_dist(RandomGenerator::get_rn_generator()) };
		auto it{ m_subscriptions.begin() };
		std::advance(it, value);
		if (it != m_subscriptions.end())
			unsubscription((*it).second);
	}
}

void Node::unsubscription(node_weak_ptr subscription)
{
	if (!subscription.expired())
	{
		m_subscriptions.erase(subscription.lock()->get_id());
		subscription.lock()->m_subscribers.erase(get_id());
		m_handlers.erase(subscription.lock()->get_id());
	}
}

bool Node::is_valid() const
{
	return !m_subscriptions.empty() || !m_subscribers.empty();
}