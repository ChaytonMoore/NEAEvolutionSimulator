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
	shape.setOutlineThickness(1);
	shape.setPosition(ButtonPosition);

	TLeft = ButtonPosition;
	BRight = ButtonPosition + ButtonSize;


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
	shape.setOutlineThickness(1);
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


bool Button::isClicked(sf::RenderWindow* Window)
{


	if (ButtonUsable)
	{
		

		ButtonUsable = false;

		return MouseInButton(Window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
	}
	else
	{
		return false;
	}
	
}


bool Button::MouseInButton(sf::RenderWindow* Window)
{
	return ((Window->getPosition().x + int(TLeft.x) < sf::Mouse::getPosition().x) && (Window->getPosition().y + int(TLeft.y) < sf::Mouse::getPosition().y - 30) && (Window->getPosition().x + int(BRight.x) > sf::Mouse::getPosition().x) && (Window->getPosition().y + int(BRight.y) > sf::Mouse::getPosition().y-30));
}

void Button::ButtonTick(sf::RenderWindow* Window)
{
	//This is the code for the button that is executed every tick
	if (DefaultFunctionality&&MouseInButton(Window)&& sf::Mouse::isButtonPressed(sf::Mouse::Left)&&ButtonUsable)
	{
		fcnPtr(Window);
		//std::cout << "clicked" << std::endl;
		ButtonUsable = false;
		
		//Executes the buttons default code
	}
	if (MouseInButton(Window))
	{
		isPressed = true;
	}
	else
	{
		isPressed = false;
	}

	if (!ButtonUsable)
	{

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			
			ButtonUsable = true;
		}
	}
	
	//else
	//{
	//	std::cout << Window->getPosition().y + int(TLeft.y) <<""<<sf::Mouse::getPosition().y<<std::endl;
	//}

	//std::cout << sf::Mouse::getPosition().x << std::endl;
}
