#pragma once
#include <random>

class RandomGenerator
{
public:
	static std::mt19937& get_rn_generator();
};