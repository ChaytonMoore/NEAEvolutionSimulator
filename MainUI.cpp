#include <SFML/Graphics.hpp>
#include "Structures.h"
#include "MainUI.h"


//This function will take a font from 
/*


bool operator>(const sf::Vector2i& a, const sf::Vector2i& b)
{
	return a.x > b.x && a.y > b.y;
}

bool operator<(const sf::Vector2i& a, const sf::Vector2i& b)
{
	return a.x < b.x && a.y < b.y;
}
*/



//Might try to use function pointers for the functions of the buttons



int OpenUIWindow()
{
	sf::RenderWindow window(sf::VideoMode(300, 200), "Evolution Simulator");
	sf::RectangleShape shape(sf::Vector2f(100, 50));
	shape.setFillColor(sf::Color::Green);

	DataCarrier MainDataCarrier;
	MainDataCarrier.DefaultFontFileName = "//Bebas-Regular.ttf";


	std::vector<Button*> Buttons;
	Buttons.push_back(new Button("abc",&MainDataCarrier, sf::Vector2f(10,10), sf::Vector2f(60, 10)));
	



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//window.draw(shape);
		

		//render all of the buttons
		for (size_t i = 0; i < Buttons.size(); i++)
		{
			window.draw(Buttons[i]->shape);
			window.draw(Buttons[i]->text);
			Buttons[i]->ButtonTick();
		}

		window.display();
	}



	return 0;
}
