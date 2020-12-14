#include "ClassFunctions.h"


//Might be a lot better if I don't use classes for muscles and Bones
//Or maybe just make muscle and bone be the same class with a different parameters

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
		if (rand() % 1 == 0)
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
			Output->Nodes[i]->Location = Position(rand() % 40 , rand() % 40 );
			//Remember all locations are relative to the location of the creature


			//TODO: make sure the nodes don't spawn to near to each other
			break;
		} while (true);
	}

	//Now to use the connections to connect the nodes

	//Definitly maybe remove this code
	std::vector<Connection*> TempConnections;
	TempConnections.insert(std::end(TempConnections), std::begin(Output->Bones), std::end(Output->Bones));
	TempConnections.insert(std::end(TempConnections), std::begin(Output->Muscles), std::end(Output->Muscles));

	int RandomNodeIdx1, RandomNodeIdx2;
	for (size_t i = 0; i < TempConnections.size(); i++)
	{
		do
		{
			//Make sure the random nodes are not the same
			RandomNodeIdx1 = rand() % Output->Nodes.size();
			RandomNodeIdx2 = rand() % Output->Nodes.size();
			if (RandomNodeIdx1 != RandomNodeIdx2)
			{
				break;
			}
		} while (true);
		Output->Nodes[RandomNodeIdx1]->Connections.push_back(TempConnections[i]);
		Output->Nodes[RandomNodeIdx2]->Connections.push_back(TempConnections[i]);

		//This connections nodes together

		//TODO make sure that there are no connections in the same place
	}

	int TempTimes;
	for (size_t i = 0; i < Output->Muscles.size(); i++)
	{
		TempTimes = 0;
		do
		{
			TempTimes++;
			Output->Muscles[i]->ends[0] = Output->Nodes[rand() % Output->Nodes.size()];
			Output->Muscles[i]->ends[1] = Output->Nodes[rand() % Output->Nodes.size()];
			
		} while (Output->Muscles[i]->ends[0] == Output->Muscles[i]->ends[1] && TempTimes < 25);
		
		Output->Muscles[i]->Location = Position((Output->Muscles[i]->ends[0]->Location.x + Output->Muscles[i]->ends[1]->Location.x)/2, (Output->Muscles[i]->ends[0]->Location.y + Output->Muscles[i]->ends[1]->Location.y) / 2);
		Output->Muscles[i]->StartingDistance = Output->Muscles[i]->ends[0]->Location.DistanceTo(Output->Muscles[i]->ends[1]->Location);
		Output->Muscles[i]->MovementProgress = 1;
	}


	
	return Output;
}

Creature* CreateChild(Creature* Base, int seed)
{
	//Creates another creature based on a creature, also takes a seed
	Creature* Output = new Creature(*Base);

	srand(seed);
	//Now to randomise a few of the variables.

	//The number of nodes can be increased or decreased at random by 1
	if (rand() % 32 == 0)
	{
		//The chance that a node is either added or removed
		if (rand() % 1 == 0)
		{
			Output->Nodes.push_back(new Node);
			//Add new Node
		}
		else
		{
			Output->Nodes.pop_back();
		}
	}
	int RandomNode;
	for (size_t i = 0; i < Output->Nodes.size(); i++)
	{
		//firstly check to see if any node has no connections
		if (Output->Nodes[i]->Connections.size() == 0)
		{
			//For all nodes that are found to be lacking a connection one will be generated to a random node.
			//Randomise whether it will be a muscle or a bone
			if (rand() % 1 == 0)
			{
				Output->Nodes[i]->Connections.push_back(new Muscle);
				Output->Muscles.push_back((Muscle*)(Output->Nodes[i]->Connections[0]));
				//Also needs to be added to the bones or muscles list
			}
			else
			{
				Output->Nodes[i]->Connections.push_back(new Bone);
				Output->Bones.push_back((Bone*)Output->Nodes[i]->Connections[0]);
			}
			//Now to connect it to a random Node, can't be itself
			do
			{
				RandomNode = rand() % Output->Nodes.size();

			} while (RandomNode != i);
				//Now add the connection to that Nodes
				Output->Nodes[RandomNode]->Connections.push_back(Output->Nodes[i]->Connections[0]);
		}

	}

	//Now the probability that the a bone will change to a muscle and a muscle to a bone

	for (int i = 0; i < Output->Muscles.size(); i++)
	{
		if (rand() % 25 == 0)//of course all these random numbers might be changed
		{
			//Generate the replacement
			Output->Bones.push_back(new Bone);
			for (int j = 0; j < Output->Nodes.size(); j++)
			{
				
				//if (Output->Nodes[j]->Connections.Contains(Output->Muscles[i]))
				if(TContains(Output->Muscles[i], Output->Nodes[j]->Connections))
				{
					//Output->Nodes[j]->Connections[Output->Nodes[j]->Connections.find(Output->Muscles[i])] = Output->Bones[Output->Bones.size()];
					Output->Nodes[j]->Connections[TFindElem((Connection*)Output->Muscles[i], Output->Nodes[j]->Connections)] = Output->Bones[Output->Bones.size()];
					
						//That's a long and confusing line, it replaces references

				}
			}
			Output->Muscles.erase(Output->Muscles.begin()+i);

		}
	}

	for (int i = 0; i < Output->Bones.size(); i++)
	{
		//This is just copy and paste code from the muscle replacement
		if (rand() % 25 == 0)
		{

			//Generate the replacement
			Output->Muscles.push_back(new Muscle);
			for (int j = 0; j < Output->Nodes.size(); j++)
			{
				//if (Output->Nodes[j]->Connections.Contains(Output->Bones[i]), Output->Nodes[j]->Connections)
				if (TContains(Output->Bones[i], Output->Nodes[j]->Connections))
				{
					//Output->Nodes[j]->Connections[Output->Nodes[j].Connections.find(Output->Bones[i])] = Output->Muscles[Output.Muscles.size()];
					Output->Nodes[j]->Connections[TFindElem((Connection*)Output->Bones[i], Output->Nodes[j]->Connections)] = Output->Bones[Output->Muscles.size()];
						//That's a long and confusing line, it replaces references

				}
			}
			Output->Bones.erase(Output->Bones.begin()+i);
		}


	}

	//Now to modify some of the values for the muscles, all bones are the same.
	for (int i = 0; i < Output->Muscles.size(); i++)
	{
		if (rand() % 20 == 0)
		{
			//Change the strength of the Muscles
			if (rand() % 1 == 0)
			{
				Output->Muscles[i]->Strength = Output->Muscles[i]->Strength * 1.01;
			}
			else
			{
				Output->Muscles[i]->Strength = Output->Muscles[i]->Strength * 0.99;
			}
		}

		if (rand() % 25 == 0)
		{
			if (rand() % 1 == 0)
			{
				Output->Muscles[i]->Frequency = Output->Muscles[i]->Frequency * 1.01;
			}
			else
			{
				Output->Muscles[i]->Frequency = Output->Muscles[i]->Frequency * 0.99;
			}
		}
	}

	//Also want to modify the locations of the Nodes
	for (int i = 0; i < Output->Nodes.size(); i++)
	{
		if (rand() % 25 == 0)
		{
			Output->Nodes[i]->Location.x += rand() % 4 - 2;
			Output->Nodes[i]->Location.y += rand() % 4 - 2;
		}
	}

	return Output;
}

