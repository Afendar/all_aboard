#pragma once

#include <cstring>

#include "tile/Tile.h"
#include "../Random.h"

typedef unsigned int byte;

class LevelGen {
	public:

		LevelGen(int w, int h, int featureSize);
		virtual ~LevelGen();

		static byte** createMap();
		
	private:

		inline float sample(int x, int y);
		inline void setSample(int x, int y, float value);

		static byte** createTopMap(int w, int h);
		
		static Random* m_random;
		float* m_values;
		int m_w, m_h;
		int m_widthMinusOne, m_heightMinusOne;
};