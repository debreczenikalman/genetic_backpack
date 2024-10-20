#pragma once


#include "Engine.hpp"
#include "Backpack.hpp"
#include <iostream>
#include <fstream>
#include <string>

#define NAME_AND_VALUE(variable) #variable << ":\t" << variable


class TestEngine
{
public:
	static GeneticSelector globalSelector;
	static PopulateMethod globalPopulator;
	TestEngine() = delete;

	static void DisplayTests()
	{
		std::cout << "Possible tests: (bottom, top parameters) - (recommended)" << std::endl;
		std::cout << "0: Default (ignore parameters)" << std::endl;
		std::cout << "1: DividerTest (mutationChance = RAND_MAX / (1 << parameter)) - (1 - 14)" << std::endl;
		std::cout << "2: BackpackSizeTest (influence the backpack size) (1 - 32)" << std::endl;
		std::cout << "3: IterationCountTest (NO. of generations = 1 << parameter) (1 - 10)" << std::endl;
		std::cout << "4: SeedTest (srand(parameter)) (100 - 200)" << std::endl;
	}

	static void DisplayParameters()
	{
		std::cout << "Possible parameters for genetic algorithm:" << std::endl;
		std::cout << "PopulateMethod:" << std::endl;
		std::cout << "\t0: Bacterial" << std::endl;
		std::cout << "\t1: Crossover" << std::endl;
		std::cout << "GeneticSelector:" << std::endl;
		std::cout << "\t0: BestOfAll" << std::endl;
		std::cout << "\t1: Roulette" << std::endl;
	}

	static void Metadata(std::string name = "metadata.txt")
	{
		std::ofstream fs(name);
		fs << "Metadata for genetic_backpack inner settings:" << std::endl;
		fs << NAME_AND_VALUE(Engine::randomSeed) << std::endl;
		fs << NAME_AND_VALUE(Engine::corssoverK) << std::endl;
		fs << NAME_AND_VALUE(Engine::itemsCount) << std::endl;
		fs << NAME_AND_VALUE(Engine::backpacksCount) << std::endl;
		fs << NAME_AND_VALUE(Engine::backpackWeight) << std::endl;
		fs << NAME_AND_VALUE(Engine::testLength) << std::endl;
		fs << NAME_AND_VALUE(Engine::itemMaxValue) << std::endl;
		fs << NAME_AND_VALUE(Engine::itemMaxWeight) << std::endl;
		fs << NAME_AND_VALUE(globalSelector) << std::endl;
		fs << NAME_AND_VALUE(globalPopulator) << std::endl;
		EndFile(fs);
	}
	static void BeginLine(std::ofstream& fs)
	{
		fs << "[";
	}
	static void SaveStates(std::ofstream& fs, int value)
	{
		fs << value << " ";
	}
	static void SaveNextLine(std::ofstream& fs)
	{
		fs << "];" << std::endl;
	}
	static void EndFile(std::ofstream& fs)
	{
		fs.flush();
		fs.close();
	}

	void Settings
	(
		int randomSeed,
		int itemsCount,
		int backpacksCount,
		int backpackWeight,
		int testLength,
		int itemMaxValue,
		int itemMaxWeight
	)
	{
		Engine::randomSeed = randomSeed;
		Engine::itemsCount = itemsCount;
		Engine::backpacksCount = backpacksCount;
		Engine::backpackWeight = backpackWeight;
		Engine::testLength = testLength;
		Engine::itemMaxValue = itemMaxValue;
		Engine::itemMaxWeight = itemMaxWeight;
	}

	static void DefaultTest()
	{
		Metadata("default_metadata.txt");
		Engine* e = Engine::GetInstance();
		unsigned int divider = 128;

		e->First(RAND_MAX / divider);

		for (size_t i = 0; i < Engine::testLength; i++)
		{
			e->Next(RAND_MAX / divider, globalSelector, globalPopulator);
		}

		std::ofstream fs("default.txt");

		for (size_t i = 0; i < Engine::backpacksCount; i++)
		{
			BeginLine(fs);
			for (size_t j = 0; j < Engine::testLength; j++)
			{
				SaveStates(fs, e->iterations[j]->backpacks[i]->Value());
			}
			SaveNextLine(fs);
		}
		EndFile(fs);
		delete e;
	}

