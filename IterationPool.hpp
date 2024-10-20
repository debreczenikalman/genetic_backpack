#pragma once

class IterationPool;
class Backpack;;

#include "Engine.hpp"
//#include "Backpack.hpp"
#include <vector>

class IterationPool
{
	void SelectBest();
	void SelectRoulette();

	void PopulateBacterial(IterationPool* base);
	void PopulateCrossover(IterationPool* base);
public:
	std::vector<Backpack*> backpacks;
	Backpack* selected[2];

	IterationPool();

	~IterationPool();

	void Select(GeneticSelector selector);
	void Populate(PopulateMethod method, IterationPool* base = nullptr);
	void Mutate(unsigned int mutationChance);
};
