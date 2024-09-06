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
		delete[] backpacks;
	}


	Backpack* backpacks;
	Backpack* selected[2];

	void Populate();
	void PopulateBacterial(IterationState* original);
	void PopulateCrossover(IterationState* original, unsigned int k = 1); // k = 1 -> uniform

	void Mutate(unsigned int mutationChance);
	
	void SelectBest(GeneticSelector selector, int count = 0);

private:
	void Initialise();
	void SelectBestOf(int count);
	void SelectRoulette(int count);
};




#endif