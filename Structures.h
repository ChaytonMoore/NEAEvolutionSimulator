#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <windows.h>

//Struct declarations

//bool operator>(const sf::Vector2i& a, const sf::Vector2i& b);


//bool operator<(const sf::Vector2i& a, const sf::Vector2i& b);



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

struct DataCarrier
{
	std::string FilePath;
	std::string DefaultFontFileName;
	sf::Font StandardFont;

	std::string getPath() {
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		return std::string(buffer).substr(0, pos);
	}
};

sf::Font GetDefaultFont(DataCarrier* GetFontFrom);


template <typename T, typename X>
bool TContains(X item, std::vector<T> v)
{
	return (std::find(v.begin(), v.end(), item) != v.end());
	
}

template <typename T>
int TFindElem(T Elem, std::vector<T> Array)
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
*/
