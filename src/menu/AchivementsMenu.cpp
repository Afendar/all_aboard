#include "AchivementsMenu.h"

#include "../Game.h"

AchivementsMenu::AchivementsMenu()
{
}

AchivementsMenu::~AchivementsMenu()
{
}

void AchivementsMenu::tick()
{
	if (m_input->exit->clicked) {
		m_game->setMenu(NULL);
	}
}

void AchivementsMenu::render(Screen * screen)
{
}
