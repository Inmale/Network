#include <iostream>
#include "network.h"

static void read_chance(weights_vector& weights)
{
    float input{ 0.0 };
    std::cin >> input;
    weights.push_back(input);
}

int main()
{
    weights_vector weights;

    std::cout << "Create Value chances: \n";
    read_chance(weights);

    std::cout << "Subscribe chances: \n";
    read_chance(weights);

    std::cout << "Unsubscribe chances: \n";
    read_chance(weights);

    std::cout << "Create node and Subscribe chances: \n";
    read_chance(weights);

    std::cout << "No action chance: \n";
    read_chance(weights);

    Network::set_max_start_num_nodes(300);
    Network::init(weights);
    Network::start_simulation();
}