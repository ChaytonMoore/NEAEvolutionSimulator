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
		}#include <SFML/Graphics.hpp>
#include "Structures.h"
#include "MainUI.h"
#include <iostream>
#include "SettingWidget.h"
#include "Generations.h"
#include <numeric>
#include <ios>
#include <direct.h>
#include <experimental/filesystem>


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
int NumberofGenerations;
int GenerationSeed;
int NumberofCreatures;

const std::vector<std::string> explode(const std::string& s, const char& c)
{
	std::string buff{ "" };
	std::vector<std::string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}

sf::Text* SetupText(sf::Vector2f Loc, std::string Text, DataCarrier* FontData)
{
	sf::Text* text = new sf::Text();
	text->setPosition(Loc);
	text->setFillColor(sf::Color::Green);
	text->setCharacterSize(12);
	text->setString(Text);
	FontData->StandardFont = GetDefaultFont(FontData);
	text->setFont(FontData->StandardFont); //Need to get the DataCarrier that contains the default font

	return text;

}

sf::Text* SetupText(sf::Vector2f Loc, int size, std::string Text, DataCarrier* FontData ,sf::Color colour)
{
	sf::Text* text = new sf::Text();
	text->setPosition(Loc);
	text->setFillColor(colour);
	text->setCharacterSize(size);
	text->setString(Text);
	FontData->StandardFont = GetDefaultFont(FontData);
	text->setFont(FontData->StandardFont); //Need to get the DataCarrier that contains the default font


	return text;
}

int BeginNextGen(sf::RenderWindow* Oldwindow)
{
	Oldwindow->close();


	return 1;
}


char* ReverseBytes(const char* a,int size)
{
	int s = size - 1;
	char* output = new char[size];
	
	std::cout << a << std::endl;


	for (size_t i = 0; i < size; i++)
	{
		output[i] = a[s-i];
	}
	std::cout << output << std::endl;

	return output;
}


int SaveAndExit(sf::RenderWindow* Oldwindow, std::vector<Creature*> creatures)
{
	//I'm trying a new way of storing data


	//Here is the code that will save the creatures.
	//std::cout << "r";
	//test stuff first
	std::string SaveName;
	int tmp1;
	int tmp2;

	int Temp; //Quite a few temp variables are needed
	int NodeT;

	namespace fsA = std::experimental::filesystem;
	


	std::string SavePath;
	if(std::experimental::filesystem::exists("LocalSavePath.txt"))
	{
		
			std::ifstream fin("LocalSavePath.txt", std::ios::in);
			fin >> SavePath;
			SavePath = SavePath;
			fin.close();
	}
	else
	{
		SavePath = "Saves";
	}
	fsA::create_directories("./"+SavePath);

	std::ofstream f(SavePath+"/Save.txt", std::ios::out | std::ios::binary);
	f.clear();
	for (size_t i = 0; i < creatures.size(); i++)
	{
		f << std::to_string(i+1);
		if (i+1 < creatures.size())
		{
			f << ",";
		}
	}



	f.close();


	for (size_t i = 0; i < creatures.size(); i++)
	{

	


		SaveName = SavePath+"/"  +std::to_string(i+1) +".CSD";
		std::ofstream f(SaveName);
		f.clear();

		//First thing to do is store the number of muscles
		Temp = creatures[i]->Muscles.size();
		f.write(reinterpret_cast<const char*>(&Temp), sizeof(Temp));
		std::cout << creatures[i]->Muscles.size() << " " <<  std::endl;


		/*
		for (size_t j = 0; j < creatures[i]->Muscles.size(); j++)
		{



			//Find place of the ends values
			tmp1 = std::distance(creatures[i]->Nodes.begin(),std::find(creatures[i]->Nodes.begin(), creatures[i]->Nodes.end(), creatures[i]->Muscles[j]->ends[0]));
			tmp2 = std::distance(creatures[i]->Nodes.begin(), std::find(creatures[i]->Nodes.begin(), creatures[i]->Nodes.end(), creatures[i]->Muscles[j]->ends[1]));

			f.write(reinterpret_cast<const char*>((&creatures[i]->Muscles[j]->Frequency)), sizeof(float)); // frequency
			f.write(reinterpret_cast<const char*>((&creatures[i]->Muscles[j]->Strength)), sizeof(float)); // strength
			f.write(reinterpret_cast<const char*>((&tmp1)), sizeof(int)); // ends 0
			f.write(reinterpret_cast<const char*>((&tmp2)), sizeof(int)); // ends 1
			f.write(reinterpret_cast<const char*>((&creatures[i]->Muscles[j]->Biases)), sizeof(float[4]));
		}
		//Now to write all the data regarding the nodes

		NodeT = creatures[i]->Nodes.size();
		f.write(reinterpret_cast<const char*>(&NodeT), sizeof(int));
		for (size_t j = 0; j < creatures[i]->Nodes.size(); j++)
		{

			//Temp = creatures[i]->Nodes[j]->Connections.size();
			//f.write(reinterpret_cast<const char*>(&Temp), sizeof(int)); // size of Connection places 
			


			

			//for (size_t n = 0; n < creatures[i]->Nodes[j]->Connections.size(); n++)
			//{
				


				//f.write(reinterpret_cast<const char*>((std::distance(creatures[i]->Muscles.begin(), std::find(creatures[i]->Muscles.begin(), creatures[i]->Muscles.end(), (Muscle*)creatures[i]->Nodes[j]->Connections[n])))), sizeof(int)); //connection elements
			//}

			//^ I don't actually think the connection variable is used anymore
			f.write(reinterpret_cast<const char*>((&creatures[i]->Nodes[j]->Weight)), sizeof(float));
			f.write(reinterpret_cast<const char*>((&creatures[i]->Nodes[j]->Location)), sizeof(Position));


		}

		*/

		f.close();
	}
	
	
	//f.write(reinterpret_cast<const char*>((&NumberofCreatures)), sizeof(creatures.size()));
	//std::cout << sizeof(*(creatures[0]))<< std::endl;
	
	
	
	//for (size_t i = 0; i < creatures.size(); i++)
	//{
		
		//f.write((char*)(creatures[i]), sizeof(*creatures[i]));
	//}
	

	



	exit(0);
	return 1;
}

