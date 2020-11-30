#include "Node.h"


//Sink function
void Node::WeightFunction()
{
    //Will move the node proportional to its weight every tick
    
    Location.y =- weight;
}

void Node::MuscleMovement()
{
    Position DeltaPosition = Position(0,0);
    //This will find all the movements of all the nodes 
    
    
    
    //Now move the node by what it should be moved by
    Position += DeltaPosition;
}
