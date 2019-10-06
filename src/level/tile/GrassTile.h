#pragma once

#include "Tile.h"

class GrassTile : public Tile {
	public:
		GrassTile(int id);
		virtual ~GrassTile();
		virtual void render(Screen * screen, Level * level, int x, int y);
		virtual void renderMinimap(Screen * screen, int x, int y);
		void tick(Level * level, int xt, int yt);
		bool interact(Level * level, int xt, int yt, Player * player, Item * item, int attackDir);
};