#pragma once

#include "Menu.h"
#include "../Screen.h"

class LooseMenu : public Menu {
	public:
		LooseMenu();
		virtual ~LooseMenu();

		void tick();
		void render(Screen* screen);

	private:
		void renderFrame(Screen* screen, int x0, int y0, int x1, int y1);

		int m_inputDelay;
};