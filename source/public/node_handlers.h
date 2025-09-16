#pragma once
#include <memory>
#include <unordered_map>

class Node;
using node_ptr = std::shared_ptr<Node>;

class IEventHandler
{
public:
	//TODO: needs add handlers list
	virtual void handle(int value) = 0;
	virtual ~IEventHandler() {}
};

class SumHandler : public IEventHandler
{
	size_t m_recipient_id{ 0 };
	node_ptr m_sender;

	int m_sum{ 0 };
public:
	SumHandler(node_ptr sender, size_t recipient_id)
		: m_sender(sender), m_recipient_id(recipient_id) {};
	virtual void handle(int value);
	virtual ~SumHandler() {}
};

class CountHandler : public IEventHandler
{
	size_t m_recipient_id{ 0 };
	node_ptr m_sender;

	int m_count{ 0 };
public:
	CountHandler(node_ptr sender, size_t recipient_id)
		: m_sender(sender), m_recipient_id(recipient_id) {};
	virtual void handle(int);
	virtual ~CountHandler() {};
};