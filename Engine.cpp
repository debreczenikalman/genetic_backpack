#include "Engine.hpp"
#include <cstdlib>
#include <iostream>

Engine* Engine::instancePtr = nullptr; // Move this to the .cpp file

int Engine::randomSeed = 1;
int Engine::crossoverK = 2;
int Engine::itemsCount = 1024;			// The number of available items
int Engine::backpacksCount = 16;		// The number of backpacks in each run
int Engine::backpackWeight = 128;		// The max weight of one backpack
int Engine::testLength = 128;			// How many runs there are
int Engine::itemMaxValue = 32;		// Maximum value of an item
int Engine::itemMaxWeight = 32;		// Maximum weight of an item

Engine::Engine() : availableItems(new Item[Engine::itemsCount]), iterations()
{
	srand(randomSeed);
	iterations.reserve(testLength);
	for (int i = 0; i < Engine::itemsCount; i++)
	{
		availableItems[i] = Item({ (unsigned int)rand() % Engine::itemMaxWeight, (unsigned int)rand() % Engine::itemMaxValue});
	}
}

Engine::~Engine()
{
	delete[] availableItems;
	for (size_t i = 0; i < iterations.size(); i++)
	{
		delete iterations[i];
	}
	instancePtr = nullptr;
}

void Engine::First(int mutationChance, GeneticSelector selector, PopulateMethod method)
{
	IterationPool* pool = new IterationPool();
	pool->Populate(method);
	iterations.push_back(pool);
}

void Engine::Next(int mutationChance, GeneticSelector selector, PopulateMethod method)
{
	IterationPool* last = iterations.back();
	IterationPool* next = new IterationPool();
	last->Select(selector);
	next->Populate(method, last);
	next->Mutate(mutationChance);
	iterations.push_back(next);
}

int Engine::MemCheck()
{
	return _CrtDumpMemoryLeaks();
}

