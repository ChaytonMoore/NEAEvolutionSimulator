#include "Button.h"
#include <iostream>



Button::Button(std::string ButtonText, DataCarrier* FontData, sf::Vector2f ButtonPosition, sf::Vector2f ButtonSize)
{
	// select the font
	FontData->StandardFont = GetDefaultFont(FontData);
	text.setFont(FontData->StandardFont); //Need to get the DataCarrier that contains the default font

	// set the string to display
	text.setString(ButtonText);

	// set the character size
	text.setCharacterSize(12);

	text.setFillColor(sf::Color::Green);

	text.setPosition(ButtonPosition);

	// set up the button stuff
	shape.setSize(ButtonSize);
	shape.setOutlineColor(sf::Color::Red);
	shape.setFillColor(sf::Color::Blue);
	shape.setOutlineThickness(5);
	shape.setPosition(ButtonPosition);

	BLeft = ButtonPosition;
	TRight = ButtonPosition + ButtonSize;
	

}

void Button::InitButton(std::string ButtonText, DataCarrier* FontData)
{
		// select the font
		text.setFont(GetDefaultFont(FontData)); //Need to get the DataCarrier that contains the default font

		// set the string to display
		text.setString(ButtonText);

		// set the character size
		text.setCharacterSize(12);

		// set up the button stuff
		shape.setSize(sf::Vector2f(100, 50));
		shape.setOutlineColor(sf::Color::Red);
		shape.setOutlineThickness(5);
		shape.setPosition(10, 20);
}

	//This function is for when I don't want to put a button there.
void Button::InitButton(DataCarrier* FontData)
{
		// select the font
		text.setFont(GetDefaultFont(FontData)); //Need to get the DataCarrier that contains the default font

		// set the string to display
		text.setString("Button");

		// set the character size
		text.setCharacterSize(12);
}


bool Button::isClicked()
{
		sf::Vector2i MousePosition = sf::Mouse::getPosition();;
		if (MousePosition.x > BLeft.x && MousePosition.y > BLeft.y && MousePosition.x < TRight.x && MousePosition.y < TRight.y && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			isPressed = true;
		}
		else
		{
			isPressed = false;
		}
		return isPressed;
}

void Button::ButtonTick()
{
		//This is the code for the button that is executed every tick
	if (DefaultFunctionality&&isClicked())
	{
		fcnPtr();
		std::cout << "clicked" << std::endl;
		//Executes the buttons default code
	}
	std::cout << sf::Mouse::getPosition().x << std::endl;
}
