#include "Spritesheet.h"

Spritesheet::Spritesheet(std::string file)
{
	m_texture.loadFromFile(file);
}

Spritesheet::~Spritesheet()
{
}

sf::Sprite Spritesheet::getSprite(int x, int y, int color, int flip)
{
	sf::Sprite s;
	s.setTexture(m_texture);
	s.setTextureRect(sf::IntRect(
		flip == 1 || flip == 3 ? x * 16 + 16 : x * 16, 
		flip == 2 || flip == 3 ? y * 16 + 16 : y * 16, 
		flip == 1 || flip == 3 ? -16 : 16, 
		flip == 2 || flip == 3 ? -16 : 16
	));

	if (color >= 0) {
		int a = (color >> 24) & 255;
		int r = (color >> 16) & 255;
		int g = (color >> 8) & 255;
		int b = color & 255;
		s.setColor(sf::Color(176, 144, 113, 255));
	}

	return s;
}

sf::Sprite Spritesheet::getSprite(int x, int y, int w, int h, int color, int flip)
{
	sf::Sprite s;
	s.setTexture(m_texture);
	s.setTextureRect(sf::IntRect(
		flip == 1 || flip == 3 ? x * 16 + w : x * 16,
		flip == 2 || flip == 3 ? y * 16 + h : y * 16,
		flip == 1 || flip == 3 ? -w : w, 
		flip == 2 || flip == 3 ? -h : h
	));

	if (color >= 0) {
		int a = (color >> 24) & 255;
		int r = (color >> 16) & 255;
		int g = (color >> 8) & 255;
		int b = color & 255;
		s.setColor(sf::Color(r, g, b, a));
	}

	return s;
}

sf::Sprite Spritesheet::getFontSprite(int x, int y, int w, int h, int color, int flip) {
	sf::Sprite s;
	s.setTexture(m_texture);
	s.setTextureRect(sf::IntRect(
		flip == 1 || flip == 3 ? x * 8 + w : x * 8,
		flip == 2 || flip == 3 ? y * 16 + h : y * 16,
		flip == 1 || flip == 3 ? -w : w,
		flip == 2 || flip == 3 ? -h : h
	));

	if (color != -1) {
		s.setColor(sf::Color(color));
	}

	return s;
}