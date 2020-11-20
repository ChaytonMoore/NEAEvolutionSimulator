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
    Position RelativeMusclePosition;
    for (int i = 0; i < Connections.size(); i++) 
    {
        RelativeMusclePosition = Connections[i].Location - Position;
        if(Connections[i].Pulling)
        {
            //When it is pulling move that way by strength
            DeltaPosition += RelativeMusclePosition * ((Muscle*)Connections[0]).strength;
        }
        
    }
    //Now move the node by what it should be moved by
    Position += DeltaPosition;
}
