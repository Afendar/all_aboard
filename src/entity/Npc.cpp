#include "Npc.h"
#include "../Game.h"

#include "../menu/DialogueMenu.h"

#include <iostream>

Npc::Npc(std::string name, Game* game) :
	m_name(name),
	m_game(game),
	m_currentDialog(0)
{
	m_x = 21 * FINAL_TILESIZE;
	m_y = 30 * FINAL_TILESIZE;

	m_wantTalk = true;
}

Npc::~Npc()
{
}

void Npc::setCurrentDialog(int idDialog)
{
	m_currentDialog = idDialog;
}

void Npc::render(Screen * screen)
{
	int xt = 22;
	int yt = 30;
	int flip = 0;
	int flip2 = 0;

	if (m_wantTalk) {
		int yy = m_y - (TILE_SIZE * SCALE / 2) - 4;
		if (m_tickTime / 8 % 2 == 0)
			yy -= 2;
		screen->render(m_x + (TILE_SIZE * SCALE) / 2, yy, 31, -1);
	}

	screen->render(m_x, m_y, xt + yt * 32, 32, 16, -1, flip);
	screen->render(flip2 ? m_x + 1 : m_x, m_y + 32, xt + (yt + 1) * 32, 32, 16, -1, flip2);
}

bool Npc::interact(Player * player, Item * item, int attackDir)
{
	if (m_currentDialog == 2 && !player->m_backpack->hasResources(Resource::m_blackberrie, 10)) {
		m_currentDialog = 5;
	}

	m_game->setMenu(new DialogueMenu(this, 0, m_currentDialog));
	return true;
}

ClassType Npc::classType()
{
	return ClassType::NPC;
}

void Npc::tick()
{
	Mob::tick();
}
