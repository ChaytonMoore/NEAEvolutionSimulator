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
	for (size_t i = 0; i < rand() % 3 + 2; i++)
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

	//TempConnections.insert(std::end(TempConnections), std::begin(Output->Bones), std::end(Output->Bones)); \\legacy funcationality

	//creature pointer list thing
	std::vector<Muscle*> temppointers;
	for (size_t i = 0; i < Output->Muscles.size(); i++)
	{
		temppointers.push_back(Output->Muscles[i]);
	}

	TempConnections.insert(std::end(TempConnections), std::begin(temppointers), std::end(temppointers));
	//^This might be fixed or it might be broken
	

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
			
		} while ((Output->Muscles[i]->ends[0] == Output->Muscles[i]->ends[1]) && TempTimes < 25);
		
		
		Output->Muscles[i]->Location = Position((Output->Muscles[i]->ends[0]->Location.x + Output->Muscles[i]->ends[1]->Location.x)/2, (Output->Muscles[i]->ends[0]->Location.y + Output->Muscles[i]->ends[1]->Location.y) / 2);
		Output->Muscles[i]->StartingDistance = Output->Muscles[i]->ends[0]->Location.DistanceTo(Output->Muscles[i]->ends[1]->Location);
		Output->Muscles[i]->MovementProgress = 1;
	}


	
	return Output;
}


