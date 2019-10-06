#pragma once

#include <SFML/Graphics.hpp>

class Spritesheet {
	public:
		Spritesheet(std::string file);
		virtual ~Spritesheet();

		sf::Sprite getSprite(int x, int y, int color, int flip);
		sf::Sprite getSprite(int x, int y, int w, int h, int color, int flip);
		sf::Sprite getFontSprite(int x, int y, int w, int h, int color, int flip);

	private:
		sf::Texture m_texture;
};