#include "command_fabric.h"
#include "random_generator.h"

command_ptr CommandFabric::create_random_command(node_weak_ptr sender)
{
	return create_command((ECommandType)get_int_command_distribution(), sender);
}

int CommandFabric::get_int_command_distribution()
{
	static std::uniform_int_distribution<int> int_dist(0, (int)(get_creators_map().size() - 1));
	return int_dist(RandomGenerator::get_rn_generator());
}

command_ptr CommandFabric::create_command(ECommandType type, node_weak_ptr sender)
{
	auto creator{ get_creators_map().at(type) };
	if (creator != nullptr)
		return creator(sender);
	return command_ptr();
}

typename CommandFabric::commands_map& CommandFabric::get_creators_map()
{
	static commands_map commands = init_creators_map();
	return commands;
}

typename CommandFabric::commands_map CommandFabric::init_creators_map()
{
	commands_map commands;
	commands.insert({ ECommandType::CREATE_VALUE, &create_gen_value_command });
	commands.insert({ ECommandType::SUBSCRIBE, &create_subscribe_command });
	commands.insert({ ECommandType::UNSUBSCRIBE, &create_unsubscribe_command });
	commands.insert({ ECommandType::CREATE_SUB_NODE, &create_cr_and_sub_command });
	return commands;
}

command_ptr CommandFabric::create_gen_value_command(node_weak_ptr sender)
{
	if (!sender.expired())
		return std::make_shared<GenerateValueCommand>(sender);
	return command_ptr();
}

command_ptr CommandFabric::create_subscribe_command(node_weak_ptr sender)
{
	if (!sender.expired())
		return std::make_shared<SubscribeCommand>(sender);
	return command_ptr();
}

command_ptr CommandFabric::create_unsubscribe_command(node_weak_ptr sender)
{
	if (!sender.expired())
		return std::make_shared<UnsubscribeCommand>(sender);
	return command_ptr();
}

command_ptr CommandFabric::create_cr_and_sub_command(node_weak_ptr sender)
{
	if (!sender.expired())
		return std::make_shared<CreateAndSubcribeCommand>(sender);
	return command_ptr();
}