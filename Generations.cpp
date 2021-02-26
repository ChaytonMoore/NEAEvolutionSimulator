#include "Generations.h"
//#include "MainUI.cpp"
const float GenerationTime = 2;

CreatureFitness* InitialGeneration(int Inputseed, int CreaturesInGeneration)
{


	int seed = Inputseed;
	//OpenUIWindow();

	//This is a test sequence

	std::cout << CreaturesInGeneration << std::endl;

	bool SimulationRunning = true;

	std::vector<Creature*> Creatures;
	std::vector<CreaturePositionData> PositionSaveData;
	for (size_t i = 0; i < CreaturesInGeneration; i++)
	{
		Creatures.push_back(GenerateNewRandom2(seed + i));
		PositionSaveData.push_back(*new CreaturePositionData);
		for (size_t j = 0; j < Creatures[i]->Nodes.size(); j++)
		{
			PositionSaveData[i].Data.push_back(Creatures[i]->Nodes[j]->Location);
		}


		Creatures.back()->Offset(25 * i);
	}

	//Creature* test = GenerateNewRandom2(0);
	


	auto t_start = std::chrono::high_resolution_clock::now();
	auto t_end = std::chrono::high_resolution_clock::now();
	double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
	double TotalTime = 0;
	sf::RenderWindow Window(sf::VideoMode(900, 600), "Evolution Simulator");


	std::vector<sf::CircleShape> Circles;
	std::vector<Node*> CircleNodeRef;
	//This variable is used such that required nodes can be easily referenced


	//Circles.push_back(*new sf::CircleShape); Circles.push_back(*new sf::CircleShape);
	//sf::CircleShape N1,N2;

	std::vector<LineData> Lines;
	std::vector<Muscle*> LineMuscleRef;

	for (size_t c = 0; c < Creatures.size(); c++)
	{



		for (size_t i = 0; i < Creatures[c]->Nodes.size(); i++)
		{
			Circles.push_back(*new sf::CircleShape);
			CircleNodeRef.push_back(Creatures[c]->Nodes[i]);
			Circles.back().setRadius(2);
		}



		for (size_t i = 0; i < Creatures[c]->Muscles.size(); i++)
		{
			Lines.push_back(LineData(sf::Vertex(sf::Vector2f(10, 10)), sf::Vertex(sf::Vector2f(150, 150))));
			LineMuscleRef.push_back(Creatures[c]->Muscles[i]);
			Lines.back().LinesD->color = sf::Color::Red;

		}


	}
	sf::Vertex line[] = { sf::Vertex(sf::Vector2f(10, 10)),sf::Vertex(sf::Vector2f(150, 150)) };
	line->color = sf::Color::Red;


	std::cout<<Creatures.size() <<std::endl;
	sf::RectangleShape BackgroundRect;
	BackgroundRect.setSize(sf::Vector2f(900, 600));
	BackgroundRect.setFillColor(sf::Color::Blue);
	std::vector<float> Fitness; //Fitness is measured as the average location of the creature. This might cause problems of creatures getting larger so might add some stuff on it fix it.

	//Creatures will move  keep their positions between generations 
	



	//std::cout << PositionSaveData[1].Data[0].x << "b" << std::endl;
	
	while (Window.isOpen())
	{


		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();
		}


		Window.clear();
		//First thing to draw is the blue background

		for (size_t i = 0; i < Circles.size(); i++)
		{
			Window.draw(Circles[i]);
			//Circles[i].setPosition(test->Nodes[i]->Location.x, test->Nodes[i]->Location.y);
			Circles[i].setPosition(CircleNodeRef[i]->Location.x, CircleNodeRef[i]->Location.y);

		}

		for (size_t i = 0; i < Lines.size(); i++)
		{
			Window.draw(Lines[i].LinesD, 2, sf::Lines);

			//Lines[i].LinesD[0].position = sf::Vector2f(test->Muscles[i]->ends[0]->Location.x, test->Muscles[i]->ends[0]->Location.y) + sf::Vector2f(1, 1);
			//Lines[i].LinesD[1].position = sf::Vector2f(test->Muscles[i]->ends[1]->Location.x, test->Muscles[i]->ends[1]->Location.y) + sf::Vector2f(1, 1);

			Lines[i].LinesD[0].position = sf::Vector2f(LineMuscleRef[i]->ends[0]->Location.x, LineMuscleRef[i]->ends[0]->Location.y) + sf::Vector2f(1, 1);
			Lines[i].LinesD[1].position = sf::Vector2f(LineMuscleRef[i]->ends[1]->Location.x, LineMuscleRef[i]->ends[1]->Location.y) + sf::Vector2f(1, 1);

		}








		//std::cout << test->GetAverageLocation().x << std::endl;

		t_end = std::chrono::high_resolution_clock::now();
		elapsed_time_ms = std::chrono::duration<double>(t_end - t_start).count();
		TotalTime += elapsed_time_ms;

		for (size_t c = 0; c < Creatures.size(); c++)
		{
			Creatures[c]->EventTick(abs(elapsed_time_ms));
		}




		//std::cout << test->Nodes[1]->Location.x <<" "<< test->Nodes[1]->Location.y << std::endl;
		//std::cout << test->Nodes[0]->Location.x << " " << test->Nodes[0]->Location.y << std::endl;
		t_start = std::chrono::high_resolution_clock::now();

		if (fmod(TotalTime, 1) < 0.01)
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


		//std::cout <<"aaaa"<< test->Muscles[0]->StartingDistance << std::endl;

		Window.display();
		//std::cout << TotalTime << std::endl;
		if (TotalTime > GenerationTime)
		{
			Window.close();
			break;

			

			
		}


	}

	//After the generation had been completed it needs to be sorted and repopulated.
	//std::cout << PositionSaveData[1].Data[0].x <<"a"<<std::endl;


	for (size_t i = 0; i < Creatures.size(); i++)
	{
		Fitness.push_back(Creatures[i]->GetAverageLocation().x);
	}

	//Now the positions of the creatures will be set. This might cause a problem with the creature ranking, I'll just have to use the fitness instead of creature data.
	for (size_t i = 0; i < Creatures.size(); i++)
	{
		for (size_t j = 0; j < Creatures[i]->Nodes.size(); j++)
		{
			Creatures[i]->Nodes[j]->Location = PositionSaveData[i].Data[j];
		}
	}

	std::cout << "Fitness size" << Fitness.size() << std::endl;
	
	return new CreatureFitness(Reproduce(Creatures, Fitness, seed),Fitness);
	//return Creatures;
}


