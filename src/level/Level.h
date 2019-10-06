#pragma once

#include <list>

#include "../entity/Entity.h"
#include "../Screen.h"
#include "../Random.h"

typedef unsigned int byte;

class Player;

class Level {
	public:
		Level();
		virtual ~Level();

		void renderBackground(Screen * screen, int xScroll, int yScroll);
		void renderBackgroundMinimap(Screen* screen, int posX, int posY);
		void renderSprites(Screen * screen, int xScroll, int yScroll);
		Tile* getTile(int x, int y);
		void setTile(int x, int y, Tile* tile, int dataVal);
		int getData(int x, int y);
		void setData(int x, int y, int val);
		void add(Entity * entity);
		void trySpawn(int count);
		void update();
		std::list<Entity*>* getEntities(int x0, int y0, int x1, int y1);
		std::list<Entity*>* getEntities(int x0, int y0);
		std::list<Entity*>* getEntities(int x0, int y0, int x1, int y1, Entity* exclude);

		int getWidth();
		int getHeight();

		Player* m_player;

	private:

		void insertEntity(int x, int y, Entity* e);
		void removeEntity(int x, int y, Entity* e);

		int m_depth;
		int m_w, m_h;
		byte* m_tiles;
		byte* m_data;

		std::list<Entity*> m_rowSprites;
		std::list<Entity*> m_entities;
		std::list<Entity*>* m_entitiesInTiles;

		Random* m_random;
};