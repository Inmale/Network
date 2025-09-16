#pragma once
#include "commands.h"
#include <unordered_map>

class IEventHandler;
class Node;

using nodes_umap = std::unordered_map<size_t, std::weak_ptr<Node>>;
using node_w_ptr = std::weak_ptr<Node>;
using handler_ptr = std::shared_ptr<IEventHandler>;

struct SNodeParameters
{
	size_t m_id{ 0 };

	SNodeParameters() {}
	SNodeParameters(size_t id) : m_id(id) {}
};

class Node : std::enable_shared_from_this<Node>
{
	size_t m_id{ 0 };
	std::unordered_map<size_t, handler_ptr> m_handlers;
	nodes_umap m_subscriptions;
	nodes_umap m_subscribers;
public:
	Node(const SNodeParameters& parameters);

	void handle(int value);
private:
	void execute_handler(size_t subscription_id, int value);
	handler_ptr get_random_handler();
public:
	void subscribe(node_ptr subscriber);
	void unsubscribe(node_ptr subscriber);
	inline size_t get_id() const { return m_id; }
	bool is_valid() const;
};