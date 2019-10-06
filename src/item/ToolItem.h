#pragma once

#include <string>
#include "ToolType.h"
#include "Item.h"
#include "../Random.h"

class Screen;
class ItemEntity;
class Entity;

class ToolItem : public Item {
	public:
		ToolItem(ToolType* type);
		virtual ~ToolItem();
		ToolType* m_type;

		int getSprite();
		void renderIcon(Screen * screen, int x, int y, int alpha);
		void renderInventory(Screen * screen, int x, int y);
		std::string getName();
		void onTake(ItemEntity * itemEntity);
		bool canAttack();
		int getAttackDamageBonus(Entity * e);
		bool matches(Item * item);
		ClassType classType();

	private:
		Random* m_random;
};