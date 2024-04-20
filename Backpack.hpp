#ifndef BACKPACK
#define BACKPACK

class Backpack;

#include "Engine.hpp"
#include "Item.hpp"


class Backpack
{
public:
	Backpack()
	{
		includedItems = new bool[ITEMS_COUNT];
		for (int i = 0; i < ITEMS_COUNT; i++)
		{
			includedItems[i] = false;
		}
	}

	Backpack(Backpack& other)
	{
		includedItems = new bool[ITEMS_COUNT];
		for (int i = 0; i < ITEMS_COUNT; i++)
		{
			includedItems[i] = other.includedItems[i];
		}
	}

	void operator=(const Backpack& other)
	{
		for (int i = 0; i < ITEMS_COUNT; i++)
		{
			includedItems[i] = other.includedItems[i];
		}
	}

	void Display();

	int Value();
	int Weight();

	~Backpack()
	{
		delete[] includedItems;
	}

	bool* includedItems;

private:

};

#endif