#pragma once

#include "Screen.h"
#include "InputHandler.h"
#include "entity/Player.h"
#include "entity/Npc.h"
#include "level/Level.h"
#include "Font.h"
#include "item/resource/Resource.h"
#include "achievement/Achievement.h"

typedef unsigned short ushort;

class Menu;

class Game {
	public:
		Game();
		virtual ~Game();

		void run();
		void init();
		void render();
		void renderGui();
		void tick();
		void setMenu(Menu* m);
		void setAchievement(Achievement* a);

		void resetGame();

		Player* getPlayer();

	private:

		Level* m_level;
		Player* m_player;
		Screen* m_screen;
		Spritesheet* m_spritesheet;
		InputHandler* m_inputHandler;
		Menu* m_menu;
		Menu* m_previousMenu;

		Achievement* m_a;

		bool m_running;
		int m_gameTime;
		int m_frames;
		int m_ticks;
};