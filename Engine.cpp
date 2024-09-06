#include "Engine.hpp"
#include <cstdlib>
#include <iostream>


Engine* Engine::instancePtr = nullptr; // Move this to the .cpp file

Engine::~Engine()
{
	for (int i = 0; i < 2; i++)
	{
		delete iterations[i];
	}
	delete[] iterations;
	for (int i = 0; i < ITEMS_COUNT; i++)
	{
		delete availableItems[i];
	}
	delete[] availableItems;
}

void Engine::DisplayCurrentIteration()
{
	//std::cout << "Displaying " << currentIteration << "th iteration" << std::endl;
	//for (int i = 0; i < BACKPACK_COUNT_PER_ITERATION; i++)
	//{
	//	std::cout << "Backpack no." << i << std::endl;
	//	iterations[currentIteration]->backpacks[i].Display();
	//}
	std::cout << "Displaying best" << std::endl;
	iterations[currentIteration]->SelectBest(BestOf);
	iterations[currentIteration]->selected[0]->Display();
	std::cout << "Value: " << iterations[currentIteration]->selected[0]->Value() << std::endl;
	std::cout << "Weight: " << iterations[currentIteration]->selected[0]->Weight() << std::endl;
}

void Engine::DisplayItems()
{
	std::cout << "Displaying items:" << std::endl;
	for (int i = 0; i < ITEMS_COUNT; i++)
	{
		std::cout << "Item no. " << i << ": " << std::endl;
		std::cout << "\tWieght: " << availableItems[i]->weight << std::endl;
		std::cout << "\tValue: " << availableItems[i]->value << std::endl;
		std::cout << "=========================================" << std::endl;
	}
}

void Engine::DisplayProperties()
{
	std::cout << "Displaying propertis of simulation" << std::endl;
	std::cout << "Backpack capacity: " << BACKPACK_WEIGHT << std::endl;
	std::cout << "Number of backpacks in an iteration: " << BACKPACK_COUNT_PER_ITERATION << std::endl;
	std::cout << "Item max weight: " << MAX_WEIGHT << std::endl;
	std::cout << "Item max value: " << MAX_VALUE << std::endl;
}

void Engine::GenerateNewIteration(PopulateMethod method)
{
	IterationState* current = iterations[currentIteration];
	++currentIteration;
	currentIteration %= 2;
	IterationState* future = iterations[currentIteration];
	switch (method)
	{
		case Bacterial:
			future->PopulateBacterial(current);
			break;
		case Crossover:
			future->PopulateCrossover(current);
			break;
		case EndOfPopulateMethod:
		default:
			std::runtime_error("Invalid selector");
			break;
	}
}

void Engine::FirstIteration()
{
	iterations[0]->Populate();
	iterations[1]->Populate();
}

void Engine::Run(int mutationChance, Backpack* store, GeneticSelector selector, PopulateMethod method)
{
	FirstIteration();
	for (int i = 0; i < iterationsCount; i++)
	{
		iterations[currentIteration]->Mutate(mutationChance);
		if (selector == GeneticSelector::BestOf)
		{
			iterations[currentIteration]->SelectBest(selector, 2);
		}
		else
		{
			iterations[currentIteration]->SelectBest(selector, 2);
		}
		store[i] = Backpack(*iterations[currentIteration]->selected[0]);
		GenerateNewIteration(method);
	}
	iterations[currentIteration]->Mutate(mutationChance);
	if (selector == GeneticSelector::BestOf)
	{
		iterations[currentIteration]->SelectBest(selector, 2);
	}
	else
	{
		iterations[currentIteration]->SelectBest(selector, 2);
	}
	store[iterationsCount - 1] = Backpack(*iterations[currentIteration]->selected[0]);
}


Engine::Engine() : availableItems(0), currentIteration(0), iterations(0), iterationsCount(0)
{
	Initialise();
}

Engine::Engine(int iterationsCount) : availableItems(0), currentIteration(0), iterations(0), iterationsCount(iterationsCount)
{
	Initialise();
}

void Engine::Initialise()
{
	if (iterationsCount > 0)
	{
		iterations = new IterationState * [2];
		for (int i = 0; i < 2; i++)
		{
			iterations[i] = new IterationState();
		}
	}

	availableItems = new Item * [ITEMS_COUNT];
	for (int i = 0; i < ITEMS_COUNT; i++)
	{
		availableItems[i] = new Item({ (unsigned int)rand() % MAX_WEIGHT, (unsigned int)rand() % MAX_VALUE, 0 });
	}
}
