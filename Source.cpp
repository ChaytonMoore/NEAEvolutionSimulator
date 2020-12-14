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
	std::vector<sf::CircleShape> Circles;
	//Circles.push_back(*new sf::CircleShape); Circles.push_back(*new sf::CircleShape);
	//sf::CircleShape N1,N2;

	for (size_t i = 0; i < test->Nodes.size(); i++)
	{
		Circles.push_back(*new sf::CircleShape);
		Circles.back().setRadius(2);
	}

	
	std::vector<LineData> Lines;

	for (size_t i = 0; i < test->Muscles.size(); i++)
	{
		Lines.push_back(LineData(sf::Vertex(sf::Vector2f(10, 10)), sf::Vertex(sf::Vector2f(150, 150))));
		Lines.back().LinesD->color = sf::Color::Red;
		
	}

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
		for (size_t i = 0; i < Circles.size(); i++)
		{
			Window.draw(Circles[i]);
			Circles[i].setPosition(test->Nodes[i]->Location.x, test->Nodes[i]->Location.y);
			
		}
		
		for (size_t i = 0; i < Lines.size(); i++)
		{
			Window.draw(Lines[i].LinesD, 2, sf::Lines);
			
			Lines[i].LinesD[0].position = sf::Vector2f(test->Muscles[i]->ends[0]->Location.x, test->Muscles[i]->ends[0]->Location.y) + sf::Vector2f(1, 1);
			Lines[i].LinesD[1].position = sf::Vector2f(test->Muscles[i]->ends[1]->Location.x, test->Muscles[i]->ends[1]->Location.y) + sf::Vector2f(1, 1);
			
		}
		


		


		

		//std::cout << test->GetAverageLocation().x << std::endl;
		
		t_end = std::chrono::high_resolution_clock::now();
		elapsed_time_ms = std::chrono::duration<double>(t_end - t_start).count();
		TotalTime += elapsed_time_ms;
		test->EventTick(abs(elapsed_time_ms));
	
		//std::cout << test->Nodes[1]->Location.x <<" "<< test->Nodes[1]->Location.y << std::endl;
		//std::cout << test->Nodes[0]->Location.x << " " << test->Nodes[0]->Location.y << std::endl;
		t_start = std::chrono::high_resolution_clock::now();

		if (fmod(TotalTime,1) < 0.01)
		{
			//std::cout <<"right"<< test->Nodes[0]->Location.x << " " << test->Nodes[0]->Location.y << std::endl;
			//std::cout <<"left"<< test->Nodes[1]->Location.x << " " << test->Nodes[1]->Location.y << std::endl;
			//std::cout << test->Muscles[0]->MuscleOutput << std::endl;

			//std::cout <<" a  "<< test->Nodes[0]->NodeVelocity(test->Nodes[0]).x << test->Nodes[0]->MovementResistance(test->Area, test->Nodes[0]->NodeVelocity(test->Nodes[0])).x<< std::endl;
			//std::cout << test->Nodes[1]->LatentVelocity.x << std::endl;
			
			//std::cout << test->Muscles[0]->ends[1]->LatentVelocity.x << std::endl;
			//std::cout << test->Muscles[0]->ends[0]->LatentVelocity.x << std::endl;
			

			
			//std::cout << test->Muscles[0]->MovingIn << std::endl;
			//std::cout << test->Muscles[0]->MovementProgress << std::endl;
			
		}


		

		Window.display();
	}
	

	return 0;
}

