#pragma once

#include "Mob.h"

class Skeleton : public Mob {
	public:
		Skeleton();
		virtual ~Skeleton();

		void tick();
		void render(Screen* screen);

	private:
		int m_xa, m_ya;
		int m_randomWalkTime;

	protected:
		void die();
		void touchedBy(Entity* entity);
};