CreatureFitness* StandardGeneration(int Inputseed, std::vector<Creature*> Creatures)
{
	


	int CreaturesInGeneration = Creatures.size();
	int seed = Inputseed;
	//OpenUIWindow();

	//This is a test sequence
	std::vector<CreaturePositionData> PositionSaveData;


	for (size_t i = 0; i < Creatures.size(); i++)
	{
		PositionSaveData.push_back(*new CreaturePositionData);


		for (size_t j = 0; j < Creatures[i]->Nodes.size(); j++)
		{
			PositionSaveData[i].Data.push_back(Creatures[i]->Nodes[j]->Location);
		}
	}


	bool SimulationRunning = true;
	for (size_t i = 0; i < CreaturesInGeneration; i++)
	{
		std::cout << "Before CY " << Creatures[i]->GetAverageLocation().y << std::endl;
		Creatures[i]->Offset(25 * i);
		std::cout << "CY " << Creatures[i]->GetAverageLocation().y << std::endl;
		std::cout << "CX " << Creatures[i] << std::endl;
		
	}
	

	//Creature* test = GenerateNewRandom2(0);



	auto t_start = std::chrono::high_resolution_clock::now();
	auto t_end = std::chrono::high_resolution_clock::now();
	double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
	double TotalTime = 0;
	sf::RenderWindow Window(sf::VideoMode(900, 600), "Evolution Simulator");


	std::vector<sf::CircleShape> Circles;
	std::vector<Node*> CircleNodeRef;
	//This variable is used such that required nodes can be easily referenced


	//Circles.push_back(*new sf::CircleShape); Circles.push_back(*new sf::CircleShape);
	//sf::CircleShape N1,N2;

	std::vector<LineData> Lines;
	std::vector<Muscle*> LineMuscleRef;

	for (size_t c = 0; c < Creatures.size(); c++)
	{



		for (size_t i = 0; i < Creatures[c]->Nodes.size(); i++)
		{
			Circles.push_back(*new sf::CircleShape);
			CircleNodeRef.push_back(Creatures[c]->Nodes[i]);
			Circles.back().setRadius(2);
		}



		for (size_t i = 0; i < Creatures[c]->Muscles.size(); i++)
		{
			Lines.push_back(LineData(sf::Vertex(sf::Vector2f(10, 10)), sf::Vertex(sf::Vector2f(150, 150))));
			LineMuscleRef.push_back(Creatures[c]->Muscles[i]);
			Lines.back().LinesD->color = sf::Color::Red;

		}


	}
	sf::Vertex line[] = { sf::Vertex(sf::Vector2f(10, 10)),sf::Vertex(sf::Vector2f(150, 150)) };
	line->color = sf::Color::Red;



	sf::RectangleShape BackgroundRect;
	BackgroundRect.setSize(sf::Vector2f(900, 600));
	BackgroundRect.setFillColor(sf::Color::Blue);
	std::vector<float> Fitness; //Fitness is measured as the average location of the creature. This might cause problems of creatures getting larger so might add some stuff on it fix it.






	while (Window.isOpen())
	{


		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();
		}


		Window.clear();
		//First thing to draw is the blue background

		for (size_t i = 0; i < Circles.size(); i++)
		{
			Window.draw(Circles[i]);
			//Circles[i].setPosition(test->Nodes[i]->Location.x, test->Nodes[i]->Location.y);
			Circles[i].setPosition(CircleNodeRef[i]->Location.x, CircleNodeRef[i]->Location.y);

		}

		for (size_t i = 0; i < Lines.size(); i++)
		{
			Window.draw(Lines[i].LinesD, 2, sf::Lines);

			//Lines[i].LinesD[0].position = sf::Vector2f(test->Muscles[i]->ends[0]->Location.x, test->Muscles[i]->ends[0]->Location.y) + sf::Vector2f(1, 1);
			//Lines[i].LinesD[1].position = sf::Vector2f(test->Muscles[i]->ends[1]->Location.x, test->Muscles[i]->ends[1]->Location.y) + sf::Vector2f(1, 1);

			Lines[i].LinesD[0].position = sf::Vector2f(LineMuscleRef[i]->ends[0]->Location.x, LineMuscleRef[i]->ends[0]->Location.y) + sf::Vector2f(1, 1);
			Lines[i].LinesD[1].position = sf::Vector2f(LineMuscleRef[i]->ends[1]->Location.x, LineMuscleRef[i]->ends[1]->Location.y) + sf::Vector2f(1, 1);
			
		}


		//std::cout << test->GetAverageLocation().x << std::endl;

		t_end = std::chrono::high_resolution_clock::now();
		elapsed_time_ms = std::chrono::duration<double>(t_end - t_start).count();
		TotalTime += elapsed_time_ms;

		for (size_t c = 0; c < Creatures.size(); c++)
		{
			Creatures[c]->EventTick(abs(elapsed_time_ms));
		}




		//std::cout << test->Nodes[1]->Location.x <<" "<< test->Nodes[1]->Location.y << std::endl;
		//std::cout << test->Nodes[0]->Location.x << " " << test->Nodes[0]->Location.y << std::endl;
		t_start = std::chrono::high_resolution_clock::now();

		if (fmod(TotalTime, 1) < 0.01)
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


		//std::cout <<"aaaa"<< test->Muscles[0]->StartingDistance << std::endl;

		Window.display();

		if (TotalTime > GenerationTime)
		{
			Window.close();

			//for (size_t i = 0; i < Creatures.size(); i++)
			//{
				//Fitness.push_back(Creatures[i]->GetAverageLocation().x);
			//}
		}


	}

	//After the generation had been completed it needs to be sorted and repopulated.
	for (size_t i = 0; i < Creatures.size(); i++)
	{
		Fitness.push_back(Creatures[i]->GetAverageLocation().x);
	}
	std::cout << "Fitness size" << Fitness.size() << std::endl;

	for (size_t i = 0; i < Creatures.size(); i++)
	{
		for (size_t j = 0; j < Creatures[i]->Nodes.size(); j++)
		{
			Creatures[i]->Nodes[j]->Location = PositionSaveData[i].Data[j];
		}
	}
	std::cout << "g size" << Creatures.size() << std::endl;
	//Reproduce(Creatures, Fitness, seed);


	return new CreatureFitness(Reproduce(Creatures, Fitness, seed),Fitness);
	
}
