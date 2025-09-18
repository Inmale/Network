#include "random_generator.h"

std::mt19937& RandomGenerator::get_rn_generator()
{
	static std::mt19937 gen{ std::random_device{}() };
	return gen;
}