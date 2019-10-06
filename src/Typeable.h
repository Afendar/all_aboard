#pragma once

enum ClassType
{
	UNDEFINED,
	MOB,
	NPC,
	PLAYER,
	TOOL_ITEM,
	RESOURCE_ITEM,
	POWERGLOVE_ITEM,
	FURNITURE_ITEM,
	FURNITURE
};

class Typeable 
{
	public:
		bool instanceOf(ClassType t)
		{
			if (this->classType() == t)
				return true;
			return false;
		}

		virtual ClassType classType()
		{
			return UNDEFINED;
		}
};