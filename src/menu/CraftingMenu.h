#pragma once

#include "Menu.h"
#include "../Screen.h"
#include "../crafting/Recipe.h"

class CraftingMenu : public Menu {
	public:
		CraftingMenu(std::deque<Recipe*> recipes, Player* player);
		virtual ~CraftingMenu();

		void tick();
		void render(Screen* screen);

	private:
};