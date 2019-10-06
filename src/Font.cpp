#include "Font.h"

#include <iostream>

sf::Font Font::m_font;
sf::Font Font::m_fontPirate;

Font::Font()
{

}

Font::~Font()
{
}

void Font::init() {
	if (!m_font.loadFromFile("gfx/pixelmix.ttf")) {
		std::cerr << "Unable to load file 'gfx/pixelmix.ttf'" << std::endl;
	}
	if(!m_fontPirate.loadFromFile("gfx/piratesbay.ttf")){
		std::cerr << "Unable to load file 'gfx/piratesbay.ttf'" << std::endl;
	}
}

void Font::draw(std::string msg, Screen* screen, int x, int y, sf::Font font, int col, int size) {
	sf::Text t;
	t.setString(msg);
	t.setFont(font);
	t.setPosition(x, y);
	t.setCharacterSize(size);
	t.setFillColor(sf::Color(col));
	screen->getRenderWindow()->draw(t);
}

void Font::renderFrame(Screen* screen, std::string title, int x0, int y0, int x1, int y1) {
	for (int y = y0; y <= y1; y++) {
		for (int x = x0; x <= x1; x++) {
			if (x == x0 && y == y0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28, -1);
			}
			else if (x == x1 && y == y0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28, -1, 1);
			}
			else if (x == x0 && y == y1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28, -1, 2);
			}
			else if (x == x1 && y == y1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28, -1, 3);
			}
			else if (y == y0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 29, -1);
			}
			else if (y == y1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 29, -1, 2);
			}
			else if (x == x0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 30, -1);
			}
			else if (x == x1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 30, -1, 1);
			}
			else {
				screen->renderSquare(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, TILE_SIZE, TILE_SIZE, sf::Color(198, 187, 153).toInteger());
			}
		}
	}

	if(title != "")
		draw(title, screen, x0 * 32 + 32, y0 * 32 + 32, Font::m_font, sf::Color(68, 57, 52).toInteger(), 14);
}

void Font::renderAchievement(Screen* screen, std::string label, Item* item, int x0, int y0, int x1, int y1, int alpha) {
	for (int y = y0; y <= y1; y++) {
		for (int x = x0; x <= x1; x++) {
			if (x == x0 && y == y0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28 + 32, sf::Color(255, 255, 255, alpha).toInteger());
			}
			else if(x == x0 + 1 && y == y0 + 1) {
				screen->renderSquare(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, TILE_SIZE, TILE_SIZE, sf::Color(136, 105, 83, alpha).toInteger());
				screen->render(x * TILE_SIZE * SCALE - (TILE_SIZE * SCALE) / 2, y * TILE_SIZE * SCALE, 31 + 32, sf::Color(255, 255, 255, alpha).toInteger());
				item->renderIcon(screen, x * TILE_SIZE * SCALE - (TILE_SIZE * SCALE) / 2, y * TILE_SIZE * SCALE, alpha);
			}
			else if (x == x1 && y == y0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28 + 32, sf::Color(255, 255, 255, alpha).toInteger(), 1);
			}
			else if (x == x0 && y == y1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28 + 32, sf::Color(255, 255, 255, alpha).toInteger(), 2);
			}
			else if (x == x1 && y == y1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28 + 32, sf::Color(255, 255, 255, alpha).toInteger(), 3);
			}
			else if (y == y0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 29 + 32, sf::Color(255, 255, 255, alpha).toInteger());
			}
			else if (y == y1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 29 + 32, sf::Color(255, 255, 255, alpha).toInteger(), 2);
			}
			else if (x == x0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 30 + 32, sf::Color(255, 255, 255, alpha).toInteger());
			}
			else if (x == x1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 30 + 32, sf::Color(255, 255, 255, alpha).toInteger(), 1);
			}
			else {
				screen->renderSquare(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, TILE_SIZE, TILE_SIZE, sf::Color(136, 105, 83, alpha).toInteger());
			}
		}
	}

	draw("Completed !!!", screen, x0 * TILE_SIZE * SCALE + 2 * TILE_SIZE * SCALE - 9, y0 * TILE_SIZE * SCALE + 28, Font::m_font, sf::Color(128, 209, 124, alpha).toInteger(), 13);
	draw(label, screen, x0 * TILE_SIZE * SCALE + 2 * TILE_SIZE * SCALE - 9, y0 * 4 * TILE_SIZE + 18, Font::m_font, sf::Color(255, 255, 255, alpha).toInteger(), 12);
}