#include "Resource.h"
#include "../../level/tile/Tile.h"
#include "../../level/Level.h"
#include "../../entity/Player.h"

Resource* Resource::m_blackberrie;
Resource* Resource::m_rope;
Resource* Resource::m_wool;
Resource* Resource::m_wood;
Resource* Resource::m_backpack;

Resource::~Resource() {

}

void Resource::init() {
	Resource::m_blackberrie = new Resource("Blackberries", 25, -1);
	Resource::m_rope = new Resource("Rope", 26, -1);
	Resource::m_wool = new Resource("Wool", 27 + 32, -1);
	Resource::m_wood = new Resource("Wood", 26 + 32, -1);
	Resource::m_backpack = new Resource("Backpack", 27, -1);
}

void Resource::initPlantable() {
}

Resource::Resource(std::string name, int sprite, int color) {
	m_name = name;
	m_sprite = sprite;
}

bool Resource::interactOn(Tile* tile, Level* level, int xt, int yt, Player* player, int attackDir) {
	return false;
}