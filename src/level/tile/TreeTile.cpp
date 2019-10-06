#include "TreeTile.h"

#include "../../Random.h"
#include "../Level.h"
#include "../../entity/ItemEntity.h"
#include "../../item/ResourceItem.h"
#include "../../item/ToolItem.h"

#include "../../particle/TextParticle.h"

TreeTile::TreeTile(int id):
	Tile(id)
{
	m_connectsToGrass = true;
}

TreeTile::~TreeTile()
{
}

void TreeTile::render(Screen * screen, Level * level, int x, int y)
{
	bool u = level->getTile(x, y - 1) == this;
	bool l = level->getTile(x - 1, y) == this;
	bool r = level->getTile(x + 1, y) == this;
	bool d = level->getTile(x, y + 1) == this;
	bool ul = level->getTile(x - 1, y - 1) == this;
	bool ur = level->getTile(x + 1, y - 1) == this;
	bool dl = level->getTile(x - 1, y + 1) == this;
	bool dr = level->getTile(x + 1, y + 1) == this;

	Tile::m_grass->render(screen, level, x, y);

	if (u && ul && l) {
		screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE, 1 + 6 * 32, -1);
	}
	else {
		screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE, 5 * 32, -1);
	}

	if (u && ur && r) {
		screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE, 1 + 7 * 32, -1);
	}
	else {
		screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE, 1 + 5 * 32, -1);
	}

	if (d && dl && l) {
		screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, 1 + 7 * 32, -1);
	}
	else {
		screen->render(x * FINAL_TILESIZE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, 6 * 32, -1);
	}

	if (d && dr && r) {
		screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, 1 + 6 * 32, -1);
	}
	else {
		screen->render(x * FINAL_TILESIZE + TILE_SIZE * SCALE, y * FINAL_TILESIZE + TILE_SIZE * SCALE, 1 + 8 * 32, -1);
	}
}

void TreeTile::renderMinimap(Screen * screen, int x, int y)
{
	screen->renderSquare(x, y, 1, 1, sf::Color(72, 88, 64).toInteger());
}

void TreeTile::tick(Level * level, int xt, int yt)
{
}

bool TreeTile::interact(Level * level, int xt, int yt, Player * player, Item * item, int attackDir)
{
	if (item->instanceOf(TOOL_ITEM)) {
		ToolItem* tool = static_cast<ToolItem*>(item);
		if (tool->m_type == ToolType::m_axe) {
			hurt(level, xt, yt, m_random->nextInt(5) + 1);
			return true;
		}
	}
	return false;
}

void TreeTile::hurt(Level * level, int x, int y, int damages)
{
	int dmg = level->getData(x, y) + damages;

	level->add(new TextParticle(damages, x * FINAL_TILESIZE, y * FINAL_TILESIZE, sf::Color(255, 255, 255).toInteger()));

	if (dmg >= 20) {
		int count = m_random->nextInt(2) + 1;
		for (int i = 0; i < count; i++) {
			level->add(
				new ItemEntity(
					new ResourceItem(Resource::m_wood),
					x * FINAL_TILESIZE + m_random->nextInt(10) + 3,
					y * FINAL_TILESIZE + m_random->nextInt(10) + 3
				));
		}
		level->setTile(x, y, Tile::m_grass, 0);
	}
	else {
		level->setData(x, y, dmg);
	}
}

bool TreeTile::mayPass(Level * level, int x, int y, Entity * e)
{
	return false;
}
