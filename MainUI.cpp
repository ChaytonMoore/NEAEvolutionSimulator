#include <SFML/Graphics.hpp>
#include "Structures.h"
#include "MainUI.h"


//This function will take a font from 
sf::Font GetDefaultFont(DataCarrier* GetFontFrom)
{
    
    sf::Font font;
    if (!font.loadFromFile(FilePath+DefaultFontFileName)) //This concats strings such that the font file is inside the file path
    {
        return nullptr;
    }
    return font;
}




class Button
{
    sf::vector2i BLeft;//Bottom left of the Button
    sf::vector2i TRight;//Top right of the the Button
    bool isPressed = false;
    bool DefaultFunctionality = true;
    int (* fcnPtr)();//The function that is executed when the button is clicked unless the DefaultFunctionality variable is false 
    
    
    
    sf::Text text;

    void InitButton(std::string ButtonText,DataCarrier* FontData)
    {
        // select the font
        text.setFont(GetDefaultFont()); //Need to get the DataCarrier that contains the default font
    
        // set the string to display
        text.setString(ButtonText);
    
        // set the character size
        text.setCharacterSize(12);
    }
    
    //This function is for when I don't want to put a button there.
    void InitButton(DataCarrier* FontData)
    {
                // select the font
        text.setFont(GetDefaultFont()); //Need to get the DataCarrier that contains the default font
    
        // set the string to display
        text.setString("Button");
    
        // set the character size
        text.setCharacterSize(12);
    }


    
    bool isClicked()
    {
        sf::Vector2i MousePosition = sf::Mouse::getPosition();;
        if (MousePosition>BLeft && MousePosition<TRight && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            isPressed = true;
        }
        else
        {
            isPressed = false;
        }
    }
    
    void ButtonTick()
    {
        //This is the code for the button that is executed every tick
        if(DefaultFunctionality&&isClicked())
        {
            fcnPte();
            //Executes the buttons default code
        }
    }
    
};

//Might try to use function pointers for the functions of the buttons



int OpenUIWindow()
{
	sf::RenderWindow window(sf::VideoMode(300, 200), "Evolution Simulator");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}



	return 0;
}
