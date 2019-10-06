#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>

#include "../Typeable.h"

class Screen;
class Player;
class Tile;
class Level;
class Entity;
class ItemEntity;

using namespace std;

class Item : public Typeable {
public:
	virtual int getColor();
	virtual int getSprite();
	virtual void onTake(ItemEntity * itemEntity);
	virtual void renderInventory(Screen * screen, int x, int y);
	virtual bool interact(Player * player, Entity * entity, int attackDir);
	virtual void renderIcon(Screen * screen, int x, int y, int alpha);
	virtual bool interactOn(Tile * tile, Level * level, int xt, int yt, Player * player, int attackDir);
	virtual bool isDepleted();
	virtual bool canAttack();
	virtual int getAttackDamageBonus(Entity * e);
	virtual string getName();
	virtual bool matches(Item * item);
};