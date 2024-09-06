
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
	e->DisplayProperties();
	std::cout << "=============================================" << std::endl;
	if (false)
	{
		e->DisplayItems();
		std::cout << "=============================================" << std::endl;
	}
	SAY ENDL;

	unsigned int divider;
	SAY "Divider: ";
	std::cin >> divider;

	TestCase* tests = new TestCase[testLen];
	for (size_t i = 43; i < 45; i++)
	{
		srand(i);


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
			tests[i].DisplayResult();
		}

		std::cin;
	}
	delete[] tests;
}
