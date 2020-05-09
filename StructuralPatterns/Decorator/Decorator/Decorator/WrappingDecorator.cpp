
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

struct Shape
{
	virtual string str() const = 0;
};

struct Circle : Shape
{
	float radius = 3.f;

	Circle()
	{ 
	}

	explicit Circle(const float radius)
		: radius(radius)
	{
	}

	void resize(float factor)
	{
		radius *= factor;
	}

	string str() const override
	{
		ostringstream oss;
		oss << "A circle of radius = " << radius;
		return oss.str();
	}

};

struct Square : Shape
{
	float side;

	explicit Square(const float side)
		: side(side)
	{
	}

	string str() const override
	{
		ostringstream oss;
		oss << "A square with side = " << side;
		return oss.str();
	}
};

struct ColoredShape : Shape // This is a decorator of a Shape. Do we have to inherit from Shape when we contain a reference to a shape?
{
	Shape& shape;
	string color;

	ColoredShape(Shape& shape, const string& color)
		: shape(shape), color(color)
	{
	}

	string str() const override
	{
		ostringstream oss;
		oss << shape.str() << " has the color " << color;
		return oss.str();
	}
};

struct TransparentShape : Shape // A decorator of a Shape.
{
	Shape& shape;
	uint8_t transparency;

	TransparentShape(Shape& shape, const uint8_t transparency)
		: shape(shape), transparency(transparency)
	{
	}

	string str() const override
	{
		ostringstream oss;
		oss << shape.str() << " has " 
			<< static_cast<float>(transparency) / 255.f * 100.f << " % transparency." << endl;
		return oss.str();
	}
};

// Mixin Inheritance decorator
template <typename T> struct ColoredShape2 : T
{
	static_assert(is_base_of<Shape, T>::value,
		"Template must be of a type Shape");

	string color;

	ColoredShape2()
	{
	}

	explicit ColoredShape2(const string& color)
		: color(color)
	{
	}

	string str() const override
	{
		ostringstream oss;
		oss << T::str() << " has the color " << color;
		return oss.str();
	}

};

template <typename T> struct TransparentShape2 : T
{
	uint8_t transparency;

	template <typename... Args>
	TransparentShape2(const uint8_t transparency, Args ...args)
		: T(args...), transparency(transparency) // Problem: there's no help about what arguments should we include...
	{
	}

	string str() const override
	{
		ostringstream oss;
		oss << T::str() << " has " 
			<< static_cast<float>(transparency) / 255.f * 100.f 
			<< " % transparency." << endl;
		return oss.str();
	}

};

// Rename this method for testing purposes
int main()
{
	// Basic decorators.
	/*Circle circle{ 5 };
	cout << circle.str() << endl;

	ColoredShape redCircle{ circle, "red" };
	cout << redCircle.str() << endl;

	TransparentShape half_transparent_circle{ circle, 128 };
	cout << half_transparent_circle.str() << endl;

	TransparentShape half_tr_red_circle{ redCircle, 128 };
	cout << half_tr_red_circle.str() << endl;
	*/

	// Mixin decorators. We have to have default contructors
	/*ColoredShape2<Circle> red_circle{ "red" };
	red_circle.radius = 5;
	cout << red_circle.str() << endl;

	TransparentShape2<ColoredShape2<Circle>> red_half_transparent_circle{ 127 };
	red_half_transparent_circle.color = "red";
	red_half_transparent_circle.color = 100;
	cout << red_half_transparent_circle.str() << endl;
	*/

	// This is legal unles we add static_assert check whether the T is a shape.
	/*struct NotAShape
	{
		virtual string str() const 
		{
			return string{};
		}
	};

	ColoredShape2<NotAShape> legal;
	*/

	TransparentShape2<Square> hidden_square{ 0,15 };
	cout << hidden_square.str() << endl;

	return 0;
}