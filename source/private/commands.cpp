#include "commands.h"
#include "node.h"

void CreateValueCommand::execute()
{
	if (m_sender)
		m_sender->handle(m_value);
}

void SubscribeCommand::execute()
{
	if (m_sender && m_subscription)
		m_subscription->subscribe(m_sender);
}

void UnsubscribeCommand::execute()
{
	if (m_sender && m_subscription)
		m_subscription->unsubscribe(m_sender);
}

void CreateAndSubcribeCommand::execute()
{
	auto new_node{ create_subscription() };
	SubscribeCommand::set_subscription(new_node);
	SubscribeCommand::execute();
}

node_ptr CreateAndSubcribeCommand::create_subscription()
{
	//TODO:Create new node
	return node_ptr();
}
