#pragma once

#include "Furniture.h"

class Player;

class Workbench : public Furniture {
	public:
		Workbench();
		virtual ~Workbench();
		bool use(Player* player, int attackDir);
};