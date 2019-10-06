#pragma once

#include "Tile.h"

class BushTile : public Tile {
	public:
		BushTile(int id);
		virtual ~BushTile();

		virtual void render(Screen * screen, Level * level, int x, int y);
		virtual void renderMinimap(Screen * screen, int x, int y);

		void tick(Level * level, int xt, int yt);
		void hurt(Level * level, int x, int y, Mob * source, int dmg, int attackDir);

		bool mayPass(Level * level, int x, int y, Entity * e);
};