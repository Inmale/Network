#pragma once
#include <memory>

class Node;

class NodeFabric
{
	static std::shared_ptr<Node> create_random_node();
};