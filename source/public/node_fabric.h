#pragma once
#include <memory>

class Node;
struct SNodeParameters;

class NodeFabric
{
	static std::shared_ptr<Node> create_node(size_t id);
};