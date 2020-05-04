#include "Singleton.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
	auto& singletonDatabase = SingletonDatabase::get();
	auto& singletonDatabase2 = SingletonDatabase::get();

	std::cout << SingletonDatabase::instance_count << std::endl; // Expected 1

	// Finding a records
	SingletonRecordFinder recordFinder;
	std::vector<std::string> names{ "Seoul", "Mexico City" };

	int totalPopulation = recordFinder.total_population(names);

	std::cout << totalPopulation << std::endl; // Expected 17400000 + 17500000 = 34900000

	// Dependency Injection -> injecting dummyDatabase in ConfigurableRecordFinder
	DummyDatabase dummyDatabase{};
	ConfigurableRecordFinder configurableRecordFinder{ dummyDatabase };

	std::cout << configurableRecordFinder.total_population(std::vector<std::string>{"alpha", "gamma"}) << std::endl; // Expected 4

	return 0;
}