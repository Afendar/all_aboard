#pragma once

#include "Tile.h"

class PathTile : public Tile {
	public:
		PathTile(int id);
		virtual ~PathTile();
		virtual void render(Screen * screen, Level * level, int x, int y);
		virtual void renderMinimap(Screen * screen, int x, int y);
		void tick(Level * level, int xt, int yt);
};