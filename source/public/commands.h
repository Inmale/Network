#pragma once
#include <vector>
#include <memory>

constexpr int g_max_gen_value{ 50 };

class Node;
using node_weak_ptr = std::weak_ptr<Node>;

class ICommand
{
public:
	using command_ptr = std::shared_ptr<ICommand>;
	using command_weak_ptr = std::weak_ptr<ICommand>;

	virtual void execute() = 0;
	virtual ~ICommand() = default;
};

class GenerateValueCommand : public ICommand
{
	node_weak_ptr m_sender;
public:
	GenerateValueCommand(node_weak_ptr sender) : m_sender(sender) {}

	virtual void execute() override;
private:
	int generate_value();
public:
	virtual ~GenerateValueCommand() {}
};

class SubscribeCommand : public ICommand
{
protected:
	node_weak_ptr m_sender;
public:
	SubscribeCommand(node_weak_ptr sender) : m_sender(sender) {}
	virtual void execute() override;

	virtual ~SubscribeCommand() {}
};

class UnsubscribeCommand : public ICommand
{
	node_weak_ptr m_sender;
public:
	UnsubscribeCommand(node_weak_ptr sender) : m_sender(sender) {}

	virtual void execute() override;
	virtual ~UnsubscribeCommand() {}
};

class CreateAndSubcribeCommand : public SubscribeCommand
{
public:
	CreateAndSubcribeCommand(node_weak_ptr sender) : SubscribeCommand(sender) {}

	virtual void execute() override;
	virtual ~CreateAndSubcribeCommand() {}
private:
	node_weak_ptr create_subscription();
};