	static void DividerTest(size_t bottom, size_t top)
	{
		Metadata("divider.txt");
		for (size_t exponent = bottom; exponent < top; exponent++)
		{
			Engine* e = Engine::GetInstance();
			int mutationChance = RAND_MAX / (1 << exponent);

			e->First(mutationChance);

			for (size_t i = 0; i < Engine::testLength; i++)
			{
				e->Next(mutationChance, globalSelector, globalPopulator);
			}

			std::string name = "divider_" + std::to_string(mutationChance);
			name = name + ".txt";
			long long sep = 0;
			std::ofstream fs(name);

			for (size_t i = 0; i < Engine::backpacksCount; i++)
			{
				BeginLine(fs);
				for (size_t j = 0; j < Engine::testLength; j++)
				{
					SaveStates(fs, e->iterations[j]->backpacks[i]->Value());
				}
				SaveNextLine(fs);
			}
			EndFile(fs);
			delete e;
		}
	}

	static void BackpackSizeTest(size_t bottom, size_t top)
	{
		Metadata("backpack_sizes.txt");
		for (size_t count = bottom; count < top; count++)
		{
			Engine* e = Engine::GetInstance();
			int mutationChance = 32;

			Engine::backpacksCount = count;

			e->First(mutationChance);

			for (size_t i = 0; i < Engine::testLength; i++)
			{
				e->Next(mutationChance, globalSelector, globalPopulator);
			}

			std::string name = "backpack_sizes_" + std::to_string(Engine::backpacksCount);
			name = name + ".txt";
			long long sep = 0;
			std::ofstream fs(name);

			for (size_t i = 0; i < Engine::backpacksCount; i++)
			{
				BeginLine(fs);
				for (size_t j = 0; j < Engine::testLength; j++)
				{
					SaveStates(fs, e->iterations[j]->backpacks[i]->Value());
				}
				SaveNextLine(fs);
			}
			EndFile(fs);
			delete e;
		}
	}

	static void IterationCountTest(size_t bottom, size_t top)
	{
		Metadata("iteration_count.txt");
		for (size_t exponent = bottom; exponent < top; exponent++)
		{
			Engine* e = Engine::GetInstance();
			int mutationChance = 32;

			Engine::testLength = 1 << exponent;

			e->First(mutationChance);

			for (size_t i = 0; i < Engine::testLength; i++)
			{
				e->Next(mutationChance, globalSelector, globalPopulator);
			}

			std::string name = "iteration_count_" + std::to_string(Engine::testLength);
			name = name + ".txt";
			long long sep = 0;
			std::ofstream fs(name);

			for (size_t i = 0; i < Engine::backpacksCount; i++)
			{
				BeginLine(fs);
				for (size_t j = 0; j < Engine::testLength; j++)
				{
					SaveStates(fs, e->iterations[j]->backpacks[i]->Value());
				}
				SaveNextLine(fs);
			}
			EndFile(fs);
			delete e;
		}
	}

	static void SeedTest(size_t bottom, size_t top)
	{
		Metadata("random_seed.txt");
		for (size_t seed = bottom; seed < top; seed++)
		{
			Engine* e = Engine::GetInstance();
			int mutationChance = 32;

			Engine::randomSeed = seed;
			srand(Engine::randomSeed);

			e->First(mutationChance);

			for (size_t i = 0; i < Engine::testLength; i++)
			{
				e->Next(mutationChance, globalSelector, globalPopulator);
			}

			std::string name = "random_seed_" + std::to_string(Engine::randomSeed);
			name = name + ".txt";
			long long sep = 0;
			std::ofstream fs(name);

			for (size_t i = 0; i < Engine::backpacksCount; i++)
			{
				BeginLine(fs);
				for (size_t j = 0; j < Engine::testLength; j++)
				{
					SaveStates(fs, e->iterations[j]->backpacks[i]->Value());
				}
				SaveNextLine(fs);
			}
			EndFile(fs);
			delete e;
		}
	}
};

GeneticSelector TestEngine::globalSelector = GeneticSelector::BestOf;
PopulateMethod TestEngine::globalPopulator = PopulateMethod::Bacterial;
