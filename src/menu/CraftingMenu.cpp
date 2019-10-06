#include "CraftingMenu.h"

#include "../Game.h"

CraftingMenu::CraftingMenu(std::deque<Recipe*> recipes, Player* player)
{
}

CraftingMenu::~CraftingMenu()
{
}

void CraftingMenu::tick()
{
	if (m_input->exit->clicked) {
		m_game->setMenu(NULL);
	}
}

void CraftingMenu::render(Screen * screen)
{
}
