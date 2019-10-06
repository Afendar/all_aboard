#pragma once

#include "Tile.h"

class WaterTile : public Tile {
	public:
		WaterTile(int id);
		virtual ~WaterTile();
		virtual void render(Screen * screen, Level * level, int x, int y);
		void renderMinimap(Screen* screen, int x, int y);

		bool mayPass(Level * level, int x, int y, Entity * e);
};