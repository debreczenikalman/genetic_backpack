#include "Engine.hpp"
#include <cstdlib>
#include <iostream>


Engine* Engine::instancePtr = nullptr; // Move this to the .cpp file

Engine::~Engine()
{
#if ITERATION_IN_ARRAY
	for (int i = 0; i < iterationsCount; i++)
	{
		delete iterations[i];
	}
#else
	for (int i = 0; i < 2; i++)
	{
		delete iterations[i];
	}
#endif // ITERATION_IN_ARRAY
	delete[] iterations; // Heap corruption?

	for (int i = 0; i < ITEMS_COUNT; i++)
	{
		delete availableItems[i];
	}
	delete[] availableItems;
}

void Engine::DisplayCurrentIteration()
{
	std::cout << "Displaying " << currentIteration << "th iteration" << std::endl;
	for (int i = 0; i < BACKPACK_COUNT_PER_ITERATION; i++)
	{
		std::cout << "Backpack no." << i << std::endl;
		iterations[currentIteration]->backpacks[i]->Display();
	}
	std::cout << "Displaying best" << std::endl;
	iterations[currentIteration]->SelectBest();
	iterations[currentIteration]->best->Display();
	std::cout << "Value: " << iterations[currentIteration]->best->Value() << std::endl;
	std::cout << "Weight: " << iterations[currentIteration]->best->Weight() << std::endl;
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

void Engine::GenerateNewIteration()
{
	IterationState* current = iterations[currentIteration];
#if ITERATION_IN_ARRAY
	if (currentIteration == 0)
	{
		++currentIteration;
		iterations[currentIteration] = new IterationState();
		iterations[currentIteration]->Populate(current->best);
	}
	else
	{
		IterationState* previous = iterations[currentIteration - 1];
		++currentIteration;
		iterations[currentIteration] = new IterationState();
		if (current->best->Value() > previous->best->Value())
		{
			iterations[currentIteration]->Populate(current->best);
		}
		else
		{
			iterations[currentIteration]->Populate(previous->best);
		}
	}
#else
	++currentIteration;
	currentIteration %= 2;

	IterationState* future = iterations[currentIteration];
	future->Populate(current->best);

#endif // ITERATION_IN_ARRAY




}

void Engine::FirstIteration()
{
#if ITERATION_IN_ARRAY
	iterations[currentIteration] = new IterationState();
	iterations[currentIteration]->Populate();
#else
	iterations[0]->Populate();
	iterations[1]->Populate();
#endif // ITERATION_IN_ARRAY

}

void Engine::Run()
{
	FirstIteration();
	for (int i = 0; i < iterationsCount - 1; i++)
	{
		iterations[currentIteration]->Mutate(RAND_MAX / 8, i);
		iterations[currentIteration]->SelectBest();
		GenerateNewIteration();
	}
	iterations[currentIteration]->Mutate(RAND_MAX / 8, iterationsCount);
	iterations[currentIteration]->SelectBest();
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
	#if ITERATION_IN_ARRAY
		iterations = new IterationState * [iterationsCount];
		for (int i = 0; i < iterationsCount; i++)
		{
			iterations[i] = nullptr;
		}
	#else		
		iterations = new IterationState * [2];
		for (int i = 0; i < 2; i++)
		{
			iterations[i] = new IterationState();
		}
	#endif // ITERATION_IN_ARRAY
	}

	availableItems = new Item * [ITEMS_COUNT];
	for (int i = 0; i < ITEMS_COUNT; i++)
	{
		availableItems[i] = new Item({ (unsigned int)rand() % MAX_WEIGHT, (unsigned int)rand() % MAX_VALUE });
	}
}
