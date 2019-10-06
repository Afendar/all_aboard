#include "GrassTile.h"

#include <iostream>

#include "../../Random.h"
#include "../Level.h"

GrassTile::GrassTile(int id) :Tile(id) {
	m_connectsToGrass = true;
}

GrassTile::~GrassTile() {

}

void GrassTile::render(Screen* screen, Level * level, int x, int y) {
	screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE, 0, -1);
	screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE, 0, -1);
	screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, 0, -1);
	screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, 0, -1);
}

void GrassTile::renderMinimap(Screen* screen, int x, int y) {
	screen->renderSquare(x, y, 1, 1, sf::Color(16, 150, 49).toInteger());
}

void GrassTile::tick(Level * level, int xt, int yt)
{
	
}

bool GrassTile::interact(Level * level, int xt, int yt, Player * player, Item * item, int attackDir) {
	return false;
}