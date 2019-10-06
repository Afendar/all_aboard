#pragma once

#include <string>

class Tile;
class Level;
class Player;

class Resource {
	public:
		Resource(std::string name, int sprite, int color);
		virtual ~Resource();

		static Resource* m_blackberrie;
		static Resource* m_rope;
		static Resource* m_wool;
		static Resource* m_wood;
		static Resource* m_backpack;

		std::string m_name;
		int m_sprite;
		int m_color;

		static void init();
		static void initPlantable();
		virtual bool interactOn(Tile* tile, Level* level, int xt, int yt, Player* player, int attackDir);
};