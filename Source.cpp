#include <SFML/Graphics.hpp>
#include "Structures.h"
#include "Source.h"
#include <iostream>
#include <chrono>
#include <ctime>
//#include "ClassFunctions.cpp" //make sure to use the .h
#include "MainUI.h"
#include "ClassFunctions.h"

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
	//OpenUIWindow();

	//This is a test sequence
	Creature* test = GenerateNewRandom(3);
	auto t_start = std::chrono::high_resolution_clock::now();
	auto t_end = std::chrono::high_resolution_clock::now();
	double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
	double TotalTime = 0;
	sf::RenderWindow Window(sf::VideoMode(900, 600), "Evolution Simulator");
	sf::CircleShape N1,N2;
	N1.setRadius(2);
	N2.setRadius(2);
	sf::Vertex line[] ={sf::Vertex(sf::Vector2f(10, 10)),sf::Vertex(sf::Vector2f(150, 150))};
	line->color = sf::Color::Red;


	while (Window.isOpen())
	{
		

		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();
		}


		Window.clear();
		Window.draw(N1);
		Window.draw(N2);
		Window.draw(line, 2, sf::Lines);

		N1.setPosition(test->Nodes[0]->Location.x, test->Nodes[0]->Location.y);
		N2.setPosition(test->Nodes[1]->Location.x, test->Nodes[1]->Location.y);
		line[0].position = N1.getPosition() + sf::Vector2f(1,1);
		line[1].position = N2.getPosition() + sf::Vector2f(1, 1);


		

		//std::cout << test->GetAverageLocation().x << std::endl;
		
		t_end = std::chrono::high_resolution_clock::now();
		elapsed_time_ms = std::chrono::duration<double>(t_end - t_start).count();
		TotalTime += elapsed_time_ms;
		test->EventTick(elapsed_time_ms);
		
		//std::cout << test->Nodes[1]->Location.x <<" "<< test->Nodes[1]->Location.y << std::endl;
		//std::cout << test->Nodes[0]->Location.x << " " << test->Nodes[0]->Location.y << std::endl;
		t_start = std::chrono::high_resolution_clock::now();

		if (fmod(TotalTime,4) < 0.01)
		{
			//std::cout << test->Nodes[0]->Location.x << " " << test->Nodes[0]->Location.y << std::endl;
			//std::cout << test->Nodes[1]->Location.x << " " << test->Nodes[1]->Location.y << std::endl;
			//std::cout << test->Muscles[0]->MuscleOutput << std::endl;

			//std::cout <<" a  "<< test->Nodes[0]->NodeVelocity(test->Nodes[0]).x << test->Nodes[0]->MovementResistance(test->Area, test->Nodes[0]->NodeVelocity(test->Nodes[0])).x<< std::endl;
			std::cout << test->Nodes[1]->LatentVelocity.x << std::endl;

		}


		

		Window.display();
	}
	

	return 0;
}
