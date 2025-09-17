#include "node.h"
#include "handler_fabric.h"

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

void Node::subscribe(node_w_ptr subscriber)
{
	if (!subscriber.expired() && (subscriber.lock()->get_id() != m_id))
		if (m_subscribers.insert({ subscriber.lock()->get_id(), subscriber}).second)
		{
			subscriber.lock()->m_subscriptions.insert({m_id, shared_from_this()});
			subscriber.lock()->m_handlers.insert({m_id, HandlerFabric::create_random_handler(shared_from_this(), subscriber.lock()->get_id())});
		}
}

void Node::unsubscribe(node_w_ptr subscriber)
{
	if (!subscriber.expired())
	{
		m_subscribers.erase(subscriber.lock()->get_id());
		subscriber.lock()->m_subscriptions.erase(m_id);
	}
}

bool Node::is_valid() const
{
	return !m_subscriptions.empty() || !m_subscribers.empty();
}