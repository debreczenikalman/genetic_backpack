#include "Engine.hpp"
#include <cstdlib>
#include <iostream>

Engine* Engine::instancePtr = nullptr; // Move this to the .cpp file

int Engine::randomSeed = 1;
int Engine::corssoverK = 0b10;
int Engine::itemsCount = 0b10000000000;			// The number of available items
int Engine::backpacksCount = 0b100000;			// The number of backpacks in each run
int Engine::backpackWeight = 0b100000000000;	// The max weight of one backpack
int Engine::testLength = 0b100000000;			// How many runs there are
int Engine::itemMaxValue = 0b1000000000000;		// Maximum value of an item
int Engine::itemMaxWeight = 0b1000000000000;	// Maximum weight of an item

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

