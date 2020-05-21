/*
	Observer is an object that wishes to be informed about events happening in the system.
	Typically it provides a callback function to call when events occur.
	The entity generating the events is sometimes called observable.
*/
#include <iostream>
#include <mutex>
#include <string>
#include <vector>

#include <boost/any.hpp>
using namespace boost;

struct Person;

struct PersonListener
{
	virtual ~PersonListener() = default;
	virtual void PersonChanged(Person& p, const std::string& property_name, const any new_value) = 0;
};

static std::mutex mtx;

struct Person
{
	explicit Person(int age)
		: age(age)
	{
	}

	virtual int GetAge() const
	{
		return age;
	}

	virtual void SetAge(const int age)
	{
		if (this->age == age)
		{
			return;
		}

		const auto old_can_vote = GetCanVote();
		
		this->age = age;
		notify("age", this->age);

		const auto new_can_vote = GetCanVote();

		if (old_can_vote != new_can_vote)
		{
			notify("can_vote", new_can_vote);
		}
	}

	bool GetCanVote() const
	{
		return age >= 16;
	}

	void subscribe(PersonListener* pl)
	{
		std::lock_guard<std::mutex> guard{ mtx };
		if (std::find(std::begin(listeners), std::end(listeners), pl) == std::end(listeners))
		{
			listeners.push_back(pl);
		}
	}

	void unsubscribe(PersonListener* pl)
	{
		std::lock_guard<std::mutex> guard{ mtx };
		for (auto it = listeners.begin(); it != listeners.end(); ++it)
		{
			if (*it == pl)
			{
				*it = nullptr;
			}
		}
	}

	void notify(const std::string& property_name, const any new_value)
	{
		std::lock_guard<std::mutex> guard{ mtx };
		for (const auto listener : listeners)
		{
			if (listener)
			{
				listener->PersonChanged(*this, property_name, new_value);
			}
		}
		listeners.erase(
			remove(listeners.begin(), listeners.end(), nullptr), 
			listeners.end()
		);
	}

private:
	int age;
	std::vector<PersonListener*> listeners;
};

struct ConsoleListener : PersonListener
{
	void PersonChanged(Person& p, const std::string& property_name, const any new_value) override
	{
		std::cout << "person's " << property_name << " has been changed to ";
		if (property_name == "age")
		{
			std::cout << any_cast<int>(new_value);
		}
		else if (property_name == "can_vote")
		{
			std::cout << any_cast<bool>(new_value);
		}
		std::cout << std::endl;
		
	}
};

// No solution how to solve reentrancy 100%.
struct BadListener : PersonListener
{
	void PersonChanged(Person& p, const std::string& property_name, const any new_value) override
	{
		p.unsubscribe(this);
	}
};

int main()
{
	Person p{ 14 };
	// BadListener cl{};
	ConsoleListener cl{};
	p.subscribe(&cl);
	p.subscribe(&cl);
	p.SetAge(15);
	p.SetAge(16);
	p.unsubscribe(&cl);
	p.SetAge(17);
	
	return 0;
}