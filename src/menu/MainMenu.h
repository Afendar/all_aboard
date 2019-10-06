#pragma once

#include "Menu.h"
#include "../entity/Player.h"
#include "../Screen.h"

class MainMenu : public Menu {
	public:
		MainMenu();
		virtual ~MainMenu();

		void tick();
		void render(Screen* screen);

	private:
		bool m_flashUp;
		int m_alpha;
};