#include "FurnitureItem.h"

#include "../Font.h"
#include "../screen.h"
#include "../level/Level.h"
#include "../entity/ItemEntity.h"
#include "../entity/Entity.h"

FurnitureItem::FurnitureItem(Furniture* furniture) :
	m_placed(false)
{
	m_furniture = furniture;
}

FurnitureItem::~FurnitureItem() {
}

int FurnitureItem::getSprite()
{
	return 6 + m_furniture->m_sprite + 5 * 32;
}

void FurnitureItem::renderIcon(Screen* screen, int x, int y) {
	screen->render(x, y, getSprite(), -1, 0);
}

void FurnitureItem::renderInventory(Screen * screen, int x, int y)
{
	screen->render(x, y, getSprite(), -1, 0);
}

void FurnitureItem::onTake(ItemEntity * itemEntity) {
}

bool FurnitureItem::canAttack() {
	return false;
}

bool FurnitureItem::interactOn(Tile * tile, Level * level, int xt, int yt, Player * player, int attackDir) {
	if (tile->mayPass(level, xt, yt, m_furniture))
	{
		m_furniture->setX(xt * FINAL_TILESIZE);
		m_furniture->setY(yt * FINAL_TILESIZE);
		level->add(m_furniture);
		m_placed = true;
		return true;
	}
	return false;
}

bool FurnitureItem::isDepleted()
{
	return m_placed;
}

std::string FurnitureItem::getName()
{
	return m_furniture->m_name;
}

ClassType FurnitureItem::classType()
{
	return FURNITURE_ITEM;
}