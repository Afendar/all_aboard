#pragma once

#include "Menu.h"
#include "../Screen.h"
#include "../entity/Npc.h"

#include <string>

class DialogueMenu : public Menu {
	public:
		DialogueMenu(Npc* npc, int id, int idDialogue);
		virtual ~DialogueMenu();

		void tick();
		void render(Screen* screen);

	private:

		std::string m_dialogues[9];
		int m_id;
		int m_idDialogue;
		Npc* m_npc;
};