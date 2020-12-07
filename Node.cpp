#include "Node.h"
#include "Muscle.h"
#include <iostream>

Node::Node()
{


}
//Sink function
void Node::WeightFunction()
{
	//Will move the node proportional to its weight every tick

	Location.y = -Weight;
}

void Node::MuscleMovement()
{
	Position DeltaPosition = Position(0, 0);
	//This will find all the movements of all the nodes 



	//Now move the node by what it should be moved by
	Location += DeltaPosition;

	
}


//This should be applied to each node.
Position Node::MovementResistance(float area, Position velocity)
{
	//www.khanacademy.org/computing/computer-programming/programming-natural-simulations/programming-forces/a/air-and-fluid-resistance
	//^ That is where the function calcualtion comes from

	//This whole thing is relative force

	const float MovementConstant = 5;
	//^This should be changed if stuff needs to be different
	//float Output = -0.5 * area * pow(velocity,2) * MovementConstant;
	Position Output = Position::NormaliseVector(velocity);
	float CoefOutput;
	CoefOutput = -0.5 * area * pow(Position::ModVector(velocity), 2) * MovementConstant;
	Output.x = Output.x * CoefOutput;
	Output.y = Output.y * CoefOutput;

	
	return Output;

}

Position Node::NodeVelocity(Node* InputNode)
{
	//Firstly get all the Muscles and their forces
	//This is at school can't remeber where the stuff is will assume I've got a list of forces and a list of relative normalised positions

	
	std::vector<float> MuscleForces;
	std::vector<Position> RelativePositions; //These lists need to be the same length these positions must also be normalised
	Position Ta  = Position(0,0);
	Muscle* Temp;
	for (size_t i = 0; i < InputNode->Connections.size(); i++)
	{
		
		if ((Muscle*)(InputNode->Connections[i]))
		{
		    Temp = (Muscle*)(InputNode->Connections[i]);
			MuscleForces.push_back(Temp->MuscleOutput);
			RelativePositions.push_back(Position::NormaliseVector(InputNode->Location - (Temp->Location));
			//^ this line is a little too long to be nice
			
			//Ta = InputNode->Location - ((Muscle*)(InputNode->Connections[i]))->Location;
			
			
			//Muscles can only expand to double their original length
			if(Temp->ends[0] == InputNode)
			{
			    if(Temp->Startingdistance*2 < Distance(InputNode.Location,Temp->ends[1]))
			    {
			        //The latentvelocity will be set to 0 
			        InputNode->latentvelocity = Position(0,0);
			        Temp->MovingIn = false;
			        Temp->MovingOut = true;
			        Temp->MovementProgression = 5;
			        
			    }
			     
			}
			else
			{
			   	if(Temp->Startingdistance*2 < Distance(InputNode.Location,Temp->ends[0]))
			    {
			        //The latentvelocity will be set to 0 
			        InputNode->latentvelocity = Position(0,0);
			        Temp->MovingIn = false;
			        Temp->MovingOut = true;
			        Temp->MovementProgression = 5;
			    } 
			}
			
		}
		
		
	}

	
    

	Position TotalForceDirection = Position(0, 0);
	for (int i = 0; i < MuscleForces.size(); i++)
	{
		TotalForceDirection += RelativePositions[i] * MuscleForces[i];
	}

	if (TotalForceDirection.x > 0)
	{
		//std::cout << "force A " << TotalForceDirection.x << TotalForceDirection.y << std::endl;
	}
	

	//Now the that the force is known the mass(weight) must be used to divide it to get the velocity;
	TotalForceDirection += InputNode->MovementResistance(Area, LatentVelocity); //(TotalForceDirection + Node::MovementResistance(NodeOwner->Area, TotalForceDirection));

	return TotalForceDirection / InputNode->Weight;

}


void Node::EventTick(float DeltaTime)
{
	
	//Firstly need to move the node 
	
	LatentVelocity += NodeVelocity(this) * DeltaTime;;
	Location += LatentVelocity;
	if (abs(NodeVelocity(this).x) > 0)
	{
	//std::cout << "velocity " << NodeVelocity(this).x * DeltaTime<< NodeVelocity(this).y * DeltaTime << std::endl;
	}
	
	
}
