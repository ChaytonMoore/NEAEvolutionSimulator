#include <vector>
#include <iostream>

struct AnimDataRef
{
	std::string name;
	std::vector<std::string> FileNames;
};

struct AnimData
{
	AnimDataRef FileRef;
	std::vector<sf::texture> Textures;
	
};