void AfterGenStats(std::vector<float> Fitness,std::vector<Creature*> Creatures)
{
	DataCarrier MainDataCarrier;
	MainDataCarrier.DefaultFontFileName = "//Data/Bebas-Regular.ttf";



	sf::RenderWindow window(sf::VideoMode(600, 600), "Evolution Simulator Stats", sf::Style::Titlebar | sf::Style::Close);
	
	//find stats
	float longest;
	float shortest;
	float mean;
	float median;
	

	std::vector<float> Sorted;

	float value;
	int index;
	std::sort(Fitness.begin(), Fitness.end());
	

	longest = Fitness.back();
	shortest = Fitness[0];
	mean = std::accumulate(Fitness.begin(), Fitness.end(), 0)/Fitness.size();
	median = Fitness[int(Fitness.size()/2)];


	//End of find stats

	sf::Text* TitleBest = SetupText(sf::Vector2f(10, 10), "Best", &MainDataCarrier);
	sf::Text* Best = SetupText(sf::Vector2f(10, 20), std::to_string(longest).std::string::substr(0, 2), &MainDataCarrier);

	sf::Text* TitleMean = SetupText(sf::Vector2f(10, 40), "Mean", &MainDataCarrier);
	sf::Text* MeanText = SetupText(sf::Vector2f(10, 50), std::to_string(mean).std::string::substr(0, 2), &MainDataCarrier);

	sf::Text* TitleMedian = SetupText(sf::Vector2f(10, 70), "Median", &MainDataCarrier);
	sf::Text* MediaText = SetupText(sf::Vector2f(10, 80), std::to_string(median).std::string::substr(0, 2), &MainDataCarrier);


	Button NextGen = Button("Continue", &MainDataCarrier, sf::Vector2f(310, 290), sf::Vector2f(80, 20));
	NextGen.DefaultFunctionality = true;
	NextGen.fcnPtr = BeginNextGen;

	Button SaveExit = Button("Save and Exit", &MainDataCarrier, sf::Vector2f(310, 320), sf::Vector2f(80, 20));


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(*TitleBest);
		window.draw(*Best);

		window.draw(*TitleMean);
		window.draw(*MeanText);

		window.draw(*TitleMedian);
		window.draw(*MediaText);


		window.draw(NextGen.shape);
		window.draw(NextGen.text);
		NextGen.ButtonTick(&window);

		window.draw(SaveExit.shape);
		window.draw(SaveExit.text);
		SaveExit.ButtonTick(&window);
		
		std::cout << SaveExit.MouseInButton(&window) << std::endl;
		if (SaveExit.MouseInButton(&window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//Execute the function to save and exit
			std::cout << "run";
			SaveAndExit(&window,Creatures);
		}

		window.display();
	}
}