Creature* GenerateNewRandom2(int seed)
{
	Creature* Output = new Creature;


	//Then create the seed
	srand(seed);

	//Use the random numbers to 
	for (size_t i = 0; i < rand() % 2 + 2; i++)
	{
		Output->Nodes.push_back(new Node);
		Output->Nodes.back()->Location = Position(rand() % 20 + 20, rand() % 20 + 20);
	}
	
	for (size_t i = 0; i <  Output->Nodes.size(); i++)
	{
		if (Output->Nodes[i]->Connections.empty())
		{
			Output->Muscles.push_back(new Muscle);
			Output->Muscles.back()->ends[0] = Output->Nodes[i];
			do
			{
				Output->Muscles.back()->ends[1] = Output->Nodes[rand()% Output->Nodes.size()];

			} while (Output->Muscles.back()->ends[0] == Output->Muscles.back()->ends[1]);
		}

	}


	for (size_t i = 0; i < Output->Muscles.size(); i++)
	{
		Output->Muscles[i]->Strength = (rand() % 4 -2) / 10 + 1;
		Output->Muscles[i]->Frequency = rand() % 1 + 2;
		//Set up the starting distance for each muscle

		Output->Muscles[i]->StartingDistance = Output->Muscles[i]->ends[0]->Location.DistanceTo(Output->Muscles[i]->ends[1]->Location);
			

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



	//Remove the bone stuff
	/*for (int i = 0; i < Output->Muscles.size(); i++)
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
	*/

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


				//Actually this is legacy and isn't needed
				//if (TContains(Output->Bones[i], Output->Nodes[j].Connections)) //keep
				//{
					//Output->Nodes[j]->Connections[Output->Nodes[j].Connections.find(Output->Bones[i])] = Output->Muscles[Output.Muscles.size()];


					//Output->Nodes[j].Connections[TFindElem(&(Connection)Output->Bones[i], Output->Nodes[j].Connections)] = &(Connection)Output->Bones[Output->Muscles.size()];//keep

						//That's a long and confusing line, it replaces references

				//}
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



std::vector<Node*> ConnectionCheck(Creature* input)
{
	std::vector<Node*> output;
	for (size_t i = 0; i < input->Nodes.size(); i++)
	{
		if (input->Nodes[i]->Connections.size()<1)
		{
			output.push_back(input->Nodes[i]);
		}
	}

	return output;
}

Creature* CreateChild2(Creature* Base, int seed)
{
	srand(time(NULL));
	Creature* Output = new Creature(*Base);
	//First thing to do would be to potentially remove a node.
	int chance = rand() % 4;
	if (chance == 0 && Output->Nodes.size()>4)
	{
		Output->Nodes.erase(Output->Nodes.begin() + rand() % (Output->Nodes.size()-1));
		std::vector<Muscle*> MusclesToRemove;
		for (size_t i = 0; i < Output->Muscles.size(); i++)
		{
			if (!Output->Muscles[i]->ends[0] || !Output->Muscles[i]->ends[1])
			{
				MusclesToRemove.push_back(Output->Muscles[i]);
			}
		}
		for (size_t i = 0; i < MusclesToRemove.size(); i++)
		{
			delete MusclesToRemove[MusclesToRemove.size()-i];
		}

		//Add this later
		//std::vector<Node*> LostConnection = ConnectionCheck(Output);

		//for (size_t i = 0; i < LostConnection.size(); i++)
		//{
			
		//}

	}

	//Now time to add the code for potentially adding a new node.
	chance = rand() % 4;

	if (chance == 0 && Output->Nodes.size() < 8)
	{
		Output->Nodes.push_back(new Node);

		Output->Muscles.push_back(new Muscle);
		Output->Nodes.back()->Connections.push_back(Output->Muscles.back());

		int OtherNode = rand() % (Output->Nodes.size() - 2);
		Output->Nodes[OtherNode]->Connections.push_back(Output->Muscles.back());

		Output->Muscles.back()->ends[0] = Output->Nodes.back();
		Output->Muscles.back()->ends[1] = Output->Nodes[OtherNode];



	}
	for (size_t i = 0; i < Output->Nodes.size(); i++)
	{
		chance = rand() % 3;
		if (chance == 0)
		{
			Output->Nodes[i]->Weight += ((rand() % 2) -1)/10;
		}
		else
		{
			Output->Nodes[i]->Location.x += rand() % 4 - 2;
			Output->Nodes[i]->Location.y += rand() % 4 - 2;
		}

	}
	for (size_t i = 0; i < Output->Muscles.size(); i++)
	{
		chance = rand() % 3;
		if (chance == 0)
		{
			Output->Muscles[i]->Strength += ((rand() % 2) - 1) / 10;
		}

	}



	return Output;

}

std::vector<Creature*> Reproduce(std::vector<Creature*> StartCreatures, std::vector<float> Fitness, int seed)
{
	std::vector<Creature*> Output;
	

	std::cout << StartCreatures[0]->GetAverageLocation().x << std::endl;

	//Sort the list, original list needs to remain untouched.
	std::vector<int> ListOrder;
	
	int largest;
	int idx;
	
	while (ListOrder.size()<Fitness.size())
	{
		largest = -100000;
		//^ This should be small enough
		for (size_t i = 0; i < Fitness.size(); i++)
		{
			if (Fitness[i] > largest && !std::count(ListOrder.begin(), ListOrder.end(), i))
			{
				largest = Fitness[i];
				idx = i;

				
			}

		}
		
		ListOrder.push_back(idx);
		
	}

	for (size_t i = 0; i < ListOrder.size(); i++)
	{
		
		Output.push_back(StartCreatures[ListOrder[i]]);
		
	}

	//Now destroy half of the list for repopulation.
	Output.erase(Output.begin() + Output.size()/2, Output.end());
	int StartLength = Output.size();
	//Now for each of the creatures, create a child.


	srand(seed);

	bool TempValid;
	int TIdx1, TIdx2;
	for (size_t i = 0; i < StartLength; i++)
	{
		//Output.push_back(CreateChild2(Output[i],i));
		//Output.push_back(GenerateNewRandom2(i));
		
		//There might be a problem that copying the creature causes
		Output.push_back(new Creature());
		for (size_t j = 0; j < Output[i]->Nodes.size(); j++)
		{
			Output.back()->Nodes.push_back(new Node());
			Output.back()->Nodes.back()->Location.x = Output[i]->Nodes[j]->Location.x + (rand() % 4 -2);
			Output.back()->Nodes.back()->Location.y = Output[i]->Nodes[j]->Location.y + (rand() % 4 - 2);
			Output.back()->Nodes.back()->Weight = Output[i]->Nodes[j]->Weight * (1 + ((rand() % 100) / 200 - 0.25));
		}
		for (size_t j = 0; j < Output[i]->Muscles.size(); j++)
		{
			Output.back()->Muscles.push_back(new Muscle());

			Output.back()->Muscles.back()->Biases[0] = Output[i]->Muscles[j]->Biases[0] * (1+((rand() % 100)/500 - 0.1));
			Output.back()->Muscles.back()->Biases[1] = Output[i]->Muscles[j]->Biases[1] * (1 + ((rand() % 100) / 500 - 0.1));
			Output.back()->Muscles.back()->Biases[2] = Output[i]->Muscles[j]->Biases[2] * (1 + ((rand() % 100) / 500 - 0.1));
			Output.back()->Muscles.back()->Biases[3] = Output[i]->Muscles[j]->Biases[3] * (1 + ((rand() % 100) / 500 - 0.1));

			Output.back()->Muscles.back()->Frequency = Output[i]->Muscles[j]->Frequency;
			Output.back()->Muscles.back()->Strength = Output[i]->Muscles[j]->Strength;
			//To set the muscle ends the index of the nodes in the base creature must be found

			//Damn is this a horrible way to do it


			TIdx1 = std::distance(Output[i]->Nodes.begin(), std::find(Output[i]->Nodes.begin(), Output[i]->Nodes.end(), (Output[i]->Muscles[j]->ends[0])));
			TIdx2 = std::distance(Output[i]->Nodes.begin(), std::find(Output[i]->Nodes.begin(), Output[i]->Nodes.end(), Output[i]->Muscles[j]->ends[1])); //keep
			
			

			
			

			Output.back()->Muscles.back()->ends[0] = Output.back()->Nodes[TIdx1];
			Output.back()->Muscles.back()->ends[1] = Output.back()->Nodes[TIdx2];
			Output.back()->Muscles.back()->StartingDistance = Output[i]->Muscles[j]->StartingDistance;


			Output.back()->Nodes[TIdx1]->Connections.push_back(Output.back()->Muscles.back());
			Output.back()->Nodes[TIdx2]->Connections.push_back(Output.back()->Muscles.back());
		}

		if (rand() % 6 == 0)
		{
			//The chance that a node is either added or removed
			if (rand() % 1 == 0)
			{
				Output.back()->Nodes.push_back(new Node);
				//Add new Node
				//the new node will have to have connections created for it and so on.
				Output.back()->Nodes.back()->Location = Position(rand() % 15 + 10, rand()% 15 + 10);

				Output.back()->Muscles.push_back(new Muscle());
				Output.back()->Muscles.back()->ends[0] = Output.back()->Nodes.back();
				Output.back()->Muscles.back()->ends[1] = Output.back()->Nodes[Output.back()->Nodes.size()-2];

				
				Output.back()->Muscles[i]->StartingDistance = Output.back()->Muscles[i]->ends[0]->Location.DistanceTo(Output.back()->Muscles[i]->ends[1]->Location);
			}
			else if(Output.back()->Nodes.size() > 4)
			{
				//Might as well use a now unused variable (TIdx1)
				TIdx1 = rand() % Output.back()->Nodes.size();

				for (size_t Connect = 0; Connect < Output.back()->Nodes.back()->Connections.size(); Connect++)
				{
					
					delete Output.back()->Nodes[TIdx1]->Connections[Connect];
				}
				//Output.back()->Nodes.pop_back();
				Output.back()->Nodes.erase(Output.back()->Nodes.begin() + TIdx1);
			}
		}

		if (rand() % 5 == 0)
		{
			//The chnace to add a new muscle, this will deliberatly fail some of the time.
			//I'll use the variables declared a little while back (TIdx) for the indexing.

			TIdx1 = rand() % (Output.back()->Nodes.size() - 1);
			TIdx2 = rand() % (Output.back()->Nodes.size() - 1);
			if (TIdx1 != TIdx2)
			{
				TempValid = true;
				for (size_t i = 0; i < Output.back()->Muscles.size(); i++)
				{
					if (((Output.back()->Nodes[TIdx1]) == (Output.back()->Muscles[i]->ends[0]) && (Output.back()->Nodes[TIdx2]) == Output.back()->Muscles[i]->ends[1]) || ((Output.back()->Nodes[TIdx2]) == Output.back()->Muscles[i]->ends[1] && (Output.back()->Nodes[TIdx1]) == Output.back()->Muscles[i]->ends[0]))
					{
						TempValid = false;
					}
				}
				if (TempValid)
				{
					Output.back()->Muscles.push_back(new Muscle());
					Output.back()->Muscles.back()->ends[0] = Output.back()->Nodes[TIdx1];
					Output.back()->Muscles.back()->ends[1] = Output.back()->Nodes[TIdx2];
				}
			}
		}
	}



	std::cout << "size" << Output.size() << std::endl;
	return Output;
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
