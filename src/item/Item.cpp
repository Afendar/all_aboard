#include "Item.h"

int Item::getColor()
{
	return sf::Color(255, 255, 255).toInteger();
}

int Item::getSprite()
{
	return 0;
}

void Item::onTake(ItemEntity * itemEntity)
{
}

void Item::renderInventory(Screen * screen, int x, int y) {
}

bool Item::interact(Player * player, Entity * entity, int attackDir) {
	return false;
}

void Item::renderIcon(Screen * screen, int x, int y, int alpha) {
}

bool Item::interactOn(Tile * tile, Level * level, int xt, int yt, Player * player, int attackDir) {
	return false;
}

bool Item::isDepleted() {
	return false;
}

bool Item::canAttack() {
	return false;
}

int Item::getAttackDamageBonus(Entity * e) {
	return 0;
}

std::string Item::getName()
{
	return "";
}

bool Item::matches(Item * item)
{
	return (classType() != UNDEFINED) && (item->classType() == classType());
}