#pragma once

#include <deque>

#include "Recipe.h"

class Crafting {
	public:
		Crafting();
		virtual ~Crafting();

		static void init();

		static std::deque<Recipe*> m_workbenchRecipes;
};