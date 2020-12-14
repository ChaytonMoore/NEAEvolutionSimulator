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

	Muscle()
	{

	}

	void MuscleTick(float DeltaTime);

	float MuscleOutput = 0;

	Node* ends[2];
	float MovementProgress;

	float Biases[4] = {1,0.9,1,1.1};

	float MuscleSize();
private:
	
	// ^No idea what this value should initially be



};

