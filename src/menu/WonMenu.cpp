#include "WonMenu.h"
#include "../Game.h"

WonMenu::WonMenu():
	m_inputDelay(60)
{
}

WonMenu::~WonMenu()
{
}

void WonMenu::tick()
{
	if (m_inputDelay > 0)
		m_inputDelay--;

	if (m_input->exit->clicked) {
		m_game->setMenu(NULL);
	}
}

void WonMenu::render(Screen* screen)
{
	screen->renderSquare(0, 0, screen->getWidth() * TILE_SIZE * SCALE, (screen->getHeight() + 1) * TILE_SIZE * SCALE, sf::Color(210, 198, 189).toInteger());
	renderFrame(screen, 6, 3, 13, 9);
	screen->render(8 * TILE_SIZE * SCALE, 5 * TILE_SIZE * SCALE, 24 + 4 * 32, 4 * TILE_SIZE, 4 * TILE_SIZE, -1);
	Font::draw("You won !! Perfect !!", screen, 7 * TILE_SIZE * SCALE, 4 * TILE_SIZE * SCALE, Font::m_font, sf::Color(212, 203, 175).toInteger(), 14);
	Font::draw("Back to new horizons.", screen, 6 * TILE_SIZE * SCALE + TILE_SIZE, 11 * TILE_SIZE * SCALE, Font::m_font, sf::Color(11, 0, 4).toInteger(), 14);
}

void WonMenu::renderFrame(Screen* screen, int x0, int y0, int x1, int y1) {
	for (int y = y0; y <= y1; y++) {
		for (int x = x0; x <= x1; x++) {
			if (x == x0 && y == y0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28 + 32, -1);
			}
			else if (x == x1 && y == y0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28 + 32, -1, 1);
			}
			else if (x == x0 && y == y1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28 + 32, -1, 2);
			}
			else if (x == x1 && y == y1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28 + 32, -1, 3);
			}
			else if (y == y0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 29 + 32, -1);
			}
			else if (y == y1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 29 + 32, -1, 2);
			}
			else if (x == x0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 30 + 32, -1);
			}
			else if (x == x1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 30 + 32, -1, 1);
			}
			else {
				screen->renderSquare(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, TILE_SIZE, TILE_SIZE, sf::Color(136, 105, 83).toInteger());
			}
		}
	}
}
