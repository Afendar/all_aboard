#include "Backpack.h"

#include "../item/resource/Resource.h"
#include "../item/Item.h"

#include "../item/FurnitureItem.h"

Backpack::Backpack()
{
}

Backpack::~Backpack()
{
	for (std::deque<Item*>::iterator it = m_items.begin(); it != m_items.end(); it++)
	{
		delete *it;
	}
}

void Backpack::add(Item * item)
{
	add(m_items.size(), item);
}

void Backpack::add(int slot, Item * item)
{
	if (item->instanceOf(RESOURCE_ITEM)) {
		ResourceItem * toTake = (ResourceItem*)item;
		ResourceItem * has = findResource(toTake->m_resource);
		if (has) {
			has->m_count += toTake->m_count;
			return;
		}
	}

	if (slot == 0) {
		m_items.push_front(item);
	}
	else {
		deque<Item*>::iterator slotIterator = m_items.begin() + slot;
		m_items.insert(slotIterator, item);
	}
}

bool Backpack::hasResources(Resource * resource, int count)
{
	ResourceItem * ri = findResource(resource);
	if (ri == NULL) return false;
	return ri->m_count >= count;
}

bool Backpack::removeResource(Resource * resource, int count)
{
	ResourceItem * ri = findResource(resource);
	if (ri == NULL) return false;
	if (ri->m_count < count) return false;
	ri->m_count -= count;
	if (ri->m_count <= 0)
	{
		remove(ri);
	}
	return true;
}

void Backpack::remove(Item * item)
{
	for (deque<Item*>::iterator it = m_items.begin(); it != m_items.end(); it++)
	{
		if (*it == item)
		{
			m_items.erase(it);
			return;
		}
	}
}

Item * Backpack::removeAt(int index)
{
	deque<Item*>::iterator it = m_items.begin() + index;
	Item * item = *it;
	m_items.erase(it);
	return item;
}

int Backpack::count(Item * item)
{
	if (item->instanceOf(RESOURCE_ITEM))
	{
		ResourceItem * ri = findResource(static_cast<ResourceItem*>(item)->m_resource);
		if (ri != NULL) return ri->m_count;
	}
	else
	{
		int count = 0;
		for (unsigned int i = 0; i < m_items.size(); ++i)
		{
			if (item->instanceOf(FURNITURE_ITEM))
			{
				if (m_items.at(i)->instanceOf(FURNITURE_ITEM))
				{
					FurnitureItem* inventoryItem = static_cast<FurnitureItem*>(m_items.at(i));
					FurnitureItem* currentItem = static_cast<FurnitureItem*>(item);
					if (inventoryItem->getName() == currentItem->getName())
						count++;
				}
			}
			else
			{
				if (m_items.at(i)->matches(item)) count++;
			}
		}
		return count;
	}
	return 0;
}

ResourceItem * Backpack::findResource(Resource * resource)
{
	for (deque<Item*>::iterator it = m_items.begin(); it != m_items.end(); it++)
	{
		Item * item = *it;
		if (item->instanceOf(RESOURCE_ITEM))
		{
			ResourceItem * has = static_cast<ResourceItem*>(item);
			if (has->m_resource == resource) return has;
		}
	}
	return NULL;
}
