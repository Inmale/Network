#include "commands.h"
#include "node.h"

void CreateValueCommand::execute()
{
	if (!m_sender.expired())
		m_sender.lock()->handle(m_value);
}

void SubscribeCommand::execute()
{
	if (!m_sender.expired() && !m_subscription.expired())
		m_subscription.lock()->subscribe(m_sender);
}

void UnsubscribeCommand::execute()
{
	if (!m_sender.expired() && !m_subscription.expired())
		m_subscription.lock()->unsubscribe(m_sender);
}

void CreateAndSubcribeCommand::execute()
{
	auto new_node{ create_subscription() };
	SubscribeCommand::set_subscription(new_node);
	SubscribeCommand::execute();
}

typename CreateAndSubcribeCommand::node_ptr CreateAndSubcribeCommand::create_subscription()
{
	//TODO:Create new node
	return node_ptr();
}
