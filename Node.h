#pragma once
#include "Connection.h"
class Node :
	public Component
{
public:
	std::vector<Connection*> Connections;
	float Weight;
	Position Location;
	//Think this line ^ is correct words might be the other way round.

	Node()
	{

	}
private:
	void WeightFunction();
	void MuscleMovement();
};
