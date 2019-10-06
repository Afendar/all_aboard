#include "Mob.h"

#include "../level/Level.h"
#include "Player.h"

Mob::~Mob() {

}

Mob::Mob() :
	m_xKnockback(0),
	m_yKnockback(0)
{
	m_x = m_y = 8;
	m_xr = 4;
	m_yr = 3;
	m_hurtTime = 0;
	m_maxHealth = 5;
	m_health = m_maxHealth;
	m_swimTimer = 0;
	m_tickTime = 0;
	m_walkDist = 0;
	m_dir = 0;
}

void Mob::tick()
{
	m_tickTime++;

	if (m_health <= 0) {
		die();
	}
	if (m_hurtTime > 0) m_hurtTime--;
}

void Mob::die()
{
	remove();
}

bool Mob::move(int xa, int ya)
{
	if (xa != 0 || ya != 0) {
		m_walkDist++;
		if (xa < 0) m_dir = 2;
		if (xa > 0) m_dir = 3;
		if (ya < 0) m_dir = 1;
		if (ya > 0) m_dir = 0;
	}
	return Entity::move(xa, ya);
}

bool Mob::isSwimming()
{
	Tile* tile = m_level->getTile((m_x + (TILE_SIZE)) / (FINAL_TILESIZE), (m_y + (TILE_SIZE * SCALE)) / (FINAL_TILESIZE));
	return tile == Tile::m_water;
}

bool Mob::blocks(Entity * e) {
	return e->isBlockableBy(this);
}

void Mob::hurt(Mob * mob, int damage, int attackDir)
{
	doHurt(damage, attackDir);
}

void Mob::hurt(Tile * tile, int x, int y, int damage)
{
	int attackDir = m_dir ^ 1;
	doHurt(damage, attackDir);
}

void Mob::heal(int heal) {
	
}

void Mob::doHurt(int damage, int attackDir) {
	
}

bool Mob::findStartPos(Level * level)
{
	return false;
}

ClassType Mob::classType()
{
	return MOB;
}