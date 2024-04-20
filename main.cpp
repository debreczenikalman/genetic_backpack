
#include <iostream>

#include "Backpack.hpp"
#include "Engine.hpp"
#define SAY std::cout <<
#define ENDL std::endl

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


// =================================================== Utils

Backpack* AbsoluteBest(Backpack** backpacks)
{
	int bestIndex = 0;
	for (int i = 1; i < BACKPACK_COUNT_PER_ITERATION; i++)
	{
		if (backpacks[i]->Value() > backpacks[bestIndex]->Value())
		{
			bestIndex = i;
		}
	}
	return backpacks[bestIndex];
}

void MutateSimple(Backpack* backpack, int iterationIndex)
{
	for (int i = 0; i < ITEMS_COUNT; i++)
	{
		bool debug = (rand() < (RAND_MAX / (1.0 + iterationIndex)) + 1024);
		backpack->includedItems[i] ^= debug;
	}
}

// =================================================== End of Utils


int main()
{
	SAY "Genetic backpack problem solver" << ENDL;
	unsigned int iterationsCount = 0xFF; // 

	srand(2);

	Engine* e = Engine::GetInstance(iterationsCount);
	e->DisplayProperties();
	if (false)
	{
		e->DisplayItems();
	}
	e->selector = AbsoluteBest;
	e->mutator = MutateSimple;
	e->Run();
	e->DisplayCurrentIteration();

	delete e;
	SAY _CrtDumpMemoryLeaks() << ENDL;
	std::cout << "End" << std::endl;
}














// Debreczeni Kálmán - ZPFI2H