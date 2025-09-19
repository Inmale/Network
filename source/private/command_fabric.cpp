#include "command_fabric.h"
#include "random_generator.h"
#include <numeric>

constexpr float default_command_chance{ 10.0f };

command_ptr CommandFabric::create_random_command(node_weak_ptr sender)
{
	auto index{ get_random_command_index() };
	if (index > get_creators_map().size() - 1)
		return command_ptr{};
	return create_command((ECommandType)index, sender);
}

int CommandFabric::get_random_command_index()
{
	auto r{ get_random_float_zero_one() };

	int choice{ 0 };
	while ((choice < m_weights.size()) && (r > m_weights[choice]))
		++choice;
	return choice;
}

float CommandFabric::get_random_float_zero_one()
{
	static std::uniform_real_distribution<float> f_dist(0.0f, 1.0f);
	return f_dist(RandomGenerator::get_rn_generator());
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

void CommandFabric::init_weights(const weights_vector& in)
{
	auto validated{ validate_weights_v(in) };
	weights_normalization(validated);
}

CommandFabric::weights_vector CommandFabric::validate_weights_v(const weights_vector& in)
{
	size_t in_size{ 0 };
	if (in.size() > get_creators_map().size() + 1)
		in_size = get_creators_map().size() + 1;
	else
		in_size = in.size();
	auto target_size{ m_weights.size() };
	weights_vector validated(target_size);

	for (size_t i = 0; i < in_size; i++)
		validated[i] = in[i];

	if (in_size < target_size)
		for (size_t i = in_size; i < target_size; i++)
			validated[i] = default_command_chance;
	return validated;
}

void CommandFabric::weights_normalization(weights_vector& in)
{
	auto sum{ std::accumulate(in.begin(), in.end(), 0.0f) };
	if (sum == 0.0f)
		return;
	for (float& w : in)
		w /= sum;

	std::partial_sum(in.begin(), in.end(), m_weights.begin());
}

CommandFabric::weights_vector CommandFabric::m_weights = CommandFabric::weights_vector(CommandFabric::get_creators_map().size() + 1);