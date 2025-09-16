#pragma once

class Network
{
	static void init();
	static void update();

	static void create_random_nodes(size_t num);

	static void forming_handles_queue();
	static void update_nodes_state();
};