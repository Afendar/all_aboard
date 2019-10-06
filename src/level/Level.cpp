#include "Level.h"
#include "LevelGen.h"

Level::Level():
	m_random(new Random())
{
	byte** maps;

	maps = LevelGen::createMap();

	m_w = 128;
	m_h = 128;

	m_tiles = maps[0];
	m_data = maps[1];

	m_entitiesInTiles = new std::list<Entity*>[m_w * m_h];
}

Level::~Level()
{
	for (std::list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
	{
		delete *it;
	}

	delete[] m_entitiesInTiles;
	delete[] m_tiles;
	delete[] m_data;
	delete m_random;
}

void Level::renderBackground(Screen* screen, int xScroll, int yScroll)
{
	int xo = xScroll / (FINAL_TILESIZE);
	int yo = yScroll / (FINAL_TILESIZE);
	int w = screen->getWidth();
	int h = screen->getHeight();
	screen->setOffset(xScroll, yScroll);
	for (int y = yo; y <= h + yo; ++y)
	{
		for (int x = xo; x <= w + xo; ++x)
		{
			getTile(x, y)->render(screen, this, x, y);
		}
	}
	screen->setOffset(0, 0);
}

void Level::renderBackgroundMinimap(Screen* screen, int posX, int posY) {
	for (int x = 0; x <= m_w; x++)
	{
		for (int y = 0; y <= m_h; y++)
		{
			getTile(x, y)->renderMinimap(screen, posX + (x * SCALE), posY + (y * SCALE));
		}
	}

	screen->renderSquare(posX + (18 * SCALE), posY + (30 * SCALE), 1, 1, sf::Color(190, 57, 57).toInteger());
}

void Level::renderSprites(Screen* screen, int xScroll, int yScroll)
{
	int xo = xScroll / (FINAL_TILESIZE);
	int yo = yScroll / (FINAL_TILESIZE);
	int w = screen->getWidth();
	int h = screen->getHeight();

	screen->setOffset(xScroll, yScroll);
	for (int y = yo; y <= h + yo; ++y)
	{
		if (y < 0 || y >= m_h) continue;
		for (int x = xo; x <= w + xo; ++x)
		{
			if (x < 0 || x >= m_w) continue;
			std::list<Entity*> &ent = m_entitiesInTiles[x + y * m_w];
			if (!ent.empty())
			{
				for (std::list<Entity*>::iterator it = ent.begin(); it != ent.end(); it++)
				{
					Entity * e = *it;
					e->render(screen);
				}
			}
		}

		m_rowSprites.clear();
	}
	screen->setOffset(0, 0);
}

Tile* Level::getTile(int x, int y)
{
	if (x < 0 || y < 0 || x >= m_w || y >= m_h) return Tile::m_grass;
	return Tile::m_tiles[m_tiles[x + y * m_w]];
}

void Level::setTile(int x, int y, Tile* tile, int dataVal) {
	if (x < 0 || y < 0 || x >= m_w || y >= m_h) return;
	m_tiles[x + y * m_w] = tile->getId();
	m_data[x + y * m_w] = (byte) dataVal;
}

int Level::getData(int x, int y) {
	if (x < 0 || y < 0 || x >= m_w || y >= m_h) return 0;
	return m_data[x + y * m_w] & 0xff;
}

void Level::setData(int x, int y, int val) {
	if (x < 0 || y < 0 || x >= m_w || y >= m_h) return;
	m_data[x + y * m_w] = (byte)val;
}

void Level::add(Entity * entity)
{
	if (entity->instanceOf(PLAYER))
	{
		m_player = (Player*)entity;
	}
	entity->setRemoved(false);
	m_entities.push_back(entity);
	entity->init(this);

	insertEntity(entity->getX() / (FINAL_TILESIZE), entity->getY() / (FINAL_TILESIZE), entity);
}

void Level::trySpawn(int count)
{

}

void Level::update() {

	int tilesTickAttempt = m_w * m_h / 800;

	for (int i = 0; i < tilesTickAttempt; ++i) {
		int xt = m_random->nextInt(m_w);
		int yt = m_random->nextInt(m_h);
		getTile(xt, yt)->tick(this, xt, yt);
	}

	for (std::list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end();) {
		Entity* e = *it;
		int xto = e->getX() / (FINAL_TILESIZE);
		int yto = e->getY() / (FINAL_TILESIZE);

		e->tick();

		if (e->isRemoved()) {
			removeEntity(xto, yto, e);
			if (!e->instanceOf(PLAYER) && !e->instanceOf(FURNITURE)) {
				delete e;
			}
			it = m_entities.erase(it);
		}
		else {
			int xt = e->getX() / (FINAL_TILESIZE);
			int yt = e->getY() / (FINAL_TILESIZE);

			if (xto != xt || yto != yt) {
				removeEntity(xto, yto, e);
				insertEntity(xt, yt, e);
			}
			it++;
		}
	}
}

std::list<Entity*> * Level::getEntities(int x0, int y0, int x1, int y1)
{
	std::list<Entity*> * result = new std::list<Entity*>;
	int xt0 = (x0 / (FINAL_TILESIZE)) - 1;
	int yt0 = (y0 / (FINAL_TILESIZE)) - 1;
	int xt1 = (x1 / (FINAL_TILESIZE)) + 1;
	int yt1 = (y1 / (FINAL_TILESIZE)) + 1;
	for (int y = yt0; y <= yt1; ++y)
	{
		if (y < 0 || y >= m_h) continue;
		int yByWidth = y * m_w;
		for (int x = xt0; x <= xt1; ++x)
		{
			if (x < 0 || x >= m_w) continue;
			std::list<Entity*> &ent = m_entitiesInTiles[x + yByWidth];
			if (ent.empty()) continue;
			for (std::list<Entity*>::iterator it = ent.begin(); it != ent.end(); it++)
			{
				Entity * e = *it;
				if (e->intersects(x0, y0, x1, y1)) result->push_back(e);
			}
		}
	}
	return result;
}

std::list<Entity*> * Level::getEntities(int x0, int y0, int x1, int y1, Entity* excluded)
{
	std::list<Entity*>* result = new std::list<Entity*>;
	int xt0 = (x0 / (FINAL_TILESIZE)) - 1;
	int yt0 = (y0 / (FINAL_TILESIZE)) - 1;
	int xt1 = (x1 / (FINAL_TILESIZE)) + 1;
	int yt1 = (y1 / (FINAL_TILESIZE)) + 1;
	for (int y = yt0; y <= yt1; ++y)
	{
		if (y < 0 || y >= m_h) continue;
		int yByWidth = y * m_w;
		for (int x = xt0; x <= xt1; ++x)
		{
			if (x < 0 || x >= m_w) continue;

			std::list<Entity*> &ent = m_entitiesInTiles[x + yByWidth];

			if (ent.empty()) continue;

			for (std::list<Entity*>::iterator it = ent.begin(); it != ent.end(); it++)
			{
				Entity* e = *it;
				if (e != excluded)
				{
					if (e->intersects(x0, y0, x1, y1))
					{
						result->push_back(e);
					}
				}
			}
		}
	}
	return result;
}

int Level::getWidth()
{
	return m_w;
}

int Level::getHeight()
{
	return m_h;
}

std::list<Entity*>* Level::getEntities(int x0, int y0)
{
	int x = (x0 / (FINAL_TILESIZE));
	int y = (y0 / (FINAL_TILESIZE));
	return new std::list<Entity*>(m_entitiesInTiles[x + y * m_w]);
}

void Level::insertEntity(int x, int y, Entity* e) {
  	if (x < 0 || y < 0 || x >= m_w || y >= m_h) return;
	m_entitiesInTiles[x + y * m_w].push_back(e);
}

void Level::removeEntity(int x, int y, Entity * e)
{
	if (x < 0 || y < 0 || x >= m_w || y >= m_h) return;
	m_entitiesInTiles[x + y * m_w].remove(e);
}
