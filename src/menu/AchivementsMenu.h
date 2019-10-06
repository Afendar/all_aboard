#pragma once

#include "Menu.h"
#include "../Screen.h"

class AchivementsMenu : public Menu {
	public:
		AchivementsMenu();
		virtual ~AchivementsMenu();

		void tick();
		void render(Screen* screen);

	private:

};