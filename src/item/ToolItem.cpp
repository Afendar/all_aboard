#include "ToolItem.h"

#include "../Screen.h"
#include "../entity/ItemEntity.h"
#include "../entity/Entity.h"

ToolItem::ToolItem(ToolType * type)
	:m_random(new Random())
{
	this->m_type = type;
}

ToolItem::~ToolItem() {

}

int ToolItem::getSprite() {
	return m_type->m_sprite + 32;
}

void ToolItem::renderIcon(Screen* screen, int x, int y, int alpha) {
	screen->render(x, y, getSprite(), sf::Color(255, 255, 255, alpha).toInteger(), 0);
}

void ToolItem::renderInventory(Screen * screen, int x, int y) {
	screen->render(x, y, getSprite(), -1, 0);
}

string ToolItem::getName() {
	return m_type->m_name;
}

void ToolItem::onTake(ItemEntity * itemEntity) {

}

bool ToolItem::canAttack() {
	return true;
}

int ToolItem::getAttackDamageBonus(Entity * e) {
	if (m_type == ToolType::m_axe) {
		return  m_random->nextInt(5);
	}
	return 1;
}

bool ToolItem::matches(Item * item) {
	if (item->instanceOf(TOOL_ITEM)) {
		ToolItem * other = (ToolItem*)item;
		if (other->m_type != m_type) return false;
		return true;
	}
	return false;
}

ClassType ToolItem::classType() {
	return TOOL_ITEM;
}