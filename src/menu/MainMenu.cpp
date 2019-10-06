#include "MainMenu.h"

#include "../Game.h"
#include "../Font.h"

#include "../Sound.h"

MainMenu::MainMenu()
{
	m_flashUp = true;
	m_alpha = 0;
}

MainMenu::~MainMenu()
{
}

void MainMenu::tick()
{
	if (m_flashUp) {
		m_alpha+=4;
	}
	else {
		m_alpha-=4;
	}

	if (m_alpha <= 0) {
		m_flashUp = !m_flashUp;
		m_alpha = 0;
	}
	else if (m_alpha >= 255) {
		m_flashUp = !m_flashUp;
		m_alpha = 255;
	}

	if (m_input->attack->clicked) {
		Sound::m_pickup->play();
		m_game->setMenu(NULL);
	}
}

void MainMenu::render(Screen * screen)
{
	screen->renderSquare(0, 0, screen->getWidth() * TILE_SIZE * SCALE, (screen->getHeight() + 1) * TILE_SIZE * SCALE, sf::Color(210, 198, 189).toInteger());
	Font::draw("All Aboard", screen, 6 * TILE_SIZE * SCALE - 8, 2 * TILE_SIZE * SCALE, Font::m_fontPirate, sf::Color(11, 0, 4).toInteger(), 38);
	Font::draw("Thousand portholes", screen, 10 * TILE_SIZE * SCALE - 8, 3 * TILE_SIZE * SCALE + TILE_SIZE, Font::m_fontPirate, sf::Color(11, 0, 4).toInteger(), 20);
	
	screen->render(8 * TILE_SIZE * SCALE, 5 * TILE_SIZE * SCALE, 20 + 4 * 32, 4 * TILE_SIZE, 4 * TILE_SIZE, -1);
	Font::draw("Press SPACE to start", screen, 7 * TILE_SIZE * SCALE - 8, 11 * TILE_SIZE * SCALE, Font::m_font, sf::Color(11, 0, 4, m_alpha).toInteger(), 14);
	Font::draw("48h Game by Afendar", screen, 7 * TILE_SIZE * SCALE + 8, 13 * TILE_SIZE * SCALE, Font::m_font, sf::Color(240, 255, 255).toInteger(), 13);
	Font::draw("www.afendar.com", screen, 8 * TILE_SIZE * SCALE, 14 * TILE_SIZE * SCALE, Font::m_font, sf::Color(240, 255, 255).toInteger(), 13);
}
