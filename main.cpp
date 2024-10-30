#include "Testengine.hpp"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>


int main()
{
	FILE* file;
	fopen_s(&file, "plot_results.m", "r");
	if (file)
	{
		fclose(file);
	}
	else
	{
		std::string matlabCode =
			"function plot_rows()\n"
			"	% Define the values structure\n"
			"	values = [\n"
			"\n"
			"	% Put the results here to plot!\n"
			"\n"
			"	];\n"
			"\n"
			"% Get the number of rows and columns\n"
			"	[num_rows, num_cols] = size(values);\n"
			"\n"
			"% Create a figure for plotting\n"
			"	figure;\n"
			"\n"
			"% Plot each row separately\n"
			"	hold on;% Keep the current plot so that we can overlay multiple plots\n"
			"	for i = 1:num_rows\n"
			"		plot(values(i, :), 'DisplayName', ['Backpack ' num2str(i)]);\n"
			"	end\n"
			"\n"
			"	% Calculate the average of each column\n"
			"	column_averages = mean(values, 1);\n"
			"\n"
			"% Plot the column averages\n"
			"	plot(column_averages, 'k--', 'DisplayName', 'Column Averages', 'LineWidth', 2);\n"
			"\n"
			"% Add labels and legend\n"
			"	xlabel('No. of generation');\n"
			"	ylabel('Generation value');\n"
			"	title('Genetic Knapsack problem results');\n"
			"	legend('show');\n"
			"	hold off;% Release the hold on the current plot\n"
			"end\n"
			"\n"
			"	plot_rows();\n";
		std::ofstream matlabOut("plot_results.m");
		matlabOut << matlabCode;
		matlabOut.flush();
		matlabOut.close();
	}

	TestEngine::DisplayTests();

	std::cout << "=========================================================" << std::endl;
	std::cout << "Select test to run: ";
	int select = 0;
	std::cin >> select;

	int bottom = 0;
	int top = 0;
	int populator = 0;

	if (select != 0)
	{
		std::cout << "Parameters: " << std::endl;

		std::cout << "Bottom: ";
		std::cin >> bottom;

		std::cout << "Top: ";
		std::cin >> top;
	}

	TestEngine::DisplayParameters();

	std::cout << "Select populator: ";
	std::cin >> populator;

	switch (populator)
	{
		case 0: TestEngine::globalPopulator = PopulateMethod::Bacterial; break;
		case 1: TestEngine::globalPopulator = PopulateMethod::Crossover; break;
		default:
			std::cout << "Default populator: Bacterial" << std::endl;
			break;
	}


	std::cout << "Select selector: ";
	populator = 0;
	std::cin >> populator;

	switch (populator)
	{
		case 0: TestEngine::globalSelector = GeneticSelector::BestOf; break;
		case 1: TestEngine::globalSelector = GeneticSelector::Roulette; break;
		default:
			std::cout << "Default selector: BestOf" << std::endl;
			break;
	}

	std::cout << "Working..." << std::endl;
	switch (select)
	{
		case 0: TestEngine::DefaultTest(); break;
		case 1: TestEngine::DividerTest(bottom, top); break;
		case 2: TestEngine::BackpackSizeTest(bottom, top); break;
		case 3: TestEngine::IterationCountTest(bottom, top); break;
		case 4: TestEngine::SeedTest(bottom, top); break;
		case 5: TestEngine::CrossoverTest(bottom, top); break;
		case 6: TestEngine::CrossoverPercentageTest(bottom, top); break;
		default: std::cout << "No test selected" << std::endl; break;
	}
	std::cout << "Done! Check your files!" << std::endl;
	std::cout << Engine::MemCheck();
}