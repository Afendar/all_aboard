#include "ToolType.h"

ToolType* ToolType::m_sword = new ToolType("Sword", 22);
ToolType* ToolType::m_axe = new ToolType("Axe", 23);

ToolType::ToolType(std::string name, int sprite) {
	m_name = name;
	m_sprite = sprite;
}

ToolType::~ToolType() {

}