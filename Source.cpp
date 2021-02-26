#include <SFML/Graphics.hpp>
#include "Structures.h"
#include "Source.h"
#include <iostream>
#include <chrono>
#include <ctime>
//#include "ClassFunctions.cpp" //make sure to use the .h
#include "MainUI.h"
#include "ClassFunctions.h"

const float GenerationTime = 5;


sf::RenderWindow* CreateGameWindow()
{
	sf::RenderWindow window(sf::VideoMode(300, 200), "Evolution Simulator");
	

	/*
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


		

		window.display();
	}
	*/

	return &window;
}




int main()
{
	//First thing to do is create the start menu.
	//This start menu will have no real function unless a few more features are added.

	//FreeConsole();
	OpenUIWindow();
	return 0;
}


