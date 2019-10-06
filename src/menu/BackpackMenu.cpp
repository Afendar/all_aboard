#include "BackpackMenu.h"

#include "../Game.h"

BackpackMenu::BackpackMenu(Player* player)
{
	m_player = player;
	m_isTransparent = true;
}

BackpackMenu::~BackpackMenu()
{
}

void BackpackMenu::tick()
{
	if (m_input->exit->clicked) {
		m_game->setMenu(NULL);
	}

	if (m_input->up->clicked) m_selected -= 5;
	if (m_input->down->clicked) m_selected += 5;
	if (m_input->left->clicked) m_selected--;
	if (m_input->right->clicked) m_selected++;

	if (m_selected < 0) m_selected = 9;
	if (m_selected > 9) m_selected = 0;
}

void BackpackMenu::render(Screen * screen)
{
	Font::renderFrame(screen, "Backpack", 6, 5, 14, 10);
	renderItemList(screen, 7, 6, 13, 9, m_player->m_backpack->m_items, m_selected);
}
