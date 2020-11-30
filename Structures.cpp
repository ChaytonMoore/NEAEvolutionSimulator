#include "Structures.h"
#include <iostream>


//So yes I deleted the stuff I'd done but it was shit
//Remeber deletes some of the comments



template<typename T>
struct TGraph
{

};

//I spent way too long debugging an error to do with this code only to discover it was todo with linkers.
sf::Font GetDefaultFont(DataCarrier* GetFontFrom)
{

	sf::Font font;
	//if(!font.loadFromFile(GetFontFrom->FilePath + GetFontFrom->DefaultFontFileName))
	if (!font.loadFromFile(GetFontFrom->getPath() + GetFontFrom->DefaultFontFileName))
	{
		std::cout << "error loading font";
		return font;
	}
	std::cout << "font loaded";
	
	return font;
}







//remeber to actually use the TArray for the Node struct

