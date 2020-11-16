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

	void EventTick(float DeltaTime);



};
