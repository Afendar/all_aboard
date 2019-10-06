#pragma once

#include "Particle.h"

#include "../Screen.h"

class HitParticle : public Particle {
	public:
		HitParticle(int x, int y);
		virtual ~HitParticle();

		double m_xa, m_ya, m_za;
		double m_xx, m_yy, m_zz;

		int m_alpha;

		void tick();
		void render(Screen* screen);

private:
	
	int m_time;
};