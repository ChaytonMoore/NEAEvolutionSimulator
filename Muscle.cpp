#include "Muscle.h"
#include <iostream>

float Muscle::MuscleSize()
{
	return ends[0]->Location.DistanceTo(ends[1]->Location);
}

void Muscle::MuscleTick(float DeltaTime)
{
	//The basic idea for the tick is to decrease the value of MovementProgress by DeltaTime
	//With code elsewhere it will move the nodes and the stuff will visually update.
	//Initally this is going to look really bad, but I'll change it and stuff.


	if (MovingIn)
	{
		if (MovementProgress <= 0)
		{
			MovingOut = true;
			MovingIn = false;
			MovementProgress = 2;
			//std::cout << "r in" << std::endl;
		}

		ends[0]->ApplyForce(-Strength * Biases[0], ends[1]);
		ends[1]->ApplyForce(-Strength * Biases[1], ends[0]);
	}

	if (MovingOut)
	{
		if (MovementProgress <= 0)
		{
			MovingOut = false;
			MovingIn = true;
			MovementProgress = 2;
			//std::cout << "r out" << std::endl;
		}

		ends[0]->ApplyForce(Strength*Biases[2], ends[1]);
		ends[1]->ApplyForce(Strength*Biases[3], ends[0]);
	}

	MuscleOutput = Strength * (MovingIn -MovingOut);
	//Location.x = (ends[0]->Location.x + ends[1]->Location.x) / 2;
	//Location.y = (ends[0]->Location.y + ends[1]->Location.y) / 2;

	if ((MuscleSize() > (StartingDistance * 2) )&& MovingOut)
	{
		MovingIn = true;
		MovingOut = false;
		MovementProgress = 2;
		//std::cout <<  "s" << std::endl;
		//ends[0]->LatentVelocity = ends[0]->LatentVelocity * -1;
		//ends[1]->LatentVelocity = ends[1]->LatentVelocity * -1;
		ends[0]->LatentVelocity = ends[0]->LatentVelocity * -0.5;
		ends[1]->LatentVelocity = ends[1]->LatentVelocity * -0.5;
	}
	if (MovingIn && (MuscleSize() < (StartingDistance / 2)))
	{
		//std::cout << MovementProgress <<"aa"<< std::endl;
		MovingIn = false;
		MovingOut = true;
		MovementProgress = 2;
		//std::cout << MuscleSize() << std::endl;
		ends[0]->LatentVelocity = Position(0,0);
		ends[1]->LatentVelocity = Position(0, 0);
	}


	if (MuscleSize() < 1 && MuscleSize() < (StartingDistance / 3) && MuscleSize() != 0) //Must avoid divide by 0s
	{
		ends[0]->ApplyForce(Strength*Biases[2] * (1 / abs(MuscleSize())), ends[1]);
		ends[1]->ApplyForce(Strength*Biases[3] * (1 / abs(MuscleSize())), ends[0]);
		//^ Must use an abs for muscle size because otherwise it would just move between two different points
	}

	MovementProgress = MovementProgress - DeltaTime;

	


	if (MuscleSize() > StartingDistance * 2.5 && MovingIn)
	{
		//std::cout << MuscleSize() << std::endl;

		MovingIn = false;
		MovingOut = true;
		
	}
}
