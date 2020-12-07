#pragma once
#include <SFML/Graphics.hpp>
#include "Structures.h"
class Button
{
	sf::Vector2f BLeft;//Bottom left of the Button
	sf::Vector2f TRight;//Top right of the the Button
	bool isPressed = false;
	bool DefaultFunctionality = true;
	int(*fcnPtr)();//The function that is executed when the button is clicked unless the DefaultFunctionality variable is false 
private:



public:
	void InitButton(std::string ButtonText, DataCarrier* FontData);
	void InitButton(DataCarrier* FontData);
	bool isClicked();
	void ButtonTick();
	Button(std::string ButtonText, DataCarrier* FontData, sf::Vector2f ButtonPosition, sf::Vector2f ButtonSize);

	sf::RectangleShape shape;
	sf::Text text;


};
