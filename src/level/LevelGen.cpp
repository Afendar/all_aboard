#include "LevelGen.h"
#include <cmath>
#include <iostream>

Random* LevelGen::m_random = new Random();

LevelGen::LevelGen(int w, int h, int featureSize)
{
	m_w = w;
	m_h = h;
	m_widthMinusOne = w - 1;
	m_heightMinusOne = h - 1;

	m_values = new float[w * h];

	for (int y = 0; y < w; y += featureSize) {
		for (int x = 0; x < w; x += featureSize) {
			setSample(x, y, m_random->nextFloat() * 2 - 1);
		}
	}

	int stepSize = featureSize;
	float scale = 1.0 / w;
	float scaleMod = 1;

	do {
		int halfStep = stepSize / 2;
		float stepSizeByScale = stepSize * scale;
		for (int y = 0; y < w; y += stepSize) {
			for (int x = 0; x < w; x += stepSize) {
				float a = sample(x, y);
				float b = sample(x + stepSize, y);
				float c = sample(x, y + stepSize);
				float d = sample(x + stepSize, y + stepSize);

				float e = (a + b + c + d) / 4.0
					+ (m_random->nextFloat() * 2 - 1) * stepSizeByScale;
				setSample(x + halfStep, y + halfStep, e);
			}
		}

		stepSizeByScale /= 2;

		for (int y = 0; y < w; y += stepSize) {
			for (int x = 0; x < w; x += stepSize) {
				float a = sample(x, y);
				float b = sample(x + stepSize, y);
				float c = sample(x, y + stepSize);
				float d = sample(x + halfStep, y + halfStep);
				float e = sample(x + halfStep, y - halfStep);
				float f = sample(x - halfStep, y + halfStep);

				float H = (a + b + d + e) / 4.0
					+ (m_random->nextFloat() * 2 - 1) * stepSizeByScale;
				float g = (a + c + d + f) / 4.0
					+ (m_random->nextFloat() * 2 - 1) * stepSizeByScale;
				setSample(x + halfStep, y, H);
				setSample(x, y + halfStep, g);
			}
		}

		stepSize /= 2;
		scale *= (scaleMod + 0.8);
		scaleMod *= 0.3;
	} while (stepSize > 1);
}

LevelGen::~LevelGen()
{
	delete[] m_values;
}

byte** LevelGen::createMap()
{
	int attempt = 0;
	int w = 128;
	int h = 128;
	byte ** result = NULL;

	do
	{
		if (result)
		{
			delete result[0];
			delete result[1];
			delete[] result;
		}
		result = createTopMap(w, h);

		int count[256];

		for (int i = 0; i < w * h; i++)
		{
			count[result[0][i] & 0xff]++;
		}

		return result;

	} while (true);
}

inline float LevelGen::sample(int x, int y)
{
	return m_values[(x & m_widthMinusOne) + (y & m_heightMinusOne) * m_w];
}

inline void LevelGen::setSample(int x, int y, float value) {
	m_values[(x & m_widthMinusOne) + (y & m_heightMinusOne) * m_w] = value;
}

