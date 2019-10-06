#include "../item/ToolType.h"
#include "../item/resource/Resource.h"

#include "../entity/Workbench.h"


#include "Crafting.h"

std::deque<Recipe*> Crafting::m_workbenchRecipes;

Crafting::Crafting() {
}

Crafting::~Crafting() {
}

void Crafting::init()
{

}