#pragma once

#include <vector>
#include <SFML/Window/Event.hpp>

#include "Action.h"

class InputHandler
{
	public:
		InputHandler();
		~InputHandler();
		std::vector<Action*> keys;
		Action* up;
		Action* down;
		Action* left;
		Action* right;
		Action* attack;
		Action* backpack;
		Action* achievements;
		Action* crafting;
		Action* select;
		Action* exit;
		Action* pause;
		void releaseAll();
		void tick();
		void add(Action* key);
		void handleKeys(sf::Event* evt);

	private:
		void init();

	public:
		friend class Action;
};