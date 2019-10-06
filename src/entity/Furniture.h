#pragma once

#include <string>

#include "Entity.h"

class Screen;
class Player;

class Furniture : public Entity {
	public:
		Furniture(std::string name);
		virtual ~Furniture();

		int m_col, m_sprite;
		std::string m_name;

		virtual void tick();
		void renderCarry(Screen* screen);
		virtual void render(Screen* screen);
		virtual bool blocks(Entity* e);
		virtual void take(Player* player);

		ClassType classType();

	private:
		int m_pushTime;
		int m_pushDir;
		Player* m_shouldTake;

	protected:
		virtual void touchedBy(Entity* entity);

};