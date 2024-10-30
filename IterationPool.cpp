#include "IterationPool.hpp"
#include "Backpack.hpp"

void IterationPool::SelectBest()
{
	int bestIndex = 0;
	for (int i = 1; i < Engine::backpacksCount; i++)
	{
		if (backpacks[i]->Value() > backpacks[bestIndex]->Value())
		{
			bestIndex = i;
		}
	}
	selected[0] = backpacks[bestIndex];
	selected[1] = backpacks[bestIndex];
}

void IterationPool::SelectRoulette()
{
	int index = 0;
	int sum = 0;
	for (int i = 0; i < Engine::backpacksCount; i++)
	{
		sum += backpacks[i]->Value();
	}
	if (sum == 0)
	{
		selected[0] = (backpacks[0]);
		selected[1] = (backpacks[0]);
		return;
	}

	for (size_t h = 0; h < 2; h++)
	{
		int roll = rand() % sum;
		int localSum = 0;
		for (int i = 0; i < Engine::backpacksCount; i++)
		{
			localSum += backpacks[i]->Value();
			if (localSum >= roll)
			{
				selected[h] = (backpacks[i]);
				break;
			}
		}
	}
	//throw std::runtime_error("No winner selected in " __FILE__);
}

void IterationPool::PopulateBacterial(IterationPool* base)
{
	for (size_t i = 0; i < Engine::backpacksCount; i++)
	{
		this->backpacks[i] = new Backpack(*(base->selected[0]));
	}
}

void IterationPool::PopulateCrossover(IterationPool* base)
{
	int selectIndex = 0;
	Backpack* offspring = new Backpack();
	for (size_t i = 0; i < Engine::itemsCount; i++)
	{
		if (i % Engine::crossoverK == 0)
		{
			++selectIndex;
		}
		offspring->includedItems[i] = base->selected[selectIndex % 2]->includedItems[i];
	}
	backpacks[0] = offspring;
	for (size_t i = 1; i < Engine::backpacksCount; i++)
	{
		this->backpacks[i] = new Backpack(*offspring);
	}
}

IterationPool::IterationPool() : selected(), backpacks()
{
	backpacks.reserve(Engine::backpacksCount);
	for (size_t i = 0; i < Engine::backpacksCount; i++)
	{
		backpacks.push_back(nullptr);
	}
}

IterationPool::~IterationPool()
{
	for (size_t i = 0; i < Engine::backpacksCount; i++)
	{
		delete backpacks[i];
	}
}

void IterationPool::Select(GeneticSelector selector)
{
	switch (selector)
	{
		case BestOf:
		SelectBest();
			break;
		case Roulette:
		SelectRoulette();
			break;
		case EndOfSelectors:
		default:
			break;
	}
}

void IterationPool::Populate(PopulateMethod method, IterationPool* base)
{
	if (base == nullptr)
	{
		for (int i = 0; i < Engine::backpacksCount; i++)
		{
				backpacks[i] = new Backpack();
		}
		return;
	}
	switch (method)
	{
		case Bacterial:
			PopulateBacterial(base);
			break;
		case Crossover:
			PopulateCrossover(base);
			break;
		case EndOfPopulateMethod:
		default:
			break;
	}
}

void IterationPool::Mutate(unsigned int mutationChance)
{
	for (int i = 1; i < Engine::backpacksCount; i++)
	{
		backpacks[i]->Mutate(mutationChance);
	}
}
