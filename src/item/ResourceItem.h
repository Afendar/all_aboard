#pragma once

#include "Item.h"
#include "../entity/ItemEntity.h"
#include "../level/Level.h"
#include "../level/tile/Tile.h"
#include "../Screen.h"
#include "resource/Resource.h"

class Player;

class ResourceItem : public Item {
	public:

		ResourceItem(Resource* resource);
		ResourceItem(Resource* resource, int count);
		virtual ~ResourceItem();

		int getSprite();
		void renderIcon(Screen * screen, int x, int y, int alpha);
		void renderInventory(Screen * screen, int x, int y);
		string getName();
		void onTake(ItemEntity * itemEntity);
		bool interactOn(Tile * tile, Level * level, int xt, int yt, Player * player, int attackDir);
		bool isDepleted();
		ClassType classType();

		Resource* m_resource;
		int m_count;
};