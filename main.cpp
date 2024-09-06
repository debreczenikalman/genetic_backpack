
#include <iostream>

#include "Backpack.hpp"
#include "Engine.hpp"
#include "TestCase.hpp"
#define SAY std::cout <<
#define ENDL std::endl


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

constexpr uint32_t testLen = ((int)GeneticSelector::EndOfSelectors) * ((int)PopulateMethod::EndOfPopulateMethod);

int main()
{
	SAY "Genetic backpack problem solver" << ENDL;
	//unsigned int iterationsCount = 0xFF;
	unsigned int iterationsCount = TEST_LENGTH;
	Engine* e = Engine::GetInstance(iterationsCount);
	// e->DisplayProperties();
	std::cout << "=============================================" << std::endl;
	if (false)
	{
		e->DisplayItems();
		std::cout << "=============================================" << std::endl;
	}
	SAY ENDL;

	unsigned int divider;
	size_t begin;
	size_t top;
	SAY "Divider: ";
	std::cin >> divider;
	SAY "Seed begin: ";
	std::cin >> begin;
	SAY "Seed end: ";
	std::cin >> top;


	TestCase* tests = new TestCase[testLen];
	double** averageValues = new double* [testLen];

	for (size_t i = 0; i < testLen; i++)
	{
		averageValues[i] = new double[TEST_LENGTH];
		for (size_t j = 0; j < TEST_LENGTH; j++)
		{
			averageValues[i][j] = 0.0;
		}
	}

	for (size_t b = begin; b < top; b++)
	{
		SAY b << ENDL;
		srand(b);

		for (size_t i = 0; i < (int)GeneticSelector::EndOfSelectors; i++)
		{
			for (size_t j = 0; j < (int)PopulateMethod::EndOfPopulateMethod; j++)
			{
				tests[i * (int)GeneticSelector::EndOfSelectors + j] = TestCase(static_cast<GeneticSelector>(i), static_cast<PopulateMethod>(j));
			}
		}

		for (size_t i = 0; i < testLen; i++)
		{
			e->Run(RAND_MAX / divider, tests[i].backpacks, tests[i].selector, tests[i].populator);
			// tests[i].DisplayResult();
			for (size_t j = 0; j < TEST_LENGTH; j++)
			{
				averageValues[i][j] += tests[i].backpacks[j].Value();
			}
		}
	}

	for (size_t i = 0; i < testLen; i++)
	{
		for (size_t j = 0; j < TEST_LENGTH; j++)
		{
			averageValues[i][j] = averageValues[i][j] / (top - begin);
		}

		constexpr int width = 128;
		constexpr int height = 15;
		char graph[height][width];
		int max = 0;
		for (size_t j = 0; j < TEST_LENGTH; j++)
		{
			if (averageValues[i][j] > max)
			{
				max = averageValues[i][j];
			}
		}

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
			double debugValue = averageValues[i][(unsigned int)(TEST_LENGTH / width) * j];
			int index = (debugValue / 1.0 / max) * height;
			index = height - index - 1;
			if (index < 0)
			{
				index = 0;
			}
			graph[index][j] = '#';
		}
		std::cout << "Max: " << max << std::endl;
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				std::cout << graph[i][j];
			}
			std::cout << std::endl;
		}
	}

	delete[] tests;
	for (size_t i = 0; i < testLen; i++)
	{
		delete[] averageValues[i];
	}
	delete[] averageValues;
	delete e;
	SAY _CrtDumpMemoryLeaks();
}
