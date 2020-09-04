#include <SFML/Graphics.hpp>
#include "Structures.h"
#include "Render.h"
#include <iostream>


std::string FileLocate(std::string Local)
{

	return "C:/Users/User/Documents/NEADataFolder/" + Local;
}

int main()
{
	sf::Texture texture;
	if (!texture.loadFromFile(FileLocate("test.png")))
	{
		std::cout << FileLocate("test.png") << std::endl;
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(10.f, 50.f)); // absolute position
	sprite.move(sf::Vector2f(5.f, 10.f)); // offset relative to the current position
	OpenWindow(1000, 1000);

}


int RenderThing()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
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
