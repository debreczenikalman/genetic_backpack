#include "IterationState.hpp"
#include "Engine.hpp"
#include <cstdlib>
#include <iostream>

void IterationState::Populate()
{
	for (int i = 0; i < BACKPACK_COUNT_PER_ITERATION; i++)
	{
		for (int j = 0; j < ITEMS_COUNT; j++)
		{
			backpacks[i].includedItems[j] = false;
		}
	}
}

void IterationState::PopulateBacterial(IterationState* original)
{
	for (int i = 0; i < BACKPACK_COUNT_PER_ITERATION; i++)
	{
		for (int j = 0; j < ITEMS_COUNT; j++)
		{
			backpacks[i].includedItems[j] = original->selected[0]->includedItems[j];
		}
	}
}

void IterationState::PopulateCrossover(IterationState* original, unsigned int k)
{
	Backpack offspring;
	int selectIndex = 0;
	for (size_t i = 0; i < ITEMS_COUNT; i++)
	{
		if (i % k == 0)
		{
			++selectIndex;
		}
		offspring.includedItems[i] = original->selected[selectIndex % 2]->includedItems[i];
	}
	for (size_t i = 0; i < BACKPACK_COUNT_PER_ITERATION; i++)
	{
		this->backpacks[i] = Backpack(offspring);
	}
}

void IterationState::Mutate(unsigned int mutationChance)
{
	for (int i = 1; i < BACKPACK_COUNT_PER_ITERATION; i++)
	{
		backpacks[i].Mutate(mutationChance);
	}
}

void IterationState::SelectBest(GeneticSelector selector, int count)
{
	switch (selector)
	{
		case BestOf:
			for (int i = 0; i < count; i++)
			{
				SelectBestOf(i);
			}
			break;
		case Roulette:
			for (int i = 0; i < count; i++)
			{
				SelectRoulette(i);
			}
			break;
		case EndOfSelectors:
		default:
			break;
	}
}

void IterationState::Initialise()
{
	backpacks = new Backpack[BACKPACK_COUNT_PER_ITERATION];
	for (int i = 0; i < BACKPACK_COUNT_PER_ITERATION; i++)
	{
		backpacks[i] = Backpack();
	}
}

void IterationState::SelectBestOf(int count)
{
	int bestIndex = 0;
	for (int i = 1; i < BACKPACK_COUNT_PER_ITERATION; i++)
	{
		if (backpacks[i].Value() > backpacks[bestIndex].Value())
		{
			bestIndex = i;
		}
	}
	selected[count] = &(backpacks[bestIndex]);
}

void IterationState::SelectRoulette(int count)
{
	int index = 0;
	int sum = 0;
	int values[BACKPACK_COUNT_PER_ITERATION];
	for (int i = 0; i < BACKPACK_COUNT_PER_ITERATION; i++)
	{
		values[i] = backpacks[i].Value();
		sum += values[i];
	}
	if (sum == 0)
	{
		selected[count] = &(backpacks[0]);
		return;
	}
	int roll = rand() % sum;

	sum = 0;
	for (int i = 0; i < BACKPACK_COUNT_PER_ITERATION; i++)
	{
		sum += values[i];
		if (sum >= roll)
		{
			selected[count] = &(backpacks[i]);
			return;
		}
	}
	throw std::runtime_error("No winner selected in " __FILE__);
}
