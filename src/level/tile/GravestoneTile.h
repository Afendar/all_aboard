#pragma once

#include "Tile.h"

class GravestoneTile : public Tile {
	public:
		GravestoneTile(int id);
		virtual ~GravestoneTile();

		virtual void render(Screen * screen, Level * level, int x, int y);
		virtual void renderMinimap(Screen * screen, int x, int y);
		void tick(Level * level, int xt, int yt);

		bool mayPass(Level * level, int x, int y, Entity * e);
};