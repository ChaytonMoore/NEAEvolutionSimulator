#pragma once
#include "Structures.h"
class Component
{
	void EventTick(float DeltaTime);
public:
	Position Location = Position(0, 0);

	Component()
	{

	}

};
