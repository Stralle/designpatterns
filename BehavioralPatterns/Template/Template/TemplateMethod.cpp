/*
	Allows us to define the 'skeleton' of the algorithm, with the concrete implementations defined in subclasses.
	Similar to strategy.
*/
#include <iostream>
#include <string>

class Game
{
public:
	explicit Game(int number_of_players)
		: number_of_players(number_of_players)
	{
	}

	// This is a template method. It defines an algorithm at a high level and inheriting the algorithm class providing the specialized implementations.
	void run()
	{
		start();
		while (!have_winner())
		{
			take_turn();
		}
		std::cout << "Player " << get_winner() << " wins.\n";
	}

protected:
	virtual void start() = 0;
	virtual bool have_winner() = 0;
	virtual void take_turn() = 0;
	virtual int get_winner() = 0;
	
protected:
	int current_player{ 0 };
	int number_of_players;
};

class Chess : public Game
{
public:
	explicit Chess()
		: Game{2}
	{
	}
	
protected:

	void start() override
	{
		std::cout << "Starting a game of chess with " << number_of_players << " players." << std::endl;
	}
	
	bool have_winner() override
	{
		return turns == max_turns;
	}
	
	void take_turn() override
	{
		std::cout << "Turn " << turns << " taken by player " << current_player << std::endl;
		turns++;
		current_player = (current_player + 1) % number_of_players;
	}
	
	int get_winner() override
	{
		return current_player;
	}

private:
	int turns{ 0 }, max_turns{ 10 };
};

int main()
{
	Chess chess;
	chess.run();

	return 0;
}