#include "Recipe.h"

#include "../item/Item.h"
#include "../item/resource/Resource.h"
#include "../entity/Player.h"

Recipe::~Recipe() {

}

Recipe::Recipe(Item * resultTemplate) :
	m_canCraft(false)
{
	m_resultTemplate = resultTemplate;
}

Recipe* Recipe::addCost(Resource* resource, int count)
{
	m_costs.push_back(new ResourceItem(resource, count));
	return this;
}

void Recipe::checkCanCraft(Player * player)
{
	for (deque<Item*>::iterator it = m_costs.begin(); it != m_costs.end(); it++)
	{
		Item * item = *it;
		if (item->instanceOf(RESOURCE_ITEM))
		{
			ResourceItem * ri = static_cast<ResourceItem*>(item);
			if (!player->m_backpack->hasResources(ri->m_resource, ri->m_count))
			{
				m_canCraft = false;
				return;
			}
		}
	}
	m_canCraft = true;
}

void Recipe::renderInventory(Screen * screen, int x, int y)
{
	screen->render(x, y, m_resultTemplate->getSprite(), m_resultTemplate->getColor(), 0);
}

void Recipe::deductCost(Player * player)
{
	for (deque<Item*>::iterator it = m_costs.begin(); it != m_costs.end(); it++)
	{
		Item * item = *it;
		if (item->instanceOf(RESOURCE_ITEM)) {
			ResourceItem * ri = static_cast<ResourceItem*>(item);
			player->m_backpack->removeResource(ri->m_resource, ri->m_count);
		}
	}
}