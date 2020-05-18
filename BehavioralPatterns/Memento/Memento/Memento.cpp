/*
	Memento - a token/handle representing the system state.
	Lets us roll back to the state when the token was generated.
	That token may or may not directly expose state information.
*/

#include <iostream>
#include <memory>
#include <memory>
#include <string>
#include <vector>

class Memento
{
	int balance;
public:

	Memento(int balance)
		: balance(balance)
	{
	}

	friend class BankAccount;
	friend class BankAccount2;
	
};

class BankAccount
{
	int balance = 0;
public:

	explicit BankAccount(const int balance)
		: balance(balance)
	{
	}

	void restore(const Memento& m)
	{
		balance = m.balance;
	}

	Memento deposit(int amount)
	{
		balance += amount;
		return { balance };
	}

	friend std::ostream& operator<<(std::ostream& os, const BankAccount& obj)
	{
		return os << "balance: " << obj.balance;
	}
};

class BankAccount2
{
	int balance = 0;
	std::vector<std::shared_ptr<Memento>> changes;
	int current;
	
public:

	explicit BankAccount2(const int balance)
		: balance(balance)
	{
		changes.emplace_back(std::make_shared<Memento>(balance));
		current = 0;
	}

	void restore(const std::shared_ptr<Memento>& m)
	{
		if (m)
		{
			balance = m->balance;
			changes.push_back(m);
			current = changes.size() - 1;
		}
	}

	std::shared_ptr<Memento> deposit(int amount)
	{
		balance += amount;
		auto m = std::make_shared<Memento>(balance);
		changes.push_back(m);
		++current;
		return m;
	}

	std::shared_ptr<Memento> undo()
	{
		if (current > 0)
		{
			--current;
			auto m = changes[current];
			balance = m->balance;
			// return m;
			// Should I return M here?
		}
		return {};
	}

	std::shared_ptr<Memento> redo()
	{
		if (current + 1 < changes.size())
		{
			++current;
			auto m = changes[current];
			balance = m->balance;
			// return m;
			// Should I return M here?
		}
		return {};
	}

	friend std::ostream& operator<<(std::ostream& os, const BankAccount2& obj)
	{
		return os << "balance: " << obj.balance;
	}
};


// Basic memento example.
void basic_memento()
{
	BankAccount ba{ 100 };
	auto m1 = ba.deposit(50); // 150
	auto m2 = ba.deposit(25); // 175

	std::cout << ba << std::endl;

	// undo to m1
	ba.restore(m1);
	std::cout << ba << std::endl;

	// undo to m2
	ba.restore(m2);
	std::cout << ba << std::endl;
}

void undo_redo()
{
	BankAccount2 ba{ 100 };
	ba.deposit(50); // 150
	ba.deposit(25); // 175

	std::cout << ba << std::endl;

	ba.undo();
	std::cout << "Undo 1: " << ba << std::endl;

	ba.undo();
	std::cout << "Undo 2: " << ba << std::endl;

	ba.redo();
	std::cout << "Redo 2: " << ba << std::endl;
}

int main()
{
	//basic_memento();
	undo_redo();
	
	return 0;
}