int EndScreen()
{
	DataCarrier MainDataCarrier;
	MainDataCarrier.DefaultFontFileName = "//Data/Bebas-Regular.ttf";



	sf::RenderWindow window(sf::VideoMode(600, 600), "Evolution Simulator End", sf::Style::Titlebar | sf::Style::Close);


	sf::Text* EndText = SetupText(sf::Vector2f(10, 10), "Simulation Complete", &MainDataCarrier);
	Button NextGen = Button("Continue", &MainDataCarrier, sf::Vector2f(310, 290), sf::Vector2f(80, 20));
	NextGen.DefaultFunctionality = true;
	NextGen.fcnPtr = BeginNextGen;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		window.draw(*EndText);
		window.draw(NextGen.shape);
		window.draw(NextGen.text);
		NextGen.ButtonTick(&window);


		window.display();
	}
	return 1;
}


int BeginSimulation(sf::RenderWindow* Oldwindow)
{
	Oldwindow->close();

	//std::vector<Creature*> Creatures;
	CreatureFitness* CreatureData;

	CreatureData = InitialGeneration(GenerationSeed,NumberofCreatures);
	
	AfterGenStats(CreatureData->Fitnesses, CreatureData->Creatures);
	for (size_t i = 0; i < NumberofGenerations-1; i++)
	{
		CreatureData = StandardGeneration(GenerationSeed+i,CreatureData->Creatures);
		//std::cout << Creatures.size() <<"number of creatures"<<std::endl;
		AfterGenStats(CreatureData->Fitnesses, CreatureData->Creatures);
		
		//Remember reproduction does occur before the creatures are displayed so that might be a problem
	}
	EndScreen();
	//Now to show the end screen
	

	return 1;
}

int ContinueSimulation(sf::RenderWindow* Oldwindow)
{
	Oldwindow->close();

	//std::vector<Creature*> Creatures;
	CreatureFitness* CreatureData = new CreatureFitness(*(new std::vector<Creature*>),*(new std::vector<float>));


	//First make sure the filepath can be obtained
	std::string SavePath;
	if (std::experimental::filesystem::exists("LocalSavePath.txt"))
	{

		std::ifstream fin("LocalSavePath.txt", std::ios::in);
		fin >> SavePath;
		SavePath = SavePath;
		fin.close();
	}
	else
	{
		SavePath = "Saves";
	}
	
	SavePath = SavePath + "/Save.txt";

	//Now open the file
	std::ifstream inputData((SavePath), std::ios::in);
	//This file contains the names of the files to open
	std::string FileNames;
	
	std::getline(inputData,FileNames);


	//Then a good idea would be to split the data
	std::vector<std::string> FileNameData = explode(FileNames,*",") ;
	NumberofCreatures = FileNameData.size();

	//Now the code has to go through every create an re create it from the file data

	//A lot of various temp values are going to be needed.
	int MuscleNumber;
	float Freq;
	float Stre;
	int ends1;
	int ends2;
	float biases[4];
	int NodeNumber;
	float weight;
	Position TempLocation = Position(0,0);

	//test
	





	for (size_t i = 0; i < FileNameData.size(); i++)
	{
		//first thing to do is create the creature.
		CreatureData->Creatures.push_back(new Creature);


		//Right now open the file
		std::ifstream f((FileNameData[i]+".CSD"), std::ios::in | std::ios::binary);
		
		char ex[4];
		//f.read(reinterpret_cast<char*>(&MuscleNumber), sizeof(int));
		f.read(reinterpret_cast<char*>(&MuscleNumber), sizeof(int));
		std::cout << MuscleNumber<<"a"<< std::endl;
		std::cout << FileNameData[i] + ".CSD" << std::endl;
		/*
		for (size_t n = 0; n < MuscleNumber; n++)
		{
			//firstly a mew muscle needs to be created.
			CreatureData->Creatures.back()->Muscles.push_back(new Muscle);
			
			//Now the data regarding information about the muscle should be stored.
			//CreatureData->Creatures.back()->Muscles.back()
			f.read(reinterpret_cast<char*>(&Freq), sizeof(float));
			f.read(reinterpret_cast<char*>(&Stre), sizeof(float));
			f.read(reinterpret_cast<char*>(&ends1), sizeof(int));
			f.read(reinterpret_cast<char*>(&ends2), sizeof(int));
			f.read(reinterpret_cast<char*>(&biases), sizeof(float[4]));

			CreatureData->Creatures.back()->Muscles.back()->Frequency = Freq;
			CreatureData->Creatures.back()->Muscles.back()->Strength = Stre;
			CreatureData->Creatures.back()->Muscles.back()->Biases[0] = biases[0];
			CreatureData->Creatures.back()->Muscles.back()->Biases[1] = biases[1];
			CreatureData->Creatures.back()->Muscles.back()->Biases[2] = biases[2];
			CreatureData->Creatures.back()->Muscles.back()->Biases[3] = biases[3];

			

		}

		//Now to create all the nodes
		f.read(reinterpret_cast<char*>(&NodeNumber), sizeof(int));
		
		for (size_t n = 0; n < NodeNumber; n++)
		{
			std::cout << "n" << n << " " << i << std::endl;
			CreatureData->Creatures.back()->Nodes.push_back(new Node);

			f.read(reinterpret_cast<char*>(&weight), sizeof(float));
			f.read(reinterpret_cast<char*>(&TempLocation), sizeof(Position));
			CreatureData->Creatures.back()->Nodes.back()->Weight = weight;
			CreatureData->Creatures.back()->Nodes.back()->Location = TempLocation;

		}

		for (size_t n = 0; n < CreatureData->Creatures.back()->Muscles.size(); n++)
		{
			CreatureData->Creatures.back()->Muscles[n]->ends[0] = CreatureData->Creatures.back()->Nodes[ends1];
			CreatureData->Creatures.back()->Muscles[n]->ends[1] = CreatureData->Creatures.back()->Nodes[ends2];
		}
		*/
		f.close();

	}
	

	for (size_t i = 0; i < NumberofGenerations - 1; i++)
	{
		CreatureData = StandardGeneration(GenerationSeed + i, CreatureData->Creatures);
		//std::cout << Creatures.size() <<"number of creatures"<<std::endl;
		AfterGenStats(CreatureData->Fitnesses, CreatureData->Creatures);

		//Remember reproduction does occur before the creatures are displayed so that might be a problem
	}
	EndScreen();
	//Now to show the end screen
	

	return 1;
}

