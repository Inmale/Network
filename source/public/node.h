#pragma once
#include "commands.h"
#include <unordered_map>

class ICommand;
class IEventHandler;
class Node;

using command_ptr = std::shared_ptr<ICommand>;
using handler_ptr = std::shared_ptr<IEventHandler>;

class Node : public std::enable_shared_from_this<Node>
{
public:
	using node_ptr = std::shared_ptr<Node>;
	using node_weak_ptr = std::weak_ptr<Node>;
	using nodes_umap = std::unordered_map<size_t, node_weak_ptr>;
private:
	size_t m_id{ 0 };
	std::unordered_map<size_t, handler_ptr> m_handlers;
	nodes_umap m_subscriptions;
	nodes_umap m_subscribers;
public:
	Node(size_t id) : m_id(id) {}

	command_ptr create_random_command();
	void handle(int value);
private:
	void execute_handler(size_t subscription_id, int value);
public:
	void sub_from_random_node();
	void subscribe(node_weak_ptr subscription);
public:
	void unsub_from_random_node();
private:
	void unsubscription(node_weak_ptr subscription);
public:
	inline size_t get_id() const { return m_id; }
	bool is_valid() const;
};