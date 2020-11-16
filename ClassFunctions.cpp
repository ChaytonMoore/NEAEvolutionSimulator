#include "Creature.h"
#include "Structures.h"
#include "stdlib.h"

//This function is used for creating a new random creature, it takes a seed if I want to use seeds.

//std::vector 

template<typename T>
std::vector<T> AppendVector(std::vector<T> a, std::vector<T> b)
{
	a.insert(std::end(a), std::begin(b), std::end(b));
	return a;
}

Creature* GenerateNewRandom(int seed)
{
	//firstly create the new creature
	Creature* Output = new Creature;


	//Then create the seed
	srand(seed);

	//Use the random numbers to 
	for (size_t i = 0; i < rand() % 3 + 1; i++)
	{
		Output->Nodes.push_back(new Node);
	}

	int ConnectionLimit;
	ConnectionLimit = Output->Nodes.size();
	for (size_t i = 0; i < rand() % ConnectionLimit; i++)
	{
		//For random generation the connections need to be random
		if (rand()%1 == 0)
		{
			Output->Muscles.push_back(new Muscle);
		}
		else
		{
			Output->Bones.push_back(new Bone);
		}
	}

	//Now set the locations of the nodes.

	for (size_t i = 0; i < Output->Nodes.size(); i++)
	{
		//This is used to make sure that the nodes are atleast a small distance from each other
		do
		{
			Output->Nodes[i]->Location = Position(rand() % 40 - 20,rand()% 40 -20);
			//Remember all locations are relative to the location of the creature
			

			//TODO: make sure the nodes don't spawn to near to each other
			break;
		} while (true);
	}

	//Now to use the connections to connect the nodes
	
	std::vector<Connection*> TempConnections;
	TempConnections.insert(std::end(TempConnections), std::begin(Output->Bones), std::end(Output->Bones));
	TempConnections.insert(std::end(TempConnections), std::begin(Output->Muscles), std::end(Output->Muscles));

	int RandomNodeIdx1,RandomNodeIdx2;
	for (size_t i = 0; i < TempConnections.size(); i++)
	{
		do
		{
			//Make sure the random nodes are not the same
			RandomNodeIdx1 = rand() % Output->Nodes.size();
			RandomNodeIdx2 = rand() % Output->Nodes.size();
			if (RandomNodeIdx1!=RandomNodeIdx2)
			{
				break;
			}
		} while (true);
		Output->Nodes[RandomNodeIdx1]->Connections.push_back(TempConnections[i]);
		Output->Nodes[RandomNodeIdx2]->Connections.push_back(TempConnections[i]);

		//This connections nodes together

		//TODO make sure that there are no connections in the same place
	}
	return Output;
}

Creature* CreateChild(Creature* Base,int seed)
{
	//Creates another creature based on a creature, also takes a seed
	Creature* Output = new Creature(*Base);

	srand(seed);
	//Now to randomise a few of the variables.

}
