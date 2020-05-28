/*
	Visitor is a pattern where a component (visitor) is allowed to traverse the entire inheritance hierarchy.
	Implemented by propagating a single visit() function through the entire hierarchy.

	Dispatch
	Which function to call?

	Single dispatch: depends on name of request and type of receiver.
	Double dispatch: depends on name of request and type of two receivers. (type of visitor, type of element being visited)
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <typeindex>

#include "Model.hpp"
#include "Visitor.hpp"


struct GameObject;
void collide(GameObject& first, GameObject& second);

struct GameObject
{
	virtual ~GameObject() = default;
	virtual std::type_index type() const = 0;
	virtual void collide(GameObject& other) { ::collide(*this, other); }
};

template <typename T>
struct GameObjectImpl : GameObject
{
	std::type_index type() const override
	{
		return typeid(T);
	}
};

struct Planet : GameObjectImpl<Planet>
{
	
};

struct Asteroid : GameObjectImpl<Asteroid>
{
	
};

struct Spaceship : GameObjectImpl<Spaceship>
{
	
};

struct ArmedSpaceship : Spaceship
{
	std::type_index type() const override
	{
		return typeid(ArmedSpaceship); // This has to be done since we inherit from Spaceship that has already passed typeid.
	}
};

void spaceship_planet()
{
	std::cout << "Spaceship lands on a planet\n";
}

void asteroid_planet()
{
	std::cout << "Asteroid burns up a planet\n";
}

void asteroid_spaceship()
{
	std::cout << "Asteroid hits and destroys spaceship\n";
}

void asteroid_armed_spaceship()
{
	std::cout << "Armed spaceship shoots asteroid!\n";
}

std::map<std::pair<std::type_index, std::type_index>, void(*)(void)> outcomes
{
	{{ typeid(Spaceship), typeid(Planet) }, spaceship_planet },
	{{ typeid(Asteroid), typeid(Planet) }, asteroid_planet },
	{{ typeid(Asteroid), typeid(Spaceship) }, asteroid_spaceship },
	{{ typeid(Asteroid), typeid(ArmedSpaceship) }, asteroid_armed_spaceship },
};

void collide(GameObject& first, GameObject& second)
{
	auto it = outcomes.find({ first.type(), second.type() });
	if (it == outcomes.end())
	{
		it = outcomes.find({ second.type(), first.type() });
		if (it == outcomes.end())
		{
			std::cout << "objects pass each other harmlessly\n";
			return;
		}
	}
	it->second();

}

// Rename this to main for testing purposes.
int main()
{
	ArmedSpaceship spaceship;
	Asteroid asteroid;
	Planet planet;

	collide(planet, spaceship);
	collide(planet, asteroid);
	collide(spaceship, asteroid);
	//collide(planet, planet);
	planet.collide(planet);
	
	return 0;
}