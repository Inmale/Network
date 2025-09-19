#include "node_handlers.h"
#include "node.h"
#include <iostream>
#include <iomanip>

constexpr int field_width{ 5 };

void SumHandler::handle(int value)
{
	if (!m_sender.expired())
	{
		m_sum += value;
		std::cout << std::setw(field_width) << m_sender.lock()->get_id()
			<< "->" << std::setw(field_width) << m_recipient_id << ": S = " << m_sum << std::endl;
	}
}

void CountHandler::handle(int)
{
	if (!m_sender.expired())
	{
		++m_count;
		std::cout << std::setw(field_width) << m_sender.lock()->get_id()
			<< "->" << std::setw(field_width) << m_recipient_id << ": N = " << m_count << std::endl;
	}
}