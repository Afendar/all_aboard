#pragma once

#include <deque>

class Item;
class Resource;

#include "../item/ResourceItem.h"

class Backpack {
	public:
		Backpack();
		virtual ~Backpack();

		std::deque<Item*> m_items;

		void add(Item* item);
		void add(int slot, Item* item);
		bool hasResources(Resource* resource, int count);
		bool removeResource(Resource* resource, int count);
		void remove(Item* item);
		Item* removeAt(int index);
		int count(Item* item);

	private:
		ResourceItem* findResource(Resource* resource);
};