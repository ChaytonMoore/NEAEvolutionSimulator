#pragma once
#include "Connection.h"
class Node :
	public Component
{
public:
	std::vector<Connection*> Connections;
	float Weight;

	Node()
	{

	}
};
