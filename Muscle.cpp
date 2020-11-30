#include "Muscles.h"

void Muscles::MuscleTick(float DeltaTime)
{
    //The basic idea for the tick is to decrease the value of MovementProgress by DeltaTime
    //With code elsewhere it will move the nodes and the stuff will visually update.
    //Initally this is going to look really bad, but I'll change it and stuff.
    
    
    if(MovingIn)
    {
        if(MovementProgress<=0)
        {
            MovingOut = true;
            MovingIn = false;
            MovementProgress = 5;
        }
        else
        {
            MovementProgress -= DeltaTime;
        }
    }
    
    if(MovingOut)
    {
        if(MovementProgress<=0)
        {
            MovingOut = false;
            MovingIn = false;
            MovementProgress = 5
        }
        else
        {
            MovementProgress -= DeltaTime;
        }
    }    
}
