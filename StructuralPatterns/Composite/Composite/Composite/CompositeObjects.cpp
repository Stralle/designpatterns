/*
	Composite - a mechanism for treating individual (scalar) and compositions of objects in a uniform manner.

	Composition lets us make compound objects.

	e.g.
		Mathematical expression is composed of simpler expressions.
		Grouping of shapes that make up several shapes.

	Composite design pattern is used to treat both single and composite objects uniformly (e.g. with identical APIs)
*/

#include <cstdio>
#include <memory>
#include <iostream>
#include <vector>

using namespace std;

//#include <boost/accumulators/accumulators.hpp>
//#include <boost/accumulators/statistics.hpp>
//
//using namespace boost::accumulators;

// 2 + (3 + 4)
struct Expression
{
	virtual double eval() = 0;
	virtual void collect(vector<double>& v) = 0;
};

struct Literal : Expression
{
	double value;

	explicit Literal(const double value)
		: value(value)
	{
	}

	double eval() override
	{
		return value;
	}

	void collect(vector<double>& v) override
	{
		v.push_back(value);
	}
};

struct AdditionExpression : Expression
{
	shared_ptr<Expression> left, right;
	
	AdditionExpression(const shared_ptr<Expression>& left, const shared_ptr<Expression>& right)
		: left(left), right(right)
	{
	}

	double eval() override
	{
		return left->eval() + right->eval();
	}

	void collect(vector<double>& v) override
	{
		left->collect(v);
		right->collect(v);
	}

};

// Rename this method to main to test this out.
int composite_main(int ac, char* av)
{
	AdditionExpression sum{
		make_shared<Literal>(2),
		make_shared<AdditionExpression>(
			make_shared<Literal>(3),
			make_shared<Literal>(4)
			)
	};
	cout << "2+(3+4) = " << sum.eval() << endl;

	vector<double> v;
	sum.collect(v);
	for (auto x : v)
		cout << x << "\t";
	cout << endl;

	// Vector example of composition.
	vector<double> values{ 1,2,3,4 };
	double s = 0;
	for (auto x : values)
		s += x;
	cout << "average is " << (s / values.size()) << endl;

	// Boost example of composition.
	/*accumulator_set<double, stats<tag::mean>> acc;
	for (auto x : values)
		acc(x);
	cout << "average is " << mean(acc) << endl;*/

	return 0;
}