//Might try to use function pointers for the functions of the buttons

int StartSimSetup(sf::RenderWindow* Oldwindow)
{
	NumberofGenerations = 5; //There can't be less than 2 generations.
	Oldwindow->close();


	DataCarrier MainDataCarrier;
	MainDataCarrier.DefaultFontFileName = "//Data/Bebas-Regular.ttf";



	sf::RenderWindow window(sf::VideoMode(900, 600), "Evolution Simulator", sf::Style::Titlebar | sf::Style::Close);


	SettingWidget CreatureNum = SettingWidget(8, sf::Vector2i(50,50), 1,18, 2, &MainDataCarrier,1,"Number of Creatures");
	SettingWidget IterationNum = SettingWidget(8, sf::Vector2i(50, 100), 1, 12, 2, &MainDataCarrier, 1, "Number of Generations");



	Button StartButton = Button("Start Simulation", &MainDataCarrier, sf::Vector2f(410,550), sf::Vector2f(80, 20));
	StartButton.DefaultFunctionality = true;
	StartButton.fcnPtr = BeginSimulation;



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		

		CreatureNum.Render(&window);
		IterationNum.Render(&window);

		NumberofCreatures = CreatureNum.Value;
		NumberofGenerations = IterationNum.Value;
		//std::cout << CreatureNum.Decrement->MouseInButton(&window) << std::endl;
		if (CreatureNum.Decrement->isClicked(&window)&&CreatureNum.Value>CreatureNum.Lower)//&&CreatureNum.Value>CreatureNum.Lower)
		{
			CreatureNum.Value -= CreatureNum.Change;
			std::cout << "-" << std::endl;
		}

		if (CreatureNum.Increment->isClicked(&window) && CreatureNum.Value < CreatureNum.Upper) //&& CreatureNum.Value < CreatureNum.Upper)
		{
			CreatureNum.Value += CreatureNum.Change;
			std::cout << "+" <<std::endl;
		}


		if (IterationNum.Decrement->isClicked(&window) && IterationNum.Value > IterationNum.Lower)//&&CreatureNum.Value>CreatureNum.Lower)
		{
			IterationNum.Value -= IterationNum.Change;
			std::cout << "-" << std::endl;
		}

		if (IterationNum.Increment->isClicked(&window) && IterationNum.Value < IterationNum.Upper) //&& CreatureNum.Value < CreatureNum.Upper)
		{
			IterationNum.Value += IterationNum.Change;
			std::cout << "+" << std::endl;
		}

		window.draw(StartButton.shape);
		window.draw(StartButton.text);
		StartButton.ButtonTick(&window);

		window.display();
	}



	return 1;
}


