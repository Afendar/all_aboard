#include "GravestoneTile.h"

#include "../../Random.h"
#include "../Level.h"
#include "../../entity/Skeleton.h"

GravestoneTile::GravestoneTile(int id):
	Tile(id)
{
	m_connectsToGrass = true;
}

GravestoneTile::~GravestoneTile()
{
}

void GravestoneTile::render(Screen * screen, Level * level, int x, int y)
{
	Tile::m_grass->render(screen, level, x, y);

	int data = level->getData(x, y);
	int shape = (data / 16) % 3;

	screen->render(x * FINAL_TILESIZE + (TILE_SIZE * SCALE) / 2, y * FINAL_TILESIZE + (TILE_SIZE * SCALE) / 2, shape + 2 * 32, -1);
}

void GravestoneTile::renderMinimap(Screen * screen, int x, int y)
{
	screen->renderSquare(x, y, 1, 1, sf::Color(0, 0, 0).toInteger());
}

void GravestoneTile::tick(Level * level, int xt, int yt)
{
	if (m_random->nextInt(15) == 0) {
		return;
	}

	if ((m_random->nextInt(3) / 3) % 2 == 0) {
		Mob* mob = new Skeleton();
		mob->setX(xt * FINAL_TILESIZE);
		mob->setY(yt * FINAL_TILESIZE);
		level->add(mob);
	}
}

bool GravestoneTile::mayPass(Level * level, int x, int y, Entity * e)
{
	return false;
}
