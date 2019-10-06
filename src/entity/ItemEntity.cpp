#include "Entity.h"
#include "Mob.h"
#include "Player.h"
#include "../item/Item.h"
#include "../Sound.h"

#include "ItemEntity.h"

ItemEntity::ItemEntity(Item* item, int x, int y) :
	m_hurtTime(0),
	m_time(0),
	m_walkDist(0),
	m_dir(0)
{
	m_item = item;
	m_xx = m_x = x;
	m_yy = m_y = y;
	m_xr = 16;
	m_yr = 16;

	m_zz = 2;
	m_xa = m_random->nextFloat() * 0.3;
	m_ya = m_random->nextFloat() * 0.2;
	m_za = m_random->nextFloat() * 0.7 + 1;

	m_lifeTime = 60 * 10 + m_random->nextInt(60);
}

ItemEntity::~ItemEntity() {

}

void ItemEntity::tick() {
	m_time++;
	if (m_time >= m_lifeTime) {
		remove();
		return;
	}

	m_xx += m_xa;
	m_yy += m_ya;
	m_zz += m_za;

	if (m_zz < 0) {
		m_zz = 0;
		m_za *= -0.5;
		m_xa *= 0.6;
		m_ya *= 0.6;
	}

	m_za -= 0.15;
	int ox = m_x;
	int oy = m_y;
	int nx = (int)m_xx;
	int ny = (int)m_yy;
	int expectedx = nx - m_x;
	int expectedy = ny - m_y;
	move(nx - m_x, ny - m_y);
	int gotx = m_x - ox;
	int goty = m_y - oy;
	m_xx += gotx - expectedx;
	m_yy += goty - expectedy;

	if (m_hurtTime > 0)
		m_hurtTime--;
}

bool ItemEntity::isBlockableBy(Mob* mob) {
	return false;
}

void ItemEntity::render(Screen* screen) {
	if (m_time > m_lifeTime - 6 * 20) {
		if (m_time / 6 % 2 == 0) {
			return;
		}
	}
	
	screen->render(m_x - 16, m_y - 16, m_item->getSprite(), -1);
}

void ItemEntity::touchedBy(Entity* entity) {
		entity->touchItem(this);
}

void ItemEntity::take(Player* player) {
	Sound::m_pickup->play();
	m_item->onTake(this);
	remove();
}