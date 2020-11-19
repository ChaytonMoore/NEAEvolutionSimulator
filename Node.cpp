#include "Node.h"


//Sink function
void Node::WeightFunction()
{
    //Will move the node proportional to its weight every tick
    
    Location.y =- weight;
}

void Node::MuscleMovement()
{
    Position DeltaPosition;
    for (int i = 0; i < Connections.size(); i++) 
    {
        if(Connections[i].Pulling)
        {
                
        }
        
    }
}
