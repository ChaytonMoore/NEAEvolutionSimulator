#pragma once
#include "Connection.h"
class Node :
	public Component
{
public:
	std::vector<Connection*> Connections;
	float Weight = 1;
	Position Location = Position(0, 0);

	
	

	float CreatureArea;

	Node();

	float Area;//This is gotten from the creature it belongs to.




	static Position MovementResistance(float area, Position velocity);
	void EventTick(float DeltaTime);
	Position NodeVelocity(Node* InputNode);
	Position LatentVelocity = Position(0, 0);
	void ApplyForce(float strength, Node* OtherNode);



private:
	void WeightFunction();
	void MuscleMovement();

	

};

