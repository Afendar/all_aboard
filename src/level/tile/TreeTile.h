#pragma once

#include "Tile.h"

class TreeTile : public Tile {
	public:
		TreeTile(int id);
		virtual ~TreeTile();

		virtual void render(Screen * screen, Level * level, int x, int y);
		virtual void renderMinimap(Screen * screen, int x, int y);
		void tick(Level * level, int xt, int yt);
		bool interact(Level * level, int xt, int yt, Player * player, Item * item, int attackDir);
		void hurt(Level* level, int x, int y, int damages);
		bool mayPass(Level * level, int x, int y, Entity * e);
};