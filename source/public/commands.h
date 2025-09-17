#pragma once
#include <vector>
#include <memory>

class Node;

class ICommand
{
public:
	using node_ptr = std::weak_ptr<Node>;

	virtual void execute() = 0;
	virtual ~ICommand() = default;
};

class CreateValueCommand : public ICommand
{
	node_ptr m_sender;
	int m_value{ 0 };
public:
	CreateValueCommand(node_ptr sender, int value) : m_sender(sender), m_value(value) {}

	virtual void execute() override;
	inline int get_value() const { return m_value; }

	virtual ~CreateValueCommand() {}
};

class SubscribeCommand : public ICommand
{
	node_ptr m_sender;
	node_ptr m_subscription;
public:
	SubscribeCommand(node_ptr sender, node_ptr subscription) : m_sender(sender), m_subscription(subscription) {}
	SubscribeCommand(node_ptr sender) : m_sender(sender) {}

	inline void set_subscription(node_ptr subscription) { m_subscription = subscription; }
	virtual void execute() override;

	virtual ~SubscribeCommand() {}
};

class UnsubscribeCommand : public ICommand
{
	node_ptr m_sender;
	node_ptr m_subscription;
public:
	UnsubscribeCommand(node_ptr sender, node_ptr subscription) : m_sender(sender), m_subscription(subscription) {}

	virtual void execute() override;
	virtual ~UnsubscribeCommand() {}
};

class CreateAndSubcribeCommand : public SubscribeCommand
{
public:
	CreateAndSubcribeCommand(node_ptr sender) : SubscribeCommand(sender) {}

	virtual void execute() override;
private:
	node_ptr create_subscription();
};