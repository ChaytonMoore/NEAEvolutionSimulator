#include "Creature.h"
#include <iostream>


//^If this doesn't work then just use a normal function

bool NearEqual(const float a, const float b)
{
	float aUpper = a + a * 0.05;
	float aLower = a - a * 0.05;
	return (b > aLower && b < aUpper);
}

void Creature::MuscleMovement()
{
	//For each of the muscles see what is the mod frequency of time.
	for (int i = 0; i < Muscles.size(); i++)
	{
		if (fmod(LocalTimeValue, Muscles[i]->Frequency) < mFrequencyTolerance)
		{
			//Set the selected muscle to movingin
			Muscles[i]->MovingIn = true;
		}
	}
}

Position Creature::GetCreatureLocation()
{
	float x = 0;
	float y = 0;

	for (size_t i = 0; i < Nodes.size(); i++)
	{
		x += Nodes[i]->Location.x;
		y += Nodes[i]->Location.y;
	}
	x = x / Nodes.size();
	y = y / Nodes.size();

	return Position(x,y);
	//This should return the average position
}

void Creature::SetCreatureArea()
{
	//Basic idea is that to determine the drag force
	float TopValue = Nodes[0]->Location.y;
	float LowerValue = Nodes[0]->Location.y;

	for (size_t i = 1; i < Nodes.size(); i++)
	{
		if (Nodes[i]->Location.y>TopValue)
		{
			TopValue = Nodes[i]->Location.y;
		}
		else if (Nodes[i]->Location.y < LowerValue)
		{
			LowerValue = Nodes[i]->Location.y;
		}
	}

	Area = TopValue - LowerValue; 
	//Should be updated all the time

}


//Water movement eq is
//Force = -0.5 * density * velocity^2 * area * constant *(something else, v with hat)

Position Creature::GetAverageLocation()
{
	Position output = Position(0,0);
	for (size_t i = 0; i < Nodes.size(); i++)
	{
		output += Nodes[i]->Location;
	}
	return (output / Nodes.size());

}


void Creature::EventTick(float DeltaTime)
{

	//Increase local time by deltatime
	LocalTimeValue += DeltaTime;

	MuscleMovement();

	SetCreatureArea();

	for (int i = 0; i < Nodes.size(); i++)
	{
		Nodes[i]->Area = Area;
		Nodes[i]->EventTick(DeltaTime);
		
	}
	
	for (size_t i = 0; i < Muscles.size(); i++)
	{
		Muscles[i]->MuscleTick(DeltaTime);

		
		if (fmod(LocalTimeValue, Muscles[i]->Frequency) < 0.1 && Muscles[i]->MovingIn == false && Muscles[i]->MovingOut == false)
		{
			//std::cout << "yes" << std::endl;
			Muscles[i]->MovingIn = true;
		}

		
	}
	
}
