#include "Achievement.h"

#include "../Font.h"
#include "../item/ResourceItem.h"
#include "../Sound.h"


#include <iostream>

Achievement::Achievement(std::string label, Item* item)
{
	m_tickTime = 0;
	Sound::m_unlock->play();
	m_label = label;
	m_item = item;
}

Achievement::~Achievement()
{
}

void Achievement::init()
{
}

void Achievement::tick()
{
	m_tickTime++;
	if (m_tickTime > 60 && m_alpha > 0) {
		m_alpha-=3;
		if (m_alpha < 0) m_alpha = 0;
	}
}

void Achievement::render(Screen * screen)
{
	if (m_alpha <= 0) {
		return;
	}

	int xo = 12;
	int yo = 1;
	Font::renderAchievement(screen, m_label, m_item, xo, yo, xo + 7, yo + 2, m_alpha);
}
