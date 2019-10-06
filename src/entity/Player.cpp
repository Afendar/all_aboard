#include "Player.h"
#include "../Game.h"

#include "../menu/BackpackMenu.h"
#include "../menu/WonMenu.h"
#include "../Sound.h"
#include "../particle/HitParticle.h"

#include "../item/ToolItem.h"
#include "../Font.h"

#include <memory>
#include <iostream>

Player::~Player()
{
}

Player::Player(Game * game, InputHandler* input) :
	m_backpack(new Backpack()),
	m_attackItem(NULL),
	m_activeItem(NULL),
	m_staminaRecharge(0),
	m_staminaRechargeDelay(0),
	m_maxStamina(10),
	m_invulnerableTime(0),
	m_onStairDelay(0),
	m_score(0),
	m_attackTime(0)
{
	m_game = game;
	m_input = input;
	m_x = 18 * FINAL_TILESIZE;
	m_y = 30 * FINAL_TILESIZE;
	m_stamina = m_maxStamina;
	m_backpackUnlocked = false;
}

void Player::tick() {
	Mob::tick();

	if (m_invulnerableTime > 0) m_invulnerableTime--;

	int xa = 0;
	int ya = 0;
	if (m_input->up->down) {
		ya-=3;
	}
	if (m_input->down->down) {
		ya+=3;
	}
	if (m_input->left->down) {
		xa-=3;
	}
	if (m_input->right->down) {
		xa+=3;
	}

	if (m_input->attack->clicked) {
		attack();
	}

	if (m_input->backpack->clicked) {
		//m_game->setMenu(new WonMenu());
		if (m_backpackUnlocked) {
			m_game->setMenu(new BackpackMenu(this));
		}
	}

	if (m_input->select->clicked) {
		if (!use()) {
			interact();
		}
	}


	move(xa, ya);

	if (m_attackTime > 0) {
		m_attackTime--;
	}
}

void Player::render(Screen* screen) {
	int xt = 6;
	int yt = 30;
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

	if (m_attackTime > 0) {
		switch (m_attackDir) {
			case 0:
				screen->render(m_x, m_y + 24, 24 + 32, -1);
				break;
			case 1:
				screen->render(m_x, m_y - 2, 24 + 32, -1);
				break;
			case 2:
				screen->render(m_x - 12, m_y + 16, 24 + 32, -1);
				break;
			case 3:
				screen->render(m_x + 14, m_y + 16, 24 + 32, -1);
				break;
		}
	}
}

void Player::renderPortrait(Screen* screen, int x, int y) {
	screen->render(x, y, 2 + 22 * 32, -1);
}

void Player::touchItem(ItemEntity * itemEntity)
{
	if (!m_backpackUnlocked) {
		return;
	}

	itemEntity->take(this);
	m_backpack->add(itemEntity->m_item);
}

bool Player::canSwim()
{
	return true;
}

ClassType Player::classType() {
	return PLAYER;
}

bool Player::interact() {
	if (m_dir == 0 && interact(m_x - 10, m_y + 6, m_x + 10, m_y + 14))
		return true;
	if (m_dir == 1 && interact(m_x - 10, m_y - 14, m_x + 10, m_y - 6))
		return true;
	if (m_dir == 3 && interact(m_x + 6, m_y - 10, m_x + 14, m_y + 10))
		return true;
	if (m_dir == 2 && interact(m_x - 14, m_y - 10, m_x - 6, m_y + 10))
		return true;
}

bool Player::use(){

	if (m_dir == 0 && use(m_x - 8, m_y + 4, m_x + 8, m_y + 12))
		return true;
	if (m_dir == 1 && use(m_x - 8, m_y - 12, m_x + 8, m_y - 4))
		return true;
	if (m_dir == 3 && use(m_x + 4, m_y - 8, m_x + 12, m_y + 8))
		return true;
	if (m_dir == 2 && use(m_x - 12, m_y - 8, m_x - 4, m_y + 8))
		return true;

	int xt = m_x / (FINAL_TILESIZE);
	int yt = m_y / (FINAL_TILESIZE);

	if (xt >= 0 && yt >= 0 && xt < m_level->getWidth() && yt < m_level->getHeight()) {
		if (m_level->getTile(xt, yt)->use(m_level, xt, yt, this, m_attackDir)) {
			return true;
		}
	}

	return false;
}

void Player::attack(){

	m_attackDir = m_dir;

	int xt = (m_x + 16) / FINAL_TILESIZE;
	int yt = (m_y + 32) / FINAL_TILESIZE;
	switch (m_attackDir) {
	case 0:
		yt = (m_y + 52) / FINAL_TILESIZE;
		break;
	case 1:
		yt = (m_y - 10) / FINAL_TILESIZE;
		break;
	case 2:
		xt = (m_x - 10) / FINAL_TILESIZE;
		break;
	case 3:
		xt = (m_x + 32) / FINAL_TILESIZE;
		break;
	}

	bool done = false;

	if (m_activeItem != NULL) {
		if (xt >= 0 && yt >= 0 && xt < m_level->getWidth() && yt < m_level->getHeight()) {
			if (m_level->getTile(xt, yt)->interact(m_level, xt, yt, this, m_activeItem, m_attackDir)) {
				done = true;
			}
		}
	}

	if (done) {
		return;
	}

	if (m_activeItem == NULL || m_activeItem->canAttack()) {
		m_attackTime = 5;
		if (xt >= 0 && yt >= 0 && xt < m_level->getWidth() && yt < m_level->getHeight()) {
			m_level->getTile(xt, yt)->hurt(m_level, xt, yt, this, m_random->nextInt(3) + 1, m_attackDir);
		}
	}
}

bool Player::use(int x0, int y0, int x1, int y1){
	return false;
}

bool Player::interact(int x0, int y0, int x1, int y1){
	std::auto_ptr<std::list<Entity*>> entities(m_level->getEntities(x0, y0, x1, y1));
	for (std::list<Entity*>::iterator it = entities->begin(); it != entities->end(); it++) {
		Entity* e = *it;
		if (e != this) {
			if(e->interact(this, m_activeItem, m_attackDir)){
				return true;
			}
		}
	}
	return true;
}

void Player::die()
{
	Mob::die();
}

void Player::doHurt(int damage, int attackDir)
{
	if (m_hurtTime > 0 || m_invulnerableTime > 0) {
		return;
	}

	Sound::m_hit->play();
	m_level->add(new HitParticle(m_x, m_y));
	m_health -= damage;
	if (attackDir == 0) m_yKnockback = 6;
	if (attackDir == 1) m_yKnockback = -6;
	if (attackDir == 2) m_xKnockback = -6;
	if (attackDir == 3) m_xKnockback = 6;

	m_hurtTime = 10;
	m_invulnerableTime = 30;
}
