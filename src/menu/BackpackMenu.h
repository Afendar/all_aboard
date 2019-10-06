#pragma once

#include "Menu.h"
#include "../entity/Player.h"
#include "../Screen.h"

class BackpackMenu : public Menu {
	public:
		BackpackMenu(Player* player);
		virtual ~BackpackMenu();

		void tick();
		void render(Screen* screen);

	private:
		Player* m_player;
		int m_selected;
};