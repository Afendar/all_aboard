#pragma once

#include <SFML/Graphics.hpp>

#include "defines.h"
#include "Spritesheet.h"

class Screen {

	public:

		Screen(Spritesheet* sheet);
		virtual ~Screen();
		sf::RenderWindow* getRenderWindow();

		void clear();
		void close();
		void display();
		void setOffset(int xOffset, int yOffset);
		void render(int xp, int yp, int tile, int color, int flip = 0);
		void render(int xp, int yp, int tile, int w, int h, int color, int flip = 0);
		void renderFont(int xp, int yp, int tile, int color);
		void renderSquare(int xp, int yp, int w, int h, int color);

		int getWidth();
		int getHeight();

		bool isClosed();

	private:

		bool m_isClosed;
		bool m_isFullscreen;
		bool m_isFocused;
		bool m_mouseMoved;
		bool m_captureMouse;
		bool m_isInitialized;

		int m_xOffset;
		int m_yOffset;
		int m_w, m_h;

		Spritesheet* m_sheet;
		sf::RenderWindow m_window;
};