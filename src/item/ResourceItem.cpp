#include "ResourceItem.h"

#include "../entity/Player.h"

#include <sstream>

ResourceItem::~ResourceItem() {

}

ResourceItem::ResourceItem(Resource* resource) :
	m_count(1)
{
	m_resource = resource;
}

ResourceItem::ResourceItem(Resource* resource, int count) {
	m_resource = resource;
	m_count = count;
}

int ResourceItem::getSprite() {
	return m_resource->m_sprite;
}

void ResourceItem::renderIcon(Screen * screen, int x, int y, int alpha) {
	screen->render(x, y, m_resource->m_sprite, sf::Color(255, 255, 255, alpha).toInteger(), 0);
}

void ResourceItem::renderInventory(Screen * screen, int x, int y) {
	screen->render(x, y, m_resource->m_sprite, m_resource->m_color, 0);
	int cc = m_count;
	if (m_count > 999) cc = 999;
	stringstream ss;
	ss << cc;
}

std::string ResourceItem::getName() {
	return m_resource->m_name;
}

void ResourceItem::onTake(ItemEntity * itemEntity) {

}

bool ResourceItem::interactOn(Tile * tile, Level * level, int xt, int yt, Player * player, int attackDir) {
	if (m_resource->interactOn(tile, level, xt, yt, player, attackDir)) {
		m_count--;
		return true;
	}
	return false;
}

bool ResourceItem::isDepleted() {
	return m_count <= 0;
}

ClassType ResourceItem::classType() {
	return RESOURCE_ITEM;
}