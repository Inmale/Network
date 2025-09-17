#pragma once
#include <memory>
#include "node_handlers.h"
#include <random>
#include <unordered_map>

class IEventHandler;
class Node;
enum EHandlerType;

class HandlerFabric
{
	enum EHandlerType
	{
		SUM,
		COUNT
	};
public:
	using handler_ptr = std::shared_ptr<IEventHandler>;
	using node_ptr = std::shared_ptr<Node>;
	using creater_ptr = handler_ptr(*)(node_ptr, size_t);
	using handlers_map = std::unordered_map<EHandlerType, creater_ptr>;

	static handler_ptr create_random_handler(node_ptr sender, size_t recipient_id);
private:
	static int get_int_handler_distribution();
	static std::mt19937& get_rn_generator();

	static handler_ptr create_handler(EHandlerType type, node_ptr sender, size_t recipient_id);

	static handlers_map& get_creators_map();
	static handlers_map init_creators_map();

	static handler_ptr create_sum_handler(node_ptr sender, size_t recipient_id);
	static handler_ptr create_count_handler(node_ptr sender, size_t recipient_id);
};