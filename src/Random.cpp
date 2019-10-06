#include "Random.h"

Random::Random(unsigned int seed)
{
	srand(64);
}

Random::~Random()
{
}

int Random::nextInt(int max)
{
	return 0 + (rand() % static_cast<int>(max - 0 + 1));
}

float Random::nextFloat()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

bool Random::nextBoolean()
{
	return nextInt(2);
}
