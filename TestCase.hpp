#pragma once

#include "Backpack.hpp"
#include "Engine.hpp"


class TestCase
{
public:
	TestCase()
	{

	}
	TestCase(const GeneticSelector& selector, const PopulateMethod& populator) : selector(selector), populator(populator)
	{

	}
	~TestCase() = default;
	Backpack backpacks[TEST_LENGTH];
	GeneticSelector selector;
	PopulateMethod populator;
	void DisplayResult()
	{
		std::cout << "Displaying results for a test: " << std::endl;
		std::cout << "Generations count " << TEST_LENGTH << std::endl;
		std::cout << "Available items " << ITEMS_COUNT << std::endl;
		std::cout << "Backpack capacity " << BACKPACK_WEIGHT << std::endl;
		std::cout << "Selector: " << selector << " Populator: " << populator << std::endl;

		constexpr int width = 128;
		constexpr int height = 15;

		int max = 0;
		for (size_t i = 0; i < TEST_LENGTH; i++)
		{
			if (backpacks[i].Value() > max)
			{
				max = backpacks[i].Value();
			}
		}
		std::cout << "Maximum: " << max << std::endl;

		char graph[height][width];

		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				graph[i][j] = ' ';
				if (j == 0)
				{
					char val = (height - i) % 10 + 48;
					graph[i][j] = val;
				}
				if (i == height - 1)
				{
					char val = (j + 1) % 10 + 48;
					if (val == 48)
					{
						val = ' ';
					}
					graph[i][j] = val;
				}
			}
		}
		for (size_t j = 0; j < width; j++)
		{
			int debugValue = backpacks[(unsigned int)(TEST_LENGTH / width) * j].Value();
			int index = (debugValue / 1.0 / max) * height;
			index = height - index - 1;
			if (index < 0)
			{
				index = 0;
			}
			graph[index][j] = '#';
		}

		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				std::cout << graph[i][j];
			}
			std::cout << std::endl;
		}

		std::cout << "End of information" << std::endl << std::endl;
	}


};

