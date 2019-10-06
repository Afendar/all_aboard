#pragma once

#include "../../Random.h"

typedef unsigned short ushort;

class Level;
class Entity;
class Screen;
class Mob;
class Player;
class Item;

class Tile {
	public:
		Tile(int id);
		virtual ~Tile();

		static Tile** m_tiles;
		static int m_tickCount;

		static Tile* m_grass;
		static Tile* m_water;
		static Tile* m_path;
		static Tile* m_tree;
		static Tile* m_bush;
		static Tile* m_gravestone;
		static Tile* m_bridge;

		ushort getId();

		bool isConnectsToGrass();
		bool isConnectsToSand();
		bool isConnectsToLava();
		bool isConnectsToWater();

		static void init();
		virtual void render(Screen * screen, Level * level, int x, int y);
		virtual void renderMinimap(Screen * screen, int x, int y);
		virtual bool mayPass(Level * level, int x, int y, Entity * e);
		virtual int getLightRadius(Level * level, int x, int y);
		virtual void hurt(Level * level, int x, int y, Mob * source, int dmg, int attackDir);
		virtual void bumpedInto(Level * level, int xt, int yt, Entity * entity);
		virtual void tick(Level * level, int xt, int yt);
		virtual void steppedOn(Level * level, int xt, int yt, Entity * entity);
		virtual bool interact(Level * level, int xt, int yt, Player * player, Item * item, int attackDir);
		virtual bool use(Level * level, int xt, int yt, Player * player, int attackDir);
		virtual bool connectsToLiquid();

	protected:
		static Random* m_random;

		bool m_connectsToGrass;
		bool m_connectsToSand;
		bool m_connectsToLava;
		bool m_connectsToWater;

		ushort m_id;
};