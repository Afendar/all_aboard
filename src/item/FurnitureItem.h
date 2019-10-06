#pragma once

#include <string>
#include "Item.h"
#include "../entity/Furniture.h"

class FurnitureItem : public Item {
	public:
		FurnitureItem(Furniture* furniture);
		virtual ~FurnitureItem();

		Furniture* m_furniture;
		bool m_placed;

		int getSprite();
		void renderIcon(Screen* screen, int x, int y);
		void renderInventory(Screen* screen, int x, int y);
		void onTake(ItemEntity* itemEntity);
		bool canAttack();
		bool interactOn(Tile* tile, Level* level, int xt, int yt, Player * player, int attackDir);
		bool isDepleted();
		string getName();
		ClassType classType();
};