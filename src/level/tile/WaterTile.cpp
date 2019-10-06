#include "WaterTile.h"
#include "../Level.h"

WaterTile::WaterTile(int id) : Tile(id) {
	m_connectsToWater = true;
}

WaterTile::~WaterTile() {

}

void WaterTile::render(Screen * screen, Level * level, int x, int y)
{
	bool u = level->getTile(x, y - 1)->isConnectsToWater();
	bool d = level->getTile(x, y + 1)->isConnectsToWater();
	bool l = level->getTile(x - 1, y)->isConnectsToWater();
	bool r = level->getTile(x + 1, y)->isConnectsToWater();

	bool ul = level->getTile(x - 1, y - 1)->isConnectsToWater();
	bool ur = level->getTile(x + 1, y - 1)->isConnectsToWater();
	bool dl = level->getTile(x - 1, y + 1)->isConnectsToWater();
	bool dr = level->getTile(x + 1, y + 1)->isConnectsToWater();
	
	if (u && l) {
		if (!ul) {
			screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE, 6 + 3 * 32, -1);
		}
		else {
			screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE, 1, -1);
		}
	}
	else {
		screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE, !u && !l ? 6 : (!l ? 6 : 7) + (!u ? 0 : 1) * 32, -1);
	}

	if (u && r) {
		if (!ur) {
			screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE, 7 + 3 * 32, -1);
		}
		else {
			screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE, 1, -1);
		}
	}
	else {
		screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE, !u && !r ? 8 : (!r ? 8 : 7) + (!u ? 0 : 1) * 32, -1);
	}

	if (d && l) {
		if (!dl) {
			screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, 6 + 4 * 32, -1);
		}
		else {
			screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, 1, -1);
		}
	}
	else {
		screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, !d && !l ? 6 + 2 * 32 : (!l ? 6 : 7) + (!d ? 2 : 1) * 32, -1);
	}

	if (d && r) {
		if (!dr) {
			screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, 7 + 4 * 32, -1);
		}
		else {
			screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, 1, -1);
		}
	}
	else {
		screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, !d && !r ? 8 + 2 * 32 : (!r ? 8 : 7) + (!d ? 2 : 1) * 32, -1);
	}
}

void WaterTile::renderMinimap(Screen* screen, int x, int y) {
	screen->renderSquare(x, y, 1, 1, sf::Color(135, 202, 224).toInteger());
}

bool WaterTile::mayPass(Level * level, int x, int y, Entity * e)
{
	return false;
}
