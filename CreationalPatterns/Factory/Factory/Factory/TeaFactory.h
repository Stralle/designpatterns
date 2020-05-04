#pragma once
//#include "HotDrink.h"
#include "HotDrinkFactory.h"

struct HotDrink;

struct TeaFactory : public HotDrinkFactory
{
	std::unique_ptr<HotDrink> make() override
	{
		return std::make_unique<Tea>();
	}
};