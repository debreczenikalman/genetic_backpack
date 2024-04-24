#include "IterationState.hpp"
#include "Engine.hpp"
#include <cstdlib>

void IterationState::Populate(Backpack* original)
{
	for (int i = 0; i < BACKPACK_COUNT_PER_ITERATION; i++)
	{
	#if ITERATION_IN_ARRAY
		backpacks[i] = new Backpack(*original);
	#else
		for (int j = 0; j < ITEMS_COUNT; j++)
		{
			backpacks[i]->includedItems[j] = original->includedItems[j];
		}
	#endif // ITERATION_IN_ARRAY
	}
}

void IterationState::Populate()
{
	for (int i = 0; i < BACKPACK_COUNT_PER_ITERATION; i++)
	{
		backpacks[i] = new Backpack();
	}
}

void IterationState::Mutate(int mutationChance, int iterationIndex)
{
	for (int i = 1; i < BACKPACK_COUNT_PER_ITERATION; i++)
	{
		// if (rand() < mutationChance)
		{
			Engine::GetInstance()->mutator(backpacks[i], iterationIndex);
		}
	}
}

void IterationState::SelectBest()
{
	best = Engine::GetInstance()->selector(backpacks);
}

void IterationState::Initialise()
{
	backpacks = new Backpack * [BACKPACK_COUNT_PER_ITERATION];
	for (int i = 0; i < BACKPACK_COUNT_PER_ITERATION; i++)
	{
		backpacks[i] = nullptr;
	}
	best = nullptr;
}