byte** LevelGen::createTopMap(int w, int h)
{
	LevelGen mnoise1(w, h, 16);
	LevelGen mnoise2(w, h, 16);
	LevelGen mnoise3(w, h, 16);

	LevelGen noise1(w, h, 32);
	LevelGen noise2(w, h, 32);

	byte * map = new byte[w * h];
	byte * data = new byte[w * h];
	memset(data, 0, w * h * sizeof(byte));

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int i = x + y * w;

			float val = std::abs(noise1.m_values[i] - noise2.m_values[i]) * 3 - 2;
			float mval = std::abs(mnoise1.m_values[i] - mnoise2.m_values[i]);
			mval = std::abs(mval - mnoise3.m_values[i]) * 3 - 2;

			float xd = x / (w - 1.0) * 2 - 1;
			float yd = y / (h - 1.0) * 2 - 1;
			if (xd < 0)
				xd = -xd;
			if (yd < 0)
				yd = -yd;
			float dist = xd >= yd ? xd : yd;
			if (dist != 1.0)
			{
				dist *= dist;
				dist *= dist;
				dist *= dist;
				dist *= dist;
			}

			val = val + 1 - dist * 20;

			if (val < -0.5) {
				map[i] = Tile::m_water->getId();
			}
			else {
				map[i] = Tile::m_grass->getId();
			}

			if (val > 0 && mval < 0 && mval > -0.7) {
				map[i] = Tile::m_path->getId();
			}
		}
	}

	for (int i = 0; i < w * h / 500; i++) {
		int x = m_random->nextInt(w);
		int y = m_random->nextInt(h);
		for (int j = 0; j < 200; j++) {
			int xx = x + m_random->nextInt(15) - m_random->nextInt(15);
			int yy = y + m_random->nextInt(15) - m_random->nextInt(15);
			if (xx >= 0 && yy >= 0 && xx < w && yy < h) {
				if (map[xx + yy * w] == Tile::m_grass->getId()) {
					map[xx + yy * w] = Tile::m_tree->getId();
				}
			}
		}
	}

	for (int i = 0; i < w*h / 1500; i++) {
		int x = m_random->nextInt(w);
		int y = m_random->nextInt(h);
		for (int j = 0; j < 10; j++) {
			int xx = x + m_random->nextInt(15) - m_random->nextInt(15);
			int yy = y + m_random->nextInt(15) - m_random->nextInt(15);
			if (xx >= 0 && yy >= 0 && xx < w && yy < h) {
				if (map[xx + yy * w] == Tile::m_grass->getId()) {
					map[xx + yy * w] = Tile::m_bush->getId();
					data[xx + yy * w] = (byte)101;
				}
			}
		}
	}

	for (int i = 0; i < 40; i++) {
		int x = m_random->nextInt(w);
		int y = m_random->nextInt(h);
		int col = m_random->nextInt(3);
		int xx = x + m_random->nextInt(6) - m_random->nextInt(6);
		int yy = y + m_random->nextInt(6) - m_random->nextInt(6);
		if (xx >= 0 && yy >= 0 && xx < w && yy < h) {
			if (map[xx + yy * w] == Tile::m_grass->getId()) {
				
				map[xx + yy * w] = Tile::m_gravestone->getId();
				data[xx + yy * w] = (byte)(col + m_random->nextInt(3) * 16);
				map[xx + 1 + yy * w] = Tile::m_gravestone->getId();
				data[xx + 1 + yy * w] = (byte)(col + m_random->nextInt(3) * 16);
				map[xx - 1 + yy * w] = Tile::m_gravestone->getId();
				data[xx - 1 + yy * w] = (byte)(col + m_random->nextInt(3) * 16);
				map[xx + (yy + 1) * w] = Tile::m_gravestone->getId();
				data[xx + (yy + 1) * w] = (byte)(col + m_random->nextInt(3) * 16);
				map[xx + 1 + (yy + 1) * w] = Tile::m_gravestone->getId();
				data[xx + 1 + (yy + 1) * w] = (byte)(col + m_random->nextInt(3) * 16);
				map[xx - 1 + (yy + 1) * w] = Tile::m_gravestone->getId();
				data[xx - 1 + (yy + 1) * w] = (byte)(col + m_random->nextInt(3) * 16);
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		map[59 + (44 + i) * w] = Tile::m_bridge->getId();
		map[60 + (44 + i) * w] = Tile::m_bridge->getId();
		data[59 + (44 + i) * w] = 1;
		data[60 + (44 + i) * w] = 1;
	}

	for (int i = 0 ; i < 5; i++) {
		map[33 + i + 28 * w] = Tile::m_bridge->getId();
		map[33 + i + 29 * w] = Tile::m_bridge->getId();
		data[33 + i + 28 * w] = 0;
		data[33 + i + 29 * w] = 0;

		map[45 + i + 68 * w] = Tile::m_bridge->getId();
		map[45 + i + 69 * w] = Tile::m_bridge->getId();
		data[45 + i + 68 * w] = 0;
		data[45 + i + 69 * w] = 0;
	}

	for (int i = 0; i < 6; i++) {
		map[96 + (79 + i) * w] = Tile::m_bridge->getId();
		map[97 + (79 + i) * w] = Tile::m_bridge->getId();
		data[96 + (79 + i) * w] = 1;
		data[97 + (79 + i) * w] = 1;
	}

	map[38 + 29 * w] = Tile::m_grass->getId();
	

	byte ** result = new byte*[2];
	result[0] = map;
	result[1] = data;
	return result;
}