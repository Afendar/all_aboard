#include "DialogueMenu.h"

#include "../Font.h"
#include "../Game.h"
#include "../Sound.h"

#include "../item/ToolItem.h"

DialogueMenu::DialogueMenu(Npc* npc, int id, int idDialogue)
{
	m_isTransparent = true;
	m_id = id;
	m_npc = npc;
	m_idDialogue = idDialogue;

	m_dialogues[0] = "Hi little guy,\n\nWhat a shipwreck ! Happy that you have escaped.\n\nI imagine you want to go back ?";
	m_dialogues[1] = "But first of all, I'm hungry.\n\nCould you bring me 10 blackberries ?\n\nHere is a bag to allow you to recover them.";
	m_dialogues[2] = "Thank you so much !\n\nThese blackberries are really delicious.";
	m_dialogues[3] = "Here in exchange my old axe\n\nthat will allow you to collect 30 piece of wood.";
	m_dialogues[4] = "Good luck my little...";
	m_dialogues[5] = "There are not enougth berries for a man like me\n\nIt's just good to feed the birds.";
	m_dialogues[6] = "I already gave you my axe.\n\nYou can now collect the 30 pieces of wood.";
}

DialogueMenu::~DialogueMenu()
{
}

void DialogueMenu::tick()
{
	if (m_input->exit->clicked) {
		m_game->setMenu(NULL);
	}

	if (m_input->select->clicked) {
		Sound::m_pickup->play();

		if (m_idDialogue < 1) {
			m_idDialogue++;
		}
		else if (m_idDialogue > 1 && m_idDialogue < 4) {
			m_idDialogue++;
		}
		else {
			if (m_idDialogue == 1) {
				m_game->setAchievement(new Achievement("Bagpack !!!", new ResourceItem(Resource::m_backpack)));
				m_game->getPlayer()->m_backpackUnlocked = true;
			}
			if (m_idDialogue == 2) {
				m_game->setAchievement(new Achievement("Collect 10 blackberries", new ResourceItem(Resource::m_blackberrie)));
				m_game->getPlayer()->m_backpack->removeResource(Resource::m_blackberrie, 10);
			}
			if (m_idDialogue == 4) {
				m_game->setAchievement(new Achievement("Old man axe !", new ToolItem(ToolType::m_axe)));
				m_game->getPlayer()->m_backpack->add(new ToolItem(ToolType::m_axe));
				m_game->getPlayer()->m_activeItem = new ToolItem(ToolType::m_axe);
			}

			if (m_idDialogue == 5) m_idDialogue = 2;
			else if (m_idDialogue == 4) m_idDialogue = 6;
			else if (m_idDialogue == 6)m_idDialogue = 6;
			else
				m_idDialogue++;

			m_npc->setCurrentDialog(m_idDialogue);
			m_game->setMenu(NULL);
		}
	}
}

void DialogueMenu::render(Screen* screen)
{
	Font::renderFrame(screen, "", 2, 11, 17, 13);
	Font::draw(m_dialogues[m_idDialogue], screen, 2 * TILE_SIZE * SCALE + 16, 11 * TILE_SIZE * SCALE + 16, Font::m_font, sf::Color(0, 0, 0).toInteger(), 13);
}
