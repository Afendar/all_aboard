#pragma once

#include <string>

#include "../Screen.h"
#include "../particle/Particle.h"

class TextParticle : public Particle {
public:
	TextParticle(std::string msg, int x, int y, int color);
	TextParticle(int num, int x, int y, int color);
	void init(std::string msg, int x, int y, int color);
	virtual ~TextParticle();

	double m_xa, m_ya, m_za;
	double m_xx, m_yy, m_zz;

	int m_alpha;

	void tick();
	void render(Screen* screen);

private:

	std::string m_msg;
	int m_color;
	int m_time;
};