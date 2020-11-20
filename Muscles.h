#pragma once
#include "Connection.h"
class Muscle :
	public Connection
{
public:
	float Frequency; //Really means how many seconds between each movement
	float Strength;

	Muscle()
	{

	}
};
