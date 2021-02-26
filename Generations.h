#include <SFML/Graphics.hpp>
#include "Structures.h"
#include <iostream>
#include "SettingWidget.h"
#include "ClassFunctions.h"
#include <chrono>
#include <ctime>
#pragma once


CreatureFitness* InitialGeneration(int Inputseed, int CreaturesInGeneration);

CreatureFitness* StandardGeneration(int Inputseed, std::vector<Creature*> Creatures);
