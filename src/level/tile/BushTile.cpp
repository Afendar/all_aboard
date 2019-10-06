#include "BushTile.h"

#include "../../Random.h"
#include "../Level.h"
#include "../../entity/ItemEntity.h"
#include "../../item/ResourceItem.h"

#include <iostream>

BushTile::BushTile(int id):
	Tile(id)
{
	m_connectsToGrass = true;
}

BushTile::~BushTile()
{
}

void BushTile::render(Screen * screen, Level * level, int x, int y)
{
	Tile::m_grass->render(screen, level, x, y);

	int age = level->getData(x, y);
	int xo = 0;
	if (age > 15) {
		xo = 1;
	}

	screen->render(x * FINAL_TILESIZE + (TILE_SIZE * SCALE) / 2, y * FINAL_TILESIZE + (TILE_SIZE * SCALE) / 2, xo + 3 * 32, -1);
}

void BushTile::renderMinimap(Screen * screen, int x, int y) {
	screen->renderSquare(x, y, 1, 1, sf::Color(68, 73, 115).toInteger());
}

void BushTile::tick(Level * level, int xt, int yt)
{
	int age = level->getData(xt, yt);
	if (age > 15) {
		return;
	}

	level->setData(xt, yt, age + 1);
}

void BushTile::hurt(Level * level, int x, int y, Mob * source, int dmg, int attackDir)
{
	int age = level->getData(x, y);
	if (age <= 15) {
		return;
	}
	int count = m_random->nextInt(2) + 1;
	for (int i = 0; i < count; i++) {
		level->add(
			new ItemEntity(
				new ResourceItem(Resource::m_blackberrie),
				x * FINAL_TILESIZE + m_random->nextInt(10) + 3,
				y * FINAL_TILESIZE + m_random->nextInt(10) + 3
			));
	}
	
	level->setData(x, y, 0);
}

bool BushTile::mayPass(Level * level, int x, int y, Entity * e)
{
	return false;
}
