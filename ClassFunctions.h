#pragma once
#include "Creature.h"
#include "Structures.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
#include <string>


template<typename T>
std::vector<T> AppendVector(std::vector<T> a, std::vector<T> b);

Creature* GenerateNewRandom(int seed);

Creature* CreateChild(Creature* Base, int seed);

std::vector<Creature*> Reproduce(std::vector<Creature*> StartCreatures, std::vector<float> Fitness, int seed);

