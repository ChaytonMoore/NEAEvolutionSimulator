#pragma once
#include "Connection.h"
class Muscle :
	public Connection
{
public:
	float Frequency; //Really means how many seconds between each movement
	float Strength;
    bool MovingIn = false;
    bool MovingOut = false;
    

	Muscle()
	{

	}
	
	void MuscleTick(float DeltaTime);


private:
    float MovementProgress = 1;
    // ^No idea what this value should initially be
	
	
	
};
