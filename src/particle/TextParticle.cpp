#include "TextParticle.h"

#include "../Font.h"

TextParticle::TextParticle(std::string msg, int x, int y, int color)
{
	init(msg, x, y, color);
}

TextParticle::TextParticle(int num, int x, int y, int color)
{
	init(std::to_string(num), x, y, color);
}

void TextParticle::init(std::string msg, int x, int y, int color)
{
	m_msg = msg;
	m_x = x;
	m_y = y;
	m_color = color;
	m_time = 0;

	m_xx = x;
	m_yy = y;
	m_zz = 2;
	m_xa = m_random->nextFloat() * 0.3;
	m_ya = m_random->nextFloat() * 0.2;
	m_za = m_random->nextFloat() * 0.7 + 2;
}

TextParticle::~TextParticle()
{
}

void TextParticle::tick()
{
	m_time++;
	if (m_time > 80) {
		remove();
	}

	m_xx += m_xa;
	m_yy += m_ya;
	m_zz += m_za;

	if (m_zz < 0) {
		m_zz = 0;
		m_za *= -0.5;
		m_xa *= 0.6;
		m_ya *= 0.6;
	}

	m_za -= 0.15;
	m_x = (int)m_xx;
	m_y = (int)m_yy;
}

void TextParticle::render(Screen * screen)
{
	Font::draw(m_msg, screen, m_x - m_msg.length() * 4 + 1, m_y - (int)(m_zz)+1, Font::m_font, sf::Color(214, 86, 86).toInteger(), 14);
	Font::draw(m_msg, screen, m_x - m_msg.length() * 4, m_y - (int)(m_zz), Font::m_font, m_color, 14);
}
