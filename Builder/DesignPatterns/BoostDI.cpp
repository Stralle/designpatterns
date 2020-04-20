/*
	Dependency Injection example on Boost DI library
*/

#include "BoostDI.h"
#include <iostream>
#include <memory>

struct ILogger
{
	virtual ~ILogger()
	{
	}

	virtual void Log(const std::string& s) = 0;
};

struct ConsoleLogger : ILogger
{
	void Log(const std::string& s) override
	{
		std::cout << "LOG: " << s.c_str() << std::endl;
	}
};

struct Engine
{
	float volume = 5;
	int horse_power = 400;

	std::shared_ptr<ILogger> logger;

	Engine(const std::shared_ptr<ILogger>& iLogger)
		: logger{ iLogger }
	{
		logger->Log("Created an engine");
	}

	friend std::ostream& operator<<(std::ostream& os, const Engine& obj)
	{
		return os << "volume: " << obj.volume << " horse_power: " << obj.horse_power;
	}
};

struct Car
{
	std::shared_ptr<Engine> engine;
	std::shared_ptr<ILogger> logger;

	Car(const std::shared_ptr<Engine>& iEngine, const std::shared_ptr<ILogger>& iLogger)
		: engine(iEngine), logger(iLogger)
	{
		logger->Log("Created a car");
	}

	friend std::ostream& operator<<(std::ostream& os, const Car& obj)
	{
		return os << "Car with Engine: " << *obj.engine;
	}
};

// Change the method name to main when you want to run the example of this design pattern.
int mainBoostDI()
{
	/*std::shared_ptr<Engine> e = std::make_shared<Engine>();
	std::shared_ptr<Car> c = std::make_shared<Car>(e);

	std::cout << *e << std::endl;
	std::cout << *c << std::endl;*/

	using namespace boost;
	auto injector = di::make_injector(
		di::bind<ILogger>().to<ConsoleLogger>() // External object, injector actually handles our constructors and everything.
	);
	auto c = injector.create<std::shared_ptr<Car>>();

	std::cout << *c << std::endl;


	return 0;
}









