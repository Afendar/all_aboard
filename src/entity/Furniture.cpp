#include "Backpack.h"

#include "Furniture.h"
#include "Player.h"
#include "Mob.h"
#include "../item/FurnitureItem.h"

Furniture::Furniture(std::string name) :
	m_pushTime(0),
	m_pushDir(-1),
	m_shouldTake(NULL)
{
	m_name = name;
	m_xr = 3;
	m_yr = 3;
}

Furniture::~Furniture() {
}

void Furniture::tick()
{
	if (m_shouldTake != NULL)
	{
		if (m_shouldTake->m_activeItem->instanceOf(POWERGLOVE_ITEM))
		{
			remove();
			m_shouldTake->m_backpack->add(0, m_shouldTake->m_activeItem);
			m_shouldTake->m_activeItem = new FurnitureItem(this);
		}
		m_shouldTake = NULL;
	}
	if (m_pushDir == 0) move(0, +1);
	if (m_pushDir == 1) move(0, -1);
	if (m_pushDir == 2) move(-1, 0);
	if (m_pushDir == 3) move(+1, 0);
	m_pushDir = -1;
	if (m_pushTime > 0) m_pushTime--;
}

void Furniture::renderCarry(Screen* screen) {
	screen->render(m_x, m_y, 6 + m_sprite + 5 * 32, -1);
}

void Furniture::render(Screen * screen)
{
	screen->render(m_x, m_y, (m_sprite * 2 + 9) * 32, -1);
	screen->render(m_x + TILE_SIZE * SCALE, m_y, 1 + (m_sprite * 2 + 9) * 32, -1);
	screen->render(m_x, m_y + TILE_SIZE * SCALE, (m_sprite * 2 + 10) * 32, -1);
	screen->render(m_x + TILE_SIZE * SCALE, m_y + TILE_SIZE * SCALE, 1 + (m_sprite * 2 + 10) * 32, -1);
}

bool Furniture::blocks(Entity * e)
{
	return true;
}

ClassType Furniture::classType()
{
	return FURNITURE;
}

void Furniture::touchedBy(Entity * entity)
{
	if (entity->instanceOf(PLAYER) && m_pushTime == 0)
	{
		m_pushDir = static_cast<Player*>(entity)->m_dir;
		m_pushTime = 10;
	}
}

void Furniture::take(Player * player)
{
	m_shouldTake = player;
}