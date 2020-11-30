#include "Creature.h"

bool operator ~~(const float a, const float b) //This might not work.
{
    //This code will see if two floats are within 5% of each other
    float aUpper = a + a*0.05;
    float aLower = a - a*0.05;
    return (b>aLower && b<aUpper);
    
}
//^If this doesn't work then just use a normal function

void MuscleMovement()
{
    //For each of the muscles see what is the mod frequency of time.
    for (int i = 0; i < muscles.size(); i++) 
    {
        if(fmod(LocalTimeValue,muscles[i].frequency)<mFrequencyTolerance)
        {
            //Set the selected muscle to movingin
            muscles[i]->MovingIn = true;
        }
    }
}

//Water movement eq is
//Force = -0.5 * density * velocity^2 * area * constant *(something else, v with hat)


void Creature::EventTick(float DeltaTime)
{
    
    //Increase local time by deltatime
    LocalTimeValue += DeltaTime;
    
    MuscleMovement();
    
    for (int i = 0; i < Nodes.size(); i++) 
    {
        Nodes[i] 
    }    
    
}