std::vector<Creature*> Reproduce(std::vector<Creature*> StartCreatures, std::vector<float> Fitness, int seed)
{
	//The two lists need to be the same length
	//Firstly need to order then according to fitness, use a pretty normal sorting algorithm list will only be a max 100 long
	std::vector<Creature*> SortedCreatures;
	float value;
	int index;
	for (int i = 0; i < Fitness.size(); i++)
	{
		value = Fitness[i];
		index = 0;
		for (int j = 0; j < Fitness.size(); j++)
		{
			if (Fitness[j] > Fitness[i])
			{
				value = Fitness[j];
				index = j;
			}
		}
		Fitness.erase(Fitness.begin()+i);
		SortedCreatures.push_back(StartCreatures[i]);
		StartCreatures.erase(StartCreatures.begin()+i);

	}

	//Now the half of the list with lower fitness
	for (int i = 0; i < SortedCreatures.size() / 2; i++)
	{
		SortedCreatures.pop_back();
	}


	for (int i = 0; i < SortedCreatures.size(); i++)
	{
		SortedCreatures.push_back(CreateChild(SortedCreatures[i], seed));
		seed++;
		//Increment the seed so that the new creatures don't all have the same mutations
	}

	return SortedCreatures;

}


//This function is elsewhere
/*
Position NodeVelocity(Node* InputNode,Creature* NodeOwner)
{
	//Firstly get all the Muscles and their forces
	//This is at school can't remeber where the stuff is will assume I've got a list of forces and a list of relative normalised positions


	std::vector<float> MuscleForces;
	std::vector<Position> RelativePositions; //These lists need to be the same length these positions must also be normalised
	for (size_t i = 0; i < InputNode->Connections.size(); i++)
	{
		if ((Muscle*)(InputNode->Connections[i]))
		{
			MuscleForces.push_back(((Muscle*)(InputNode->Connections[i]))->Strength);
			RelativePositions.push_back(Position::NormaliseVector(InputNode->Location - ((Muscle*)(InputNode->Connections[i]))->Location));
			//^ this line is a little too long to be nice
		}
	} 


	
	Position TotalForceDirection = Position(0, 0);
	for (int i = 0; i < MuscleForces.size(); i++)
	{
		TotalForceDirection += RelativePositions[i] * MuscleForces[i];
	}

	//Now the that the force is known the mass(weight) must be used to divide it to get the velocity;
	TotalForceDirection += InputNode->MovementResistance(NodeOwner->Area, TotalForceDirection); //(TotalForceDirection + Node::MovementResistance(NodeOwner->Area, TotalForceDirection));

	return TotalForceDirection / InputNode->Weight;

}

*/

//Don't implement this until later
/*
void SaveCreatures(std::vector<Creature*> Creatures, std::string Filename)
{
	std::ofstream SaveFile;
	SaveFile.open(Filename);

	SaveFile << Creatures.size();
	for (int i = 0; i < Creatures.size(); i++)
	{
		SaveFile << Creatures[i];
	}

	SaveFile.close();
}

std::vector<Creature*> LoadCreatures(std::string Filename)
{
	std::vector<Creature*> output;
	std::ofstream SaveFile;
	SaveFile.open(Filename);
	int VectorSize;

	//std::vector<Creature*> Output = new Creature[]


	//Right now doesn't work
	return output;
}
*/
