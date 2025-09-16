#include "node.h"
#include "node_handlers.h"
#include <random>

Node::Node(const SNodeParameters& parameters)
	: m_id(parameters.m_id) {}

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

handler_ptr Node::get_random_handler()
{
	static std::mt19937 gen{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(0, 2);
	//TODO: needs add random generator
	return handler_ptr();
}

void Node::subscribe(node_ptr subscriber)
{
	if (subscriber && (subscriber->get_id() != m_id))
		if (m_subscribers.insert({ subscriber->get_id(), subscriber }).second)
		{
			subscriber->m_subscriptions.insert({ m_id, shared_from_this() });
			m_handlers.insert({ m_id, get_random_handler() });
		}
}

void Node::unsubscribe(node_ptr subscriber)
{
	if (subscriber)
	{
		m_subscribers.erase(subscriber->get_id());
		subscriber->m_subscriptions.erase(m_id);
	}
}

bool Node::is_valid() const
{
	return !m_subscriptions.empty() || !m_subscribers.empty();
}