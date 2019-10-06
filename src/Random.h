#pragma once

#include <stdlib.h>
#include <time.h>
#include <math.h>

class Random {
	public:

		Random(unsigned int seed = 0);
		virtual ~Random();
		int nextInt(int);
		float nextFloat();
		bool nextBoolean();
};