#ifndef ENGINE
#define ENGINE

class Engine;

#define ITERATION_IN_ARRAY false

#define ITEMS_COUNT 32
#define BACKPACK_COUNT_PER_ITERATION 0xF
#define BACKPACK_WEIGHT 128

#define MAX_VALUE 128
#define MAX_WEIGHT 128

#include "IterationState.hpp"
#include "Backpack.hpp"
//#include "Item.hpp"

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

	enum GeneticSelector
	{
		Best = 0,
		EndOfSelectors
	};

	Item** availableItems;

	IterationState** iterations;
	unsigned int iterationsCount;
	unsigned int currentIteration;

	Backpack* (*selector)(Backpack**);
	void (*mutator)(Backpack*, int);

	void DisplayCurrentIteration();
	void DisplayItems();
	void DisplayProperties();
	void GenerateNewIteration();
	void FirstIteration();
	void Run();
	

private:
	Engine();
	Engine(int iterationsCount);
	void Initialise();
	static Engine* instancePtr;

};






#endif