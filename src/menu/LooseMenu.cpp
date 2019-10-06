#include "LooseMenu.h"

#include "../Game.h"

LooseMenu::LooseMenu() :
	m_inputDelay(60)
{
}

LooseMenu::~LooseMenu()
{
}

void LooseMenu::tick()
{
	if (m_inputDelay > 0)
		m_inputDelay--;

	/*if (m_input->exit->clicked) {
		m_game->setMenu(NULL);
	}*/
}

void LooseMenu::render(Screen * screen)
{
	screen->renderSquare(0, 0, screen->getWidth() * TILE_SIZE * SCALE, (screen->getHeight() + 1) * TILE_SIZE * SCALE, sf::Color(210, 198, 189).toInteger());
	renderFrame(screen, 6, 3, 13, 9);
	screen->render(8 * TILE_SIZE * SCALE + TILE_SIZE, 6 * TILE_SIZE * SCALE, 28 + 4 * 32, 3 * TILE_SIZE, 3 * TILE_SIZE, -1);
	Font::draw("You loose !", screen, 8 * TILE_SIZE * SCALE + TILE_SIZE, 4 * TILE_SIZE * SCALE, Font::m_font, sf::Color(255, 255, 255).toInteger(), 14);
	Font::draw("Shame, you may be lucky next time.", screen, 4 * TILE_SIZE * SCALE + TILE_SIZE, 12 * TILE_SIZE * SCALE, Font::m_font, sf::Color(11, 0, 4).toInteger(), 14);

}

void LooseMenu::renderFrame(Screen* screen, int x0, int y0, int x1, int y1) {
	for (int y = y0; y <= y1; y++) {
		for (int x = x0; x <= x1; x++) {
			if (x == x0 && y == y0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28 + 3 * 32, -1);
			}
			else if (x == x1 && y == y0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28 + 3 * 32, -1, 1);
			}
			else if (x == x0 && y == y1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28 + 3 * 32, -1, 2);
			}
			else if (x == x1 && y == y1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 28 + 3 * 32, -1, 3);
			}
			else if (y == y0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 29 + 3 * 32, -1);
			}
			else if (y == y1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 29 + 3 * 32, -1, 2);
			}
			else if (x == x0) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 30 + 3 * 32, -1);
			}
			else if (x == x1) {
				screen->render(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, 30 + 3 * 32, -1, 1);
			}
			else {
				screen->renderSquare(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, TILE_SIZE, TILE_SIZE, sf::Color(11, 0, 4).toInteger());
			}
		}
	}
}
