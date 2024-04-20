#include "Backpack.hpp"
#include <iostream>

void Backpack::Display()
{
	std::cout << "\tItems: ";
	for (int i = 0; i < ITEMS_COUNT; i++)
	{
		std::cout << includedItems[i] << " ";
	}
	std::cout << std::endl;
}

int Backpack::Value()
{
	int value = 0;
	int weight = 0;
	for (int i = 0; i < ITEMS_COUNT; i++)
	{
		value += includedItems[i] * Engine::GetInstance()->availableItems[i]->value;
		weight += includedItems[i] * Engine::GetInstance()->availableItems[i]->weight;
	}
	if (weight <= BACKPACK_WEIGHT)
	{
		return value;
	}
	return 0;
}

int Backpack::Weight()
{
	int weight = 0;
	for (int i = 0; i < ITEMS_COUNT; i++)
	{
		weight += includedItems[i] * Engine::GetInstance()->availableItems[i]->weight;
	}
	return weight;
}
