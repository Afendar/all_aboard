#pragma once

#include "Mob.h"

class Game;

class Npc : public Mob {
	public:
		Npc(std::string name, Game* game);
		virtual ~Npc();

		Game* m_game;
		std::string m_name;

		void setCurrentDialog(int idDialog);
		void render(Screen* screen);
		bool interact(Player * player, Item * item, int attackDir);
		virtual ClassType classType();

	private:
		void tick();

		bool m_wantTalk;
		int m_currentDialog;
};