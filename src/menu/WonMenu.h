#pragma once

#include "Menu.h"
#include "../Screen.h"

class WonMenu : public Menu {
	public:
		WonMenu();
		virtual ~WonMenu();

		void tick();
		void render(Screen* screen);

		void renderFrame(Screen* screen, int x0, int y0, int x1, int y1);

	private:
		int m_inputDelay;
};