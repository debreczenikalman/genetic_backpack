#ifndef ITERATION_STATE
#define ITERATION_STATE

class IterationState;

#include "Engine.hpp"
#include "Backpack.hpp"
#include "Item.hpp"

//#define BACKPACK_COUNT 8


class IterationState
{
public:
	IterationState()
	{
		Initialise();
	}

	~IterationState()
	{
		for (int i = 0; i < BACKPACK_COUNT_PER_ITERATION; i++)
		{
			delete backpacks[i];
		}
		delete[] backpacks;
	}

	// Array of pointers
	Backpack** backpacks;

	// Pointer to best
	Backpack* best;

	void Populate(Backpack* original);
	void Populate();

	void Mutate(int mutationChance, int iterationIndex);
	
	void SelectBest();

private:
	void Initialise();

};




#endif