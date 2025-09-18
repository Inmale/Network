#include "handler_fabric.h"
#include "random_generator.h"
#include "command_fabric.h"

class Node;

handler_ptr HandlerFabric::create_random_handler(node_weak_ptr sender, size_t recipient_id)
{
	return create_handler((EHandlerType)get_int_handler_distribution(), sender, recipient_id);
}

int HandlerFabric::get_int_handler_distribution()
{
	static std::uniform_int_distribution<int> int_dist(0, (int)(get_creators_map().size() - 1));
	return int_dist(RandomGenerator::get_rn_generator());
}

handler_ptr HandlerFabric::create_handler(EHandlerType type, node_weak_ptr sender, size_t recipient_id)
{
	auto creator{ get_creators_map().at(type) };
	if (creator != nullptr)
		return creator(sender, recipient_id);
	return handler_ptr();
}

typename HandlerFabric::handlers_map& HandlerFabric::get_creators_map()
{
	static handlers_map handlers = init_creators_map();
	return handlers;
}

typename HandlerFabric::handlers_map HandlerFabric::init_creators_map()
{
	handlers_map handlers;
	handlers.insert({ EHandlerType::SUM, &create_sum_handler });
	handlers.insert({ EHandlerType::COUNT, &create_count_handler });
	return handlers;
}

handler_ptr HandlerFabric::create_sum_handler(node_weak_ptr sender, size_t recipient_id)
{
	return std::make_shared<SumHandler>(sender, recipient_id);
}

handler_ptr HandlerFabric::create_count_handler(node_weak_ptr sender, size_t recipient_id)
{
	return std::make_shared<CountHandler>(sender, recipient_id);;
}