int LoadSimSetup(sf::RenderWindow* Oldwindow)
{
	NumberofGenerations = 5; //There can't be less than 2 generations.
	Oldwindow->close();


	DataCarrier MainDataCarrier;
	MainDataCarrier.DefaultFontFileName = "//Data/Bebas-Regular.ttf";



	sf::RenderWindow window(sf::VideoMode(900, 600), "Evolution Simulator", sf::Style::Titlebar | sf::Style::Close);


	//SettingWidget CreatureNum = SettingWidget(8, sf::Vector2i(50, 50), 1, 18, 2, &MainDataCarrier, 1, "Number of Creatures");
	SettingWidget IterationNum = SettingWidget(8, sf::Vector2i(50, 100), 1, 12, 2, &MainDataCarrier, 1, "Number of Generations");



	Button StartButton = Button("Continue Simulation", &MainDataCarrier, sf::Vector2f(410, 550), sf::Vector2f(80, 20));
	StartButton.DefaultFunctionality = true;
	StartButton.fcnPtr = ContinueSimulation;



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();


		//CreatureNum.Render(&window);
		IterationNum.Render(&window);

		//NumberofCreatures = CreatureNum.Value;
		NumberofGenerations = IterationNum.Value;
		//std::cout << CreatureNum.Decrement->MouseInButton(&window) << std::endl;
		//if (CreatureNum.Decrement->isClicked(&window) && CreatureNum.Value > CreatureNum.Lower)//&&CreatureNum.Value>CreatureNum.Lower)
		//{
			//CreatureNum.Value -= CreatureNum.Change;
			//std::cout << "-" << std::endl;
		//}

		//if (CreatureNum.Increment->isClicked(&window) && CreatureNum.Value < CreatureNum.Upper) //&& CreatureNum.Value < CreatureNum.Upper)
		//{
			//CreatureNum.Value += CreatureNum.Change;
			//std::cout << "+" << std::endl;
		//}


		if (IterationNum.Decrement->isClicked(&window) && IterationNum.Value > IterationNum.Lower)//&&CreatureNum.Value>CreatureNum.Lower)
		{
			IterationNum.Value -= IterationNum.Change;
			std::cout << "-" << std::endl;
		}

		if (IterationNum.Increment->isClicked(&window) && IterationNum.Value < IterationNum.Upper) //&& CreatureNum.Value < CreatureNum.Upper)
		{
			IterationNum.Value += IterationNum.Change;
			std::cout << "+" << std::endl;
		}

		window.draw(StartButton.shape);
		window.draw(StartButton.text);
		StartButton.ButtonTick(&window);

		window.display();
	}



	return 1;
}


int Exit(sf::RenderWindow* Oldwindow)
{
	Oldwindow->close();
	return 1;
}

int OpenUIWindow()
{
	sf::RenderWindow window(sf::VideoMode(300, 200), "Evolution Simulator", sf::Style::Titlebar | sf::Style::Close);
	sf::RectangleShape shape(sf::Vector2f(100, 50));
	shape.setFillColor(sf::Color::Green);

	DataCarrier MainDataCarrier;
	MainDataCarrier.DefaultFontFileName = "//Data/Bebas-Regular.ttf";


	std::vector<Button*> Buttons;
	Buttons.push_back(new Button("Start",&MainDataCarrier, sf::Vector2f(50,10), sf::Vector2f(60, 10)));
	Buttons[0]->fcnPtr = StartSimSetup;
	Buttons[0]->DefaultFunctionality = true;



	Buttons.push_back(new Button("Exit", &MainDataCarrier, sf::Vector2f(50, 70), sf::Vector2f(60, 10)));
	Buttons[1]->fcnPtr = Exit;
	Buttons[1]->DefaultFunctionality = true;


	std::string SavePath;
	if (std::experimental::filesystem::exists("LocalSavePath.txt"))
	{

		std::ifstream fin("LocalSavePath.txt", std::ios::in);
		fin >> SavePath;
		SavePath = SavePath;
		fin.close();
	}
	else
	{
		SavePath = "Saves";
	}

	if (std::experimental::filesystem::exists(SavePath+"/Save.txt"))
	{
		
		Buttons.push_back(new Button("Load", &MainDataCarrier, sf::Vector2f(50, 40), sf::Vector2f(60, 10)));
		Buttons[2]->fcnPtr = LoadSimSetup;
		Buttons[2]->DefaultFunctionality = true;
	}



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
			Buttons[i]->ButtonTick(&window);

		}




		window.display();

		
		//std::cout << window.getPosition().x << std::endl;
	}
	

	return 0;
}


		window.display();
	}



	return 0;
}
