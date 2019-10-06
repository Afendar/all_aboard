#pragma once

#include <deque>
#include "../menu/ListItem.h"
#include "../Screen.h"

class Resource;
class Player;
class Item;

class Recipe : public ListItem {
	public:
		Recipe(Item * resultTemplate);
		virtual ~Recipe();

		Recipe * addCost(Resource * resource, int count);
		void checkCanCraft(Player * player);
		virtual void renderInventory(Screen * screen, int x, int y);
		virtual void craft(Player * player) = 0;
		void deductCost(Player * player);

		std::deque<Item*> m_costs;
		bool m_canCraft;
		Item* m_resultTemplate;
};