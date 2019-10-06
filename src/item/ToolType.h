#pragma once

#include <string>

class ToolType {
	public:
		ToolType(std::string name, int sprite);
		virtual ~ToolType();
		
		static ToolType* m_sword;
		static ToolType* m_axe;

		std::string m_name;
		int m_sprite;
};