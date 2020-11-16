#pragma once
#include <vector>

//Struct declarations

struct Position
{
	float x, y;

	Position(float a, float b)
	{
		x = a;
		y = b;
	}

	float DistanceTo(Position Other)
	{
		return pow((pow((x-Other.x),2)+pow((y-Other.y),2)),0.5);
	}
};
