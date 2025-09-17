#include "node_handlers.h"
#include "node.h"
#include <iostream>

void SumHandler::handle(int value)
{
	if (!m_sender.expired())
	{
		m_sum += value;
		std::cout << m_sender.lock()->get_id() << "->" << m_recipient_id << ": S = " << m_sum << std::endl;
	}
}

void CountHandler::handle(int)
{
	if (!m_sender.expired())
	{
		++m_count;
		std::cout << m_sender.lock()->get_id() << "->" << m_recipient_id << ": N = " << m_count << std::endl;
	}
}