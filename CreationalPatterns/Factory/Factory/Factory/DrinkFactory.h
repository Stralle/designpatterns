#pragma once
#include <string>
#include <map>
#include <functional>
#include "HotDrinkFactory.h"
#include "CoffeeFactory.h"
#include "TeaFactory.h"

using namespace std;

struct HotDrink;

class DrinkFactory
{
	map <string, unique_ptr<HotDrinkFactory>> factories;
public:
	DrinkFactory()
	{
		factories["coffee"] = make_unique<CoffeeFactory>();
		factories["tea"] = make_unique<TeaFactory>();
	}

	unique_ptr<HotDrink> make_drink(const string& name)
	{
		auto drink = factories[name]->make();
		drink->prepare(200); // Oops. We don't know the volume.
		return drink;
	}
};

class DrinkWithVolumeFactory
{
	map<string, function<unique_ptr<HotDrink>()>> factories;

public:
	DrinkWithVolumeFactory()
	{
		factories["tea"] = []
		{
			auto tea = make_unique<Tea>();
			tea->prepare(100);
			return tea;
		};
	}

	unique_ptr<HotDrink> make_drink(const string& name)
	{
		return factories[name]();
	}
};