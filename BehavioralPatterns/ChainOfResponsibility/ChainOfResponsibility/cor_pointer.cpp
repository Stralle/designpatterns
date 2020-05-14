/*
	Who takes the blame of unethical behavior by employee? Employee -> Manager -> CEO
	You click a graphical element on a form: Button handles it, stops further processing -> Underlying group box -> Underlying window
	Card Computer Game: Creature has attack and defense values -> Those can be boosted by other cards

	Chain of Responsibility: A chain of components who all get a chance to process a command or query, optionally having a default processing implementation
	and an ability to terminate the processin
*/
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

struct Creature
{
	string name;
	int attack, defense;


	Creature(const string& name, int attack, int defense)
		: name(name),
		  attack(attack),
		  defense(defense)
	{
	}


	friend std::ostream& operator<<(std::ostream& os, const Creature& obj)
	{
		return os
			<< "name: " << obj.name
			<< " attack: " << obj.attack
			<< " defense: " << obj.defense;
	}
};

class CreatureModifier
{
	CreatureModifier* next = nullptr;
	string name;
protected:
	Creature& creature;
public:

	CreatureModifier(Creature& creature, const string& name)
		: creature(creature), name(name)
	{
	}
	virtual ~CreatureModifier() = default;

	void add(CreatureModifier* cm)
	{
		if (next)
		{
			next->add(cm);
		}
		else
		{
			cout << "Set next modifier " << cm->name << endl;
			next = cm;
		}
	}

	virtual void handle()
	{
		if (next)
		{
			next->handle();
		}
	}
};

// 1. Double the creature's attack
// 2. Increase defense by 1 unless power > 2
// 3. No bonuses can be applied to this creature

class DoubleAttackModifier : public CreatureModifier
{
public:
	explicit DoubleAttackModifier(Creature& creature)
		: CreatureModifier(creature, "DoubleAttackModifier")
	{
	}

	void handle() override
	{
		creature.attack = creature.attack * 2;
		cout << "Doubled attack " << creature.attack << endl;
		CreatureModifier::handle(); // This is actually making a chain of responsibility
	}
};

class IncreaseDefenseModifier : public CreatureModifier
{
public:
	explicit IncreaseDefenseModifier(Creature& creature)
		: CreatureModifier(creature, "IncreaseDefenseModifier")
	{
	}

	void handle() override
	{
		if (creature.attack <= 2)
		{
			cout << "Defense increased " << creature.defense << endl;
			creature.defense += 1;
		}
		CreatureModifier::handle(); // This is actually making a chain of responsibility
	}
};

class NoBonusModifier : public CreatureModifier
{
public:
	explicit NoBonusModifier(Creature& creature)
		: CreatureModifier(creature, "NoBonusModifier")
	{
	}


	void handle() override
	{
		// Invoke no other bonuses.
	}
};

// Rename this to main to test it out
int PointerMain()
{
	Creature goblin{ "Goblin", 1, 1 };

	CreatureModifier root{ goblin, "root" };
	DoubleAttackModifier rt1{ goblin };
	DoubleAttackModifier rt1_2{ goblin };
	IncreaseDefenseModifier rt2{ goblin };
	NoBonusModifier no{ goblin };

	root.add(&no);
	root.add(&rt1);
	root.add(&rt1_2);
	root.add(&rt2);
	
	root.handle();
	
	cout << goblin << endl;
	
	return 0;
}