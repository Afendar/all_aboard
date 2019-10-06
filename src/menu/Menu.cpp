#include "Menu.h"

#include "../Font.h"
#include "../Game.h"
#include "../InputHandler.h"

Menu::Menu() : 
	m_isTransparent(false){
}

void Menu::init(Game* game, InputHandler* input)
{
	m_game = game;
	m_input = input;
}

void Menu::tick() {

}

void Menu::render(Screen* screen) {

}

void Menu::renderItemList(Screen * screen, int xo, int yo, int x1, int y1, std::deque<Item*>& listItems, int selected)
{
	bool renderCursor = true;
	if (selected < 0) {
		selected = -selected - 1;
		renderCursor = false;
	}

	for (int i = 0; i < 10; i++) {
		int xx = i % 5;
		int yy = i / 5;

		screen->render((1 + xo + xx) * 32, (yo + 1 + yy) * 32, 30 + 2 * 32, -1);
	}

	for (int i = 0; i < listItems.size(); i++) {
		int xx = i % 5;
		int yy = i / 5;

		if (listItems.at(i) != nullptr) {
			Item* item = listItems.at(i);
			if (i == selected) {
				int count = 1;
				if (item->classType() == ClassType::RESOURCE_ITEM) {
					ResourceItem* resource = static_cast<ResourceItem*>(item);
					count = resource->m_count;
				}
				Font::draw(std::to_string(count) + " " + item->getName(), screen, xo * TILE_SIZE * SCALE, y1 * TILE_SIZE * SCALE + TILE_SIZE, Font::m_font, sf::Color(68, 57, 52).toInteger(), 13);
			}

			listItems.at(i)->renderInventory(screen, (1 + xo + xx) * 32, (yo + 1 + yy) * 32);
		}
	}

	if (renderCursor) {
		int xx = selected % 5;
		int yy = selected / 5;
		screen->render((1 + xo + xx) * 32, (yo + 1 + yy) * 32, 31 + 2 * 32, -1);
	}
}

bool Menu::isTransparent() {
	return m_isTransparent;
}