#pragma once
#include "Bone.h"
#include "Muscle.h"
#include "Node.h"
#include "Structures.h"
class Creature
{
public:
	std::vector<Bone*> Bones;
	std::vector<Muscle*> Muscles;
	std::vector<Node*> Nodes;
	float Area;
	float Velocity;


	void EventTick(float DeltaTime);

	void MuscleMovement();
	Position GetAverageLocation();

private:
	//This variable is for the internal time of the creature starting from a zero point.
	float LocalTimeValue = 0;
	const float mFrequencyTolerance = 0.1;
	//^ Used in the muscle movement if statement, might want to try different values.

	void SetCreatureArea();

	Position GetCreatureLocation();

	Position OldLocation = Position(0,0);

};
