#include "Entity.h"
#include "Mob.h"
#include "Player.h"
#include "../Random.h"
#include "../level/Level.h"

Random* Entity::m_random = new Random();

Entity::Entity() :
	m_xr(6),
	m_yr(6),
	m_removed(false),
	m_x(0),
	m_y(0) {

}

Entity::~Entity()
{
}


void Entity::render(Screen * screen)
{
}

void Entity::tick() {
}

void Entity::remove() {
	m_removed = true;
}

void Entity::init(Level * level) {
	m_level = level;
}

bool Entity::intersects(int x0, int y0, int x1, int y1) {
	return !(m_x + TILE_SIZE + m_xr < x0 || m_y + TILE_SIZE + m_yr < y0 || m_x - TILE_SIZE - m_xr > x1 || m_y - TILE_SIZE - m_yr > y1);
}

bool Entity::blocks(Entity * e) {
	return false;
}

void Entity::hurt(Mob * mob, int dmg, int attackDir)
{
}

void Entity::hurt(Tile * tile, int x, int y, int dmg) {
}

bool Entity::move(int xa, int ya)
{
	if (xa != 0 || ya != 0)
	{
		bool stopped = true;
		if (xa != 0 && move2(xa, 0)) stopped = false;
		if (ya != 0 && move2(0, ya)) stopped = false;
		if (!stopped)
		{
			int xt = m_x / FINAL_TILESIZE;
			int yt = m_y / FINAL_TILESIZE;
			m_level->getTile(xt, yt)->steppedOn(m_level, xt, yt, this);
		}
		return !stopped;
	}
	return true;
}

bool Entity::move2(int xa, int ya) {
	if (xa != 0 && ya != 0)
		return false;

	int xto0 = (m_x + TILE_SIZE - m_xr) / FINAL_TILESIZE;
	int yto0 = (m_y + TILE_SIZE - m_yr) / FINAL_TILESIZE;
	int xto1 = (m_x + TILE_SIZE + m_xr) / FINAL_TILESIZE;
	int yto1 = (m_y + TILE_SIZE + m_yr) / FINAL_TILESIZE;

	int xt0 = (m_x + xa + TILE_SIZE - m_xr) / FINAL_TILESIZE;
	int yt0 = (m_y + ya + TILE_SIZE - m_yr) / FINAL_TILESIZE;
	int xt1 = (m_x + xa + TILE_SIZE + m_xr) / FINAL_TILESIZE;
	int yt1 = (m_y + ya + TILE_SIZE + m_yr) / FINAL_TILESIZE;
	bool blocked = false;

	for (int yt = yt0; yt <= yt1; yt++)
		for (int xt = xt0; xt <= xt1; xt++)
		{
			if (xt >= xto0 && xt <= xto1 && yt >= yto0 && yt <= yto1) continue;

			m_level->getTile(xt, yt)->bumpedInto(m_level, xt, yt, this);

			if (!m_level->getTile(xt, yt)->mayPass(m_level, xt, yt, this))
			{
				blocked = true;
				return false;
			}
		}

	if (blocked) return false;

	std::auto_ptr<std::list<Entity*> > wasInside(m_level->getEntities(m_x - m_xr, m_y - m_yr, m_x + m_xr, m_y + m_yr, this));
	std::auto_ptr<std::list<Entity*> > isInside(m_level->getEntities(m_x + xa - m_xr, m_y + ya - m_yr, m_x + xa + m_xr, m_y + ya + m_yr, this));

	if (!isInside->empty())
	{
 		for (std::list<Entity*>::iterator it = isInside->begin(); it != isInside->end(); it++)
		{
			Entity * e = *it;
			if (e == this) continue;

			e->touchedBy(this);
		}

		if (!wasInside->empty())
		{
			//isInside.removeAll(wasInside);
			for (std::list<Entity*>::iterator it = wasInside->begin(); it != wasInside->end(); it++)
			{
				isInside->remove(*it);
			}
		}

		for (std::list<Entity*>::iterator it = isInside->begin(); it != isInside->end(); it++)
		{
			Entity * e = *it;
			if (e == this) continue;

			if (e->blocks(this))
			{
				return false;
			}
		}
	}

	m_x += xa;
	m_y += ya;
	return true;
}

void Entity::touchedBy(Entity * entity)
{
}

bool Entity::isRemoved()
{
	return m_removed;
}

void Entity::setRemoved(bool removed)
{
	m_removed = removed;
}

int Entity::getX()
{
	return m_x;
}

void Entity::setX(int x)
{
	m_x = x;
}

int Entity::getY()
{
	return m_y;
}

void Entity::setY(int y)
{
	m_y = y;
}

bool Entity::isBlockableBy(Mob * mob)
{
	return true;
}

void Entity::touchItem(ItemEntity * itemEntity)
{
}

bool Entity::canSwim()
{
	return false;
}

bool Entity::interact(Player * player, Item * item, int attackDir)
{
	return false;
}

bool Entity::use(Player * player, int attackDir)
{
	return false;
}

int Entity::getLightRadius() {
	return 0;
}