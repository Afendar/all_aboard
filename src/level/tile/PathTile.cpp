#include "PathTile.h"

#include "../Level.h"

PathTile::PathTile(int id) :
	Tile(id)
{
}

PathTile::~PathTile()
{
}

void PathTile::render(Screen * screen, Level * level, int x, int y)
{
	bool u = level->getTile(x, y - 1)->isConnectsToGrass();
	bool d = level->getTile(x, y + 1)->isConnectsToGrass();
	bool l = level->getTile(x - 1, y)->isConnectsToGrass();
	bool r = level->getTile(x + 1, y)->isConnectsToGrass();

	screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE, 2, -1);
	screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE, 2, -1);
	screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, 2, -1);
	screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, 2, -1);

	if (u || l) {
		screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE, l && u ? 3 : (l ? 3 : 4) + (u ? 0 : 1) * 32, -1);
	}
	if (u || r) {
		screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE, r && u ? 5 : (r ? 5 : 4) + (u ? 0 : 1) * 32, -1);
	}
	if (d || l) {
		screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, l && d ? 3 + 2 * 32 : (l ? 3 : 4) + (d ? 2 : 1) * 32, -1);
	}
	if (d || r) {
		screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, r && d ? 5 + 2 * 32 : (r ? 5 : 4) + (d ? 2 : 1) * 32, -1);
	}
}

void PathTile::renderMinimap(Screen * screen, int x, int y)
{
	screen->renderSquare(x, y, 1, 1, sf::Color(177, 131, 78).toInteger());
}

void PathTile::tick(Level * level, int xt, int yt)
{
}
