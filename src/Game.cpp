#include "Game.h"
#include <iostream>

#include "menu/Menu.h"
#include "menu/LooseMenu.h"
#include "menu/WonMenu.h"
#include "menu/MainMenu.h"
#include "Sound.h"

Game::Game() :
	m_menu(NULL),
	m_player(NULL),
	m_a(NULL)
{
	m_inputHandler = new InputHandler();
	run();
}

Game::~Game()
{
}

void Game::run()
{
	long lastTime = time(0);
	double unprocessed = 0;
	double nsPerTick = 1000000000.0 / 60;
	m_frames = 0;
	m_ticks = 0;

	init();

	while (!m_screen->isClosed()) {

		m_ticks++;
		tick();

		sf::Event evt;
		while (m_screen->getRenderWindow()->pollEvent(evt)) {
			if (evt.type == sf::Event::Closed){
				m_screen->close();
			}

			m_inputHandler->handleKeys(&evt);
		}

		m_screen->clear();
		render();
		m_screen->display();
	}
}

void Game::init()
{
	Tile::init();
	Sound::initSound();
	Font::init();
	Resource::init();

	m_spritesheet = new Spritesheet("gfx/spritesheet.png");
	m_screen = new Screen(m_spritesheet);

	resetGame();

	setMenu(new MainMenu());
}

void Game::render()
{
	if (m_menu == NULL || m_menu->isTransparent()) {
		if (m_player) {
			int xScroll = (m_player->getX() + TILE_SIZE) - ((m_screen->getWidth() * FINAL_TILESIZE) / 2);
			int yScroll = (m_player->getY() + TILE_SIZE) - (((m_screen->getHeight() + 1) * FINAL_TILESIZE) / 2);
			if (xScroll < FINAL_TILESIZE) xScroll = FINAL_TILESIZE;
			if (yScroll < FINAL_TILESIZE) yScroll = FINAL_TILESIZE;
			if (xScroll > m_level->getWidth() * FINAL_TILESIZE - (m_screen->getWidth() * FINAL_TILESIZE) - FINAL_TILESIZE) xScroll = m_level->getWidth() * FINAL_TILESIZE - (m_screen->getWidth() * FINAL_TILESIZE) - FINAL_TILESIZE;
			if (yScroll > m_level->getHeight() * FINAL_TILESIZE - (m_screen->getHeight() * FINAL_TILESIZE) - FINAL_TILESIZE) yScroll = m_level->getHeight() * FINAL_TILESIZE - (m_screen->getHeight() * FINAL_TILESIZE) - FINAL_TILESIZE;
			
			m_level->renderBackground(m_screen, xScroll, yScroll);
			m_level->renderSprites(m_screen, xScroll, yScroll);

			//m_level->renderBackgroundMinimap(m_screen, 10, 10);
		}
	}

	renderGui();
}

void Game::renderGui() {
	if (m_a != NULL) {
		m_a->render(m_screen);
	}

	if (m_menu == NULL || m_menu->isTransparent()) {
		for (int i = 0; i < m_player->m_health; i++) {
			m_screen->render(8 + i * TILE_SIZE * SCALE, 8, 23, -1);
		}
	}

	if (m_menu != NULL) {
		m_menu->render(m_screen);
	}
}

void Game::tick()
{
	if (m_a != NULL) {
		if (m_a->m_alpha > 0) {
			m_a->tick();
		}
		else {
			m_a = NULL;
		}

	}

	if (m_menu != NULL) {
		m_menu->tick();
	}
	else {
		if (m_player->isRemoved()) {
			setMenu(new LooseMenu());
		}
		else if(m_player->m_backpack->hasResources(Resource::m_wood, 30)) {
			setMenu(new WonMenu());
		}

		m_level->update();
	}

	m_inputHandler->tick();
}

void Game::resetGame()
{
	m_level = new Level();

	m_player = new Player(this, m_inputHandler);

	m_level->add(m_player);
	m_level->add(new Npc("Rudolphe", this));
}

Player * Game::getPlayer()
{
	return m_player;
}

void Game::setMenu(Menu* menu)
{
	this->m_menu = menu;
	if (menu != NULL)
	{
		menu->init(this, m_inputHandler);
	}
}

void Game::setAchievement(Achievement * a)
{
	m_a = a;
}
