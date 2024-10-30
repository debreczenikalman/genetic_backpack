#pragma once

class Engine;

enum GeneticSelector
{
	BestOf = 0,
	Roulette,
	EndOfSelectors
};

enum PopulateMethod
{
	Bacterial = 0,
	Crossover,
	EndOfPopulateMethod
};

#include "Item.hpp"
//#include "Backpack.hpp"
class Backpack;
#include "IterationPool.hpp"
#include <vector>

constexpr int testLen = ((int)GeneticSelector::EndOfSelectors) * ((int)PopulateMethod::EndOfPopulateMethod);

class Engine
{
	Engine();
	static Engine* instancePtr;
public:
	static int randomSeed;
	static int crossoverK;
	static int itemsCount;
	static int backpacksCount;
	static int backpackWeight;
	static int testLength;
	static int itemMaxValue;
	static int itemMaxWeight;

	Item* availableItems;
	std::vector<IterationPool*> iterations;

	//IterationState** iterations;
	//unsigned int iterationsCount;
	//unsigned int currentIteration;

	Engine(Engine& other) = delete;

	void operator=(const Engine& other) = delete;

	~Engine();

	static Engine* GetInstance()
	{
		if (instancePtr == nullptr)
		{
			instancePtr = new Engine();
		}
		return instancePtr;
	}

	void First(int mutationChance, GeneticSelector selector = GeneticSelector::BestOf, PopulateMethod method = PopulateMethod::Bacterial);
	void Next(int mutationChance, GeneticSelector selector = GeneticSelector::BestOf, PopulateMethod method = PopulateMethod::Bacterial);

	static int MemCheck();

	//void DisplayCurrentIteration();
	//void DisplayItems();
	//void DisplayProperties();
	//void GenerateNewIteration(PopulateMethod method);
	//void FirstIteration();
	//void Run(int mutationChance, Backpack* store, GeneticSelector selector = GeneticSelector::BestOf, PopulateMethod method = PopulateMethod::Bacterial);
};