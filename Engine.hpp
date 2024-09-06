#ifndef ENGINE
#define ENGINE

class Engine;
enum GeneticSelector;

#define ITEMS_COUNT 256
#define BACKPACK_COUNT_PER_ITERATION 0xF
#define BACKPACK_WEIGHT 2048
#define TEST_LENGTH 1024

#define MAX_VALUE 2048
#define MAX_WEIGHT 2048

#include "IterationState.hpp"
#include "Backpack.hpp"
#include "Item.hpp"

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

class Engine
{
public:
	Engine(Engine& other) = delete;

	void operator=(const Engine& other) = delete;

	~Engine();

	static Engine* GetInstance()
	{
		if (instancePtr == nullptr)
		{
			instancePtr = new Engine(0);
		}
		return instancePtr;
	}

	static Engine* GetInstance(unsigned int iterationsCount)
	{
		if (instancePtr == nullptr)
		{
			instancePtr = new Engine(iterationsCount);
		}
		return instancePtr;
	}

	Item** availableItems;

	IterationState** iterations;
	unsigned int iterationsCount;
	unsigned int currentIteration;

	void DisplayCurrentIteration();
	void DisplayItems();
	void DisplayProperties();
	void GenerateNewIteration(PopulateMethod method);
	void FirstIteration();
	void Run(int mutationChance, Backpack* store, GeneticSelector selector = GeneticSelector::BestOf, PopulateMethod method = PopulateMethod::Bacterial);
	

private:
	Engine();
	Engine(int iterationsCount);
	void Initialise();
	static Engine* instancePtr;
};






#endif