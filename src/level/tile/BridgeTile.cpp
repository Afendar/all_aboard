#include "BridgeTile.h"

#include <iostream>

#include "../../Random.h"
#include "../Level.h"

BridgeTile::BridgeTile(int id) :
	Tile(id)
{
	m_connectsToWater = true;
}

BridgeTile::~BridgeTile()
{
}

void BridgeTile::render(Screen * screen, Level * level, int x, int y)
{
	bool u = level->getTile(x, y - 1) == this;
	bool d = level->getTile(x, y + 1) == this;
	bool l = level->getTile(x - 1, y) == this;
	bool r = level->getTile(x + 1, y) == this;

	bool ul = level->getTile(x - 1, y - 1) == this;
	bool ur = level->getTile(x + 1, y - 1) == this;
	bool dl = level->getTile(x - 1, y + 1) == this;
	bool dr = level->getTile(x + 1, y + 1) == this;

	int dir = level->getData(x, y) == 0 ? 0 : 3;

	if (u && l) {
		if (!ul) {
			screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE, (9 + dir) + 3 * 32, -1);
		}
		else {
			screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE, (10 + dir) + 32, -1);
		}
	}
	else {
		screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE, !u && !l ? (9 + dir) : (!l ? (9 + dir) : (10 + dir)) + (!u ? 0 : 1) * 32, -1);
	}

	if (u && r) {
		if (!ur) {
			screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE, (10 + dir) + 3 * 32, -1);
		}
		else {
			screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE, (10 + dir) + 32, -1);
		}
	}
	else {
		screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE, !u && !r ? (11 + dir) : (!r ? (11 + dir) : (10 + dir)) + (!u ? 0 : 1) * 32, -1);
	}

	if (d && l) {
		if (!dl) {
			screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, (9 + dir) + 4 * 32, -1);
		}
		else {
			screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, (10 + dir) + 32, -1);
		}
	}
	else {
		screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, !d && !l ? (9 + dir) + 2 * 32 : (!l ? (9 + dir) : (10 + dir)) + (!d ? 2 : 1) * 32, -1);
	}

	if (d && r) {
		if (!dr) {
			screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, (10 + dir) + 4 * 32, -1);
		}
		else {
			screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, (10 + dir) + 32, -1);
		}
	}
	else {
		screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, !d && !r ? (11 + dir) + 2 * 32 : (!r ? (11 + dir) : (10 + dir)) + (!d ? 2 : 1) * 32, -1);
	}
}

void BridgeTile::renderMinimap(Screen * screen, int x, int y)
{
	screen->renderSquare(x, y, 1, 1, sf::Color(255, 0, 0).toInteger());
}

void BridgeTile::tick(Level * level, int xt, int yt)
{
}

bool BridgeTile::interact(Level * level, int xt, int yt, Player * player, Item * item, int attackDir)
{
	return false;
}
