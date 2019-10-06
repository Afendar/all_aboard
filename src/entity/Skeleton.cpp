#include "Skeleton.h"

#include "../Screen.h"
#include "../item/ResourceItem.h"
#include "../item/resource/Resource.h"
#include "Player.h"

#include <cmath>
#include <iostream>

Skeleton::Skeleton() :
	m_randomWalkTime(0)
{
	m_x = m_random->nextInt(64 * 16);
	m_y = m_random->nextInt(64 * 16);
}

Skeleton::~Skeleton()
{
}

void Skeleton::tick()
{
	Mob::tick();

	if (m_level->m_player != NULL && m_randomWalkTime == 0) {

		int xd = m_level->m_player->getX() - m_x;
		int yd = m_level->m_player->getY() - m_y;

		if (xd * xd + yd * yd < 200 * 200) {
			m_xa = 0;
			m_ya = 0;
			if (xd < 0) m_xa = -2;
			if (xd > 0) m_xa = 2;
			if (yd < 0)m_ya = -2;
			if (yd > 0)m_ya = 2;
		}
	}

	int speed = m_tickTime & 1;
	if (!move(m_xa * speed, m_ya * speed) || m_random->nextInt(200) == 0) {
		m_randomWalkTime = 60;
		m_xa = (m_random->nextInt(3) - 1) * m_random->nextInt(2);
		m_ya = (m_random->nextInt(3) - 1) * m_random->nextInt(2);
	}

	if (m_randomWalkTime > 0) m_randomWalkTime--;
}

void Skeleton::render(Screen * screen)
{
	int xt = 6;
	int yt = 28;
	int flip = 0;
	int flip2 = ((m_walkDist / 9) & 1);

	if (m_dir == 1) {
		xt += 2;
	}
	if (m_dir > 1) {
		flip2 = 0;
		if (m_dir == 3) {
			flip = 1;
			flip2 = 1;
		}
		xt += 4 + ((m_walkDist / 9) & 1) * 2;
	}

	int yo = m_y - 11;

	screen->render(m_x, m_y, xt + yt * 32, 32, 16, -1, flip);
	screen->render(m_x, m_y + 32, xt + (yt + 1) * 32, 32, 16, -1, flip2);
}

void Skeleton::die()
{
	Mob::die();

	if (m_level->m_player) {
		m_level->m_player->m_score += 50;
	}
}

void Skeleton::touchedBy(Entity* entity)
{
	if (entity->instanceOf(PLAYER)) {
		entity->hurt(this, 1, m_dir);
	}
}