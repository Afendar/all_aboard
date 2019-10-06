#pragma once

#include <string>
#include "Screen.h"
#include "item/Item.h"

class Font {
	public:
		Font();
		virtual ~Font();

		static void init();

		static void draw(std::string msg, Screen* screen, int x, int y, sf::Font font, int col, int size);
		static void renderFrame(Screen* screen, std::string title, int x0, int y0, int x1, int y1);
		static void renderAchievement(Screen* screen, std::string label, Item* item, int x0, int y0, int x1, int y1, int alpha = 255);

		static sf::Font m_font, m_fontPirate;
};