#include "node_fabric.h"
#include "node.h"

std::shared_ptr<Node> NodeFabric::create_node(size_t id)
{
	return std::make_shared<Node>(id);
}
