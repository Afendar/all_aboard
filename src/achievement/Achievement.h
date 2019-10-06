#pragma once

#include <vector>
#include "../Screen.h"
#include "../item/Item.h"

struct AchievementData {
	std::string m_desc;
	int m_num;
	Item* m_item;
};

class Achievement {
	public:
		Achievement(std::string label, Item* item);
		virtual ~Achievement();

		void init();
		void tick();
		void render(Screen* screen);

		int m_tickTime;
		int m_alpha = 255;

		Item* m_item;
		std::string m_label;
};