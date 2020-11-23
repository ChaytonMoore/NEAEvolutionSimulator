#pragma once
#include <vector>
#include<string>

//Struct declarations
//Yeah some of this is bad practise.

struct DataCarrier();




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


template <typename T, typename X>
bool Contains(X item, std::vector<T> v)
{
	return (std::find(v.begin(), v.end(), item) != v.end());
	
}

template <typename T>
int FindElem(T Elem, std::vector<T> Array)
{
	int idx = -1;
	for (size_t i = 0; i < Array.size(); i++)
	{
		if (Array[i] == Elem)
		{
			idx = i;
		}
	}
	return idx;
}


/*
template <typename T>
struct Atlas
{
	int size;
	T* elements;
};
template <typename T>
struct Node
{
	T value;
	Node* Right;
	Node* Left;
};
template <typename T>
struct GraphNode
{
	T value;
	TArray<GraphNode*> Connections;
};
*
