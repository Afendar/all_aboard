#pragma once

class Item;
class Mob;
class Player;
class Screen;

#include "Entity.h"

class ItemEntity : public Entity {
	public:
		ItemEntity(Item* item, int x, int y);
		virtual ~ItemEntity();

		int m_hurtTime;
		double m_xa, m_ya, m_za;
		double m_xx, m_yy, m_zz;
		Item* m_item;

		void tick();
		bool isBlockableBy(Mob* mob);
		void render(Screen* screen);
		void touchedBy(Entity* entity);
		void take(Player* player);

	private:

		int m_time;
		int m_lifeTime;

	protected:

		int m_walkDist;
		int m_dir;
		int m_xKnockback, m_yKnockback;
};