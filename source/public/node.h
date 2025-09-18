#pragma once
#include "commands.h"
#include <unordered_map>

class IEventHandler;
class Node;

using handler_ptr = std::shared_ptr<IEventHandler>;

struct SNodeParameters
{
	size_t m_id{ 0 };

	SNodeParameters() {}
	SNodeParameters(size_t id) : m_id(id) {}
};

class Node : std::enable_shared_from_this<Node>
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
	Node(const SNodeParameters& parameters);
	Node(size_t id) : m_id(id) {}

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