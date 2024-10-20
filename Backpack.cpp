#include "Backpack.hpp"
#include <iostream>

void Backpack::Display()
{
	std::cout << "\tItems: ";
	for (int i = 0; i < Engine::itemsCount; i++)
	{
		std::cout << includedItems[i] << " ";
	}
	std::cout << std::endl;
}

int Backpack::Value()
{
	int value = 0;
	int weight = 0;
	for (int i = 0; i < Engine::itemsCount; i++)
	{
		value += includedItems[i] * Engine::GetInstance()->availableItems[i].value;
		weight += includedItems[i] * Engine::GetInstance()->availableItems[i].weight;
	}
	if (weight <= Engine::backpackWeight)
	{
		return value;
	}
	return 0;
}

int Backpack::Weight()
{
	int weight = 0;
	for (int i = 0; i < Engine::itemsCount; i++)
	{
		weight += includedItems[i] * Engine::GetInstance()->availableItems[i].weight;
	}
	return weight;
}

void Backpack::Mutate(unsigned int chance)
{
	for (size_t i = 1; i < Engine::itemsCount; i++)
	{
		if (rand() < chance)
		{
			includedItems[i] ^= 0b01;
		}
	}
}
