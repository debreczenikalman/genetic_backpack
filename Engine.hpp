#ifndef ENGINE
#define ENGINE

class Engine;
enum GeneticSelector;

#define ITEMS_COUNT 0b1000000000
#define BACKPACK_COUNT_PER_ITERATION 0b10000
#define BACKPACK_WEIGHT 0b100000000000
#define TEST_LENGTH 0b1000000000

#define MAX_VALUE 0b1000000000000
#define MAX_WEIGHT 0b1000000000000

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