/*
	Interpreter - a component that processes structured text data. Does so by turning it into separate lexical tokens (lexing)
	and then interpreting sequences of said tokens (parsing).
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <memory>
using namespace std;

#include <boost/lexical_cast.hpp>

struct my_token
{
	enum Type { integer, plus, minus, lparen, rparen } type;
	string text;

	my_token(const Type type, const string& text)
		: type(type), text(text)
	{	
	}

	friend ostream& operator<<(ostream& os, const my_token& obj)
	{
		return os << "`" << obj.text << "`";
	}
	
};

struct my_element
{
	virtual ~my_element() = default;
	virtual int eval() const = 0;
};

struct my_integer : my_element
{
	int value;

	explicit my_integer(const int value)
		: value(value)
	{
	}

	int eval() const override
	{
		return value;
	}
};

struct binary_operation : my_element
{
	enum Type { addition, subtraction } type;
	shared_ptr<my_element> lhs, rhs;

	int eval() const override
	{
		if (type == addition)
		{
			return lhs->eval() + rhs->eval();
		}
		return lhs->eval() - rhs->eval();
	}
};

vector<my_token> lex(const string& input)
{
	vector<my_token> result;

	for (int i = 0; i < input.length(); ++i)
	{
		switch(input[i])
		{
		case '+':
			result.push_back(my_token{ my_token::plus, "+" });
			break;
		case '-':
			result.push_back(my_token{ my_token::minus, "-" });
			break;
		case '(':
			result.push_back(my_token{ my_token::lparen, "(" });
			break;
		case ')':
			result.push_back(my_token{ my_token::rparen, ")" });
			break;
		default:
			ostringstream buffer;
			buffer << input[i];
			for (int j = i+1; j < input.size(); ++j)
			{
				if (isdigit(input[j]))
				{
					buffer << input[j];
					++i;
				}
				else
				{
					result.push_back(my_token{ my_token::integer, buffer.str() });
					break;
				}
			}
		}
	}
	
	return result;
}

shared_ptr<my_element> parse(const vector<my_token>& tokens)
{
	auto result = make_shared<binary_operation>();
	bool have_lhs = false;

	for (int i = 0; i < tokens.size(); ++i)
	{
		auto token = tokens[i];
		switch (token.type)
		{
		case my_token::integer:
			{
				int value = boost::lexical_cast<int>(token.text);
				auto integer = make_shared<my_integer>(value);
				if (!have_lhs)
				{
					result->lhs = integer;
					have_lhs = true;
				}
				else
				{
					result->rhs = integer;
				}
			}
			break;
		case my_token::plus:
			result->type = binary_operation::addition;
			break;
		case my_token::minus:
			result->type = binary_operation::subtraction;
			break;
		case my_token::lparen:
			{
				int j = i;
				for(; j < tokens.size(); ++j)
				{
					if (tokens[j].type == my_token::rparen)
					{
						break;
					}
				}
				vector<my_token> subexpression(&tokens[i+1], &tokens[j]);
				auto element = parse(subexpression);
				if (!have_lhs)
				{
					result->lhs = element;
					have_lhs = true;
				}
				else
				{
					result->rhs = element;
				}
				i = j;
				
			}
			break;

		// We don't need this because we'll cover everything in case lparen.
		/*
		case Token::rparen: break;
		default: break;
		*/
		}
	}
	return result;
}

int main()
{
	const string input{ "(13-4)-(12+1)" };
	auto tokens = lex(input);

	for (auto& t: tokens)
	{
		cout << t << "\t";
	}
	cout << endl;

	const auto parsed = parse(tokens);

	cout << input << " = " << parsed->eval() << endl;

	return 0;
}