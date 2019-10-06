#include "../entity/Player.h"
#include "../Game.h"
#include "../menu/CraftingMenu.h"
#include "../crafting/Crafting.h"

#include "Workbench.h"

Workbench::Workbench() :
	Furniture("Workbench")
{
	m_sprite = 1;
	m_xr = 3;
	m_yr = 2;
}

Workbench::~Workbench() {
}

bool Workbench::use(Player* player, int attackDir) {
	player->m_game->setMenu(new CraftingMenu(Crafting::m_workbenchRecipes, player));
	return true;
}