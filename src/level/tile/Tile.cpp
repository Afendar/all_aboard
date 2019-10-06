#include "Tile.h"
#include "../Level.h"
#include "../../Screen.h"

#include "GrassTile.h"
#include "WaterTile.h"
#include "PathTile.h"
#include "TreeTile.h"
#include "BushTile.h"
#include "GravestoneTile.h"
#include "BridgeTile.h"

Tile** Tile::m_tiles;

int Tile::m_tickCount = 0;

Tile* Tile::m_grass;
Tile* Tile::m_water;
Tile* Tile::m_path;
Tile* Tile::m_tree;
Tile* Tile::m_bush;
Tile* Tile::m_gravestone;
Tile* Tile::m_bridge;

Random* Tile::m_random = new Random();

Tile::Tile(int id):
	m_connectsToGrass(false),
	m_connectsToSand(false),
	m_connectsToLava(false),
	m_connectsToWater(false) 
{
	this->m_id = (ushort)id;
	m_tiles[id] = this;
}

Tile::~Tile() {

}

ushort Tile::getId()
{
	return m_id;
}

bool Tile::isConnectsToGrass()
{
	return m_connectsToGrass;
}

bool Tile::isConnectsToSand()
{
	return m_connectsToSand;
}

bool Tile::isConnectsToLava()
{
	return m_connectsToLava;
}

bool Tile::isConnectsToWater()
{
	return m_connectsToWater;
}

void Tile::init() {
	m_tiles = new Tile*[256];

	m_grass = new GrassTile(0);
	m_water = new WaterTile(1);
	m_path = new PathTile(2);
	m_tree = new TreeTile(3);
	m_bush = new BushTile(4);
	m_gravestone = new GravestoneTile(5);
	m_bridge = new BridgeTile(6);
}

void Tile::render(Screen * screen, Level * level, int x, int y) {

}

void Tile::renderMinimap(Screen * screen, int x, int y) {

}

bool Tile::mayPass(Level * level, int x, int y, Entity * e) {
	return true;
}

int Tile::getLightRadius(Level * level, int x, int y) {
	return 0;
}

void Tile::hurt(Level * level, int x, int y, Mob * source, int dmg, int attackDir){

}

void Tile::bumpedInto(Level * level, int xt, int yt, Entity * entity) {
}

void Tile::tick(Level * level, int xt, int yt){
}

void Tile::steppedOn(Level * level, int xt, int yt, Entity * entity) {
}

bool Tile::interact(Level * level, int xt, int yt, Player * player, Item * item, int attackDir){
	return false;
}

bool Tile::use(Level * level, int xt, int yt, Player * player, int attackDir){
	return false;
}

bool Tile::connectsToLiquid() {
	return m_connectsToWater || m_connectsToLava;
}