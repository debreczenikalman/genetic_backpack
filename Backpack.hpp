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
		for (int i = 0; i < ITEMS_COUNT; i++)
		{
			includedItems[i] = false;
		}
	}

	Backpack(Backpack& other)
	{
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

	void Mutate(unsigned int chance);

	~Backpack()
	{

	}

	bool includedItems[ITEMS_COUNT];

private:

};

#endif