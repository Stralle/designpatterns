/*
	Command - an object which represents an instruction to perform a particular action. Contains all information necessary for the action to be taken.
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct BankAccount
{
	int balance = 0;
	int overdraft_limit = -500;

	void deposit(int amount)
	{
		balance += amount;
		cout << "deposited " << amount << ", balance now " << balance << "\n";
	}

	void withdraw(int amount)
	{
		if (balance - amount >= overdraft_limit)
		{
			balance -= amount;
			cout << "withdrew " << amount << ", balance now " << balance << "\n";
		}
	}
};

struct ICommand
{
	virtual ~ICommand() = default;
	virtual void call() const = 0;
	virtual void undo() const = 0;
};

struct Command : ICommand
{
	BankAccount& account;
	enum Action { deposit, withdraw } action;
	int amount;

	Command(BankAccount& account, Action action, int amount)
		: account(account),
		  action(action),
		  amount(amount)
	{
	}

	void call() const override
	{
		switch (action)
		{
		case deposit:
			account.deposit(amount);
			break;
		case withdraw:
			account.withdraw(amount);
			break;
		default:
			;
		}
	}

	void undo() const override
	{
		switch (action)
		{
		case withdraw:
			account.deposit(amount);
			break;
		case deposit:
			account.withdraw(amount);
			break;
		default:
			;
		}
	}
};

struct CommandList : vector<Command>, ICommand
{
	CommandList(const initializer_list<Command>& _Ilist)
		: vector<Command>(_Ilist)
	{
	}

	void call() const override
	{
		for (const auto& cmd: *this)
		{
			cmd.call();
		}
	}
	
	void undo() const override
	{
		for_each(rbegin(), rend(),
			[](const Command& cmd)
		{
			cmd.undo();
		});
		
	}
};

int main()
{
	BankAccount ba;

	// First without CommandList and ICommand
	/*vector<Command> commands{
		Command{ba, Command::deposit, 100},
		Command{ba, Command::withdraw, 200}
	};

	cout << ba.balance << endl;
	
	for (auto& cmd: commands)
	{
		cmd.call();
	}

	cout << ba.balance << endl;

	for_each(commands.rbegin(), commands.rend(),
		[](const Command& cmd)
		{
			cmd.undo();
		});

	cout << ba.balance << endl;
	*/
	
	// Now with CommandList and ICommand
	CommandList commands {
		Command{ba, Command::deposit, 100},
		Command{ba, Command::withdraw, 200}
	};

	cout << ba.balance << endl;

	commands.call();

	cout << ba.balance << endl;

	commands.undo();

	cout << ba.balance << endl;
	
	return 0;
}