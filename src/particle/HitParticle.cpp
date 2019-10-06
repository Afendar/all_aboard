#include "HitParticle.h"

#include "../Sound.h"

HitParticle::HitParticle(int x, int y)
{
	m_x = x;
	m_y = y;
	m_time = 0;
	Sound::m_hit->play();

	m_alpha = 255;

	m_xx = x;
	m_yy = y;
	m_zz = 2;
	m_xa = m_random->nextFloat() * 0.5;
	m_ya = m_random->nextFloat() * 0.7;
	m_za = m_random->nextFloat() * 0.7 + 2;
}

HitParticle::~HitParticle()
{
}

void HitParticle::tick()
{
	m_time++;
	m_alpha -= 4;
	if (m_time > 60) {
		remove();
	}

	m_xx += m_xa;
	m_yy += m_ya;
	m_zz += m_za;

	if (m_zz < 0){
		m_zz = 0;
		m_za *= -0.5;
		m_xa *= 0.6;
		m_ya *= 0.6;
	}

	m_za -= 0.15;
	m_x = (int)m_xx;
	m_y = (int)m_yy;
}

void HitParticle::render(Screen * screen)
{
	screen->render(m_x + (TILE_SIZE/2) * 4, m_y - (int)(m_zz)+1, 23, sf::Color(255,255,255, m_alpha).toInteger());
}
