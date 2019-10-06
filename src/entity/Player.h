#pragma once

class Game;
class Item;

#include "Mob.h"
#include "../InputHandler.h"
#include "Backpack.h"

class Player : public Mob {
	public:
		Player(Game * game, InputHandler* input);
		virtual ~Player();

		Game* m_game;
		Item* m_attackItem;
		Item* m_activeItem;
		Backpack* m_backpack;
		int m_stamina;
		int m_staminaRecharge;
		int m_staminaRechargeDelay;
		int m_score;
		int m_maxStamina;
		int m_invulnerableTime;

		void render(Screen * screen);
		void renderPortrait(Screen* screen, int x, int y);
		void touchItem(ItemEntity * itemEntity);
		bool canSwim();
		virtual ClassType classType();

		bool m_backpackUnlocked;

	private:
		int m_attackTime, m_attackDir;
		int m_onStairDelay;

		InputHandler* m_input;

		void tick();
		bool use();
		bool interact();
		void attack();
		bool use(int x0, int y0, int x1, int y1);
		bool interact(int x0, int y0, int x1, int y1);

	protected:

		void die();
		void doHurt(int damage, int attackDir);
};