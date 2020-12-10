#pragma once
#include "Connection.h"
#include "Node.h"
class Muscle :
	public Connection
{
public:
	float Frequency = 3; //Really means how many seconds between each movement
	float Strength = 1;
	bool MovingIn = false;
	bool MovingOut = false;

    float StartingDistance;
    
    float StartTimeOffset; //This is used to make the muscles potentially move at different times though it might not be needed because the muscle frequencies will be different.

	Muscle()
	{

	}

	void MuscleTick(float DeltaTime);

	float MuscleOutput = 0;

	Node* ends[2];

private:
	float MovementProgress = 1;
	// ^No idea what this value should initially be



};
