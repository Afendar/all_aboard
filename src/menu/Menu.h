#pragma once

#include <deque>

#include "ListItem.h"
#include "../Screen.h"
#include "../item/Item.h"

class Game;
class InputHandler;

class Menu {
	public:
		Menu();

		virtual void init(Game* game, InputHandler* input);
		virtual void tick();
		virtual void render(Screen* screen);

		virtual void renderItemList(Screen* screen, int xo, int yo, int x1, int y1, std::deque<Item*> &listItems, int selected);

		bool isTransparent();

	protected:
		Game* m_game;
		InputHandler* m_input;
		bool m_isTransparent;
};