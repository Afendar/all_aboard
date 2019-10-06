#pragma once

#include "../entity/Entity.h"
#include "../Screen.h"

class Particle : public Entity {
	public:
		Particle() {};
		virtual ~Particle() {};
		virtual void tick() {};
		virtual void render(Screen* screen) {};
};