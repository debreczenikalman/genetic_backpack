#ifndef BACKPACK
#define BACKPACK

class Backpack;

#include "Engine.hpp"
#include "Item.hpp"


class Backpack
{
public:
	bool* includedItems;
	Backpack() : includedItems(new bool[Engine::itemsCount])
	{
		for (size_t i = 0; i < Engine::itemsCount; i++)
		{
			includedItems[i] = false;
		}
	}

	Backpack(Backpack& other) : includedItems(new bool[Engine::itemsCount])
	{
		for (int i = 0; i < Engine::itemsCount; i++)
		{
			includedItems[i] = other.includedItems[i];
		}
	}

	~Backpack()
	{
		delete includedItems;
	}

	void operator=(const Backpack& other)
	{
		for (int i = 0; i < Engine::itemsCount; i++)
		{
			includedItems[i] = other.includedItems[i];
		}
	}

	void Display();

	int Value();
	int Weight();

	void Mutate(unsigned int chance);

};

#endif