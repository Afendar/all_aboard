#pragma once

#include "Entity.h"

class Mob : public Entity {
	public:
		Mob();
		virtual ~Mob();

		int m_hurtTime;
		int m_maxHealth;
		int m_health;
		int m_swimTimer;
		int m_tickTime;
		int m_dir;

		virtual void tick();
		virtual bool move(int xa, int ya);
		virtual bool blocks(Entity * e);
		virtual void hurt(Mob * mob, int damage, int attackDir);
		virtual void hurt(Tile * tile, int x, int y, int damage);
		virtual void heal(int heal);
		virtual bool findStartPos(Level* level);
		virtual ClassType classType();

	protected:
		int m_walkDist;
		int m_xKnockback, m_yKnockback;

		virtual void die();
		virtual bool isSwimming();
		virtual void doHurt(int damage, int attackDir);
};