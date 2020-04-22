#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

class Point
{
	Point(const float x, const float y)
		: x{ x }, y{ y }
	{
	}

	class PointFactory // Internal factory, because does it really make sense to have a pointfactory if we don't have point?
	{
	public:
		static Point NewCartesian(const float x, const float y)
		{
			return { x, y }; // Returns initializer list that autocompletes the creation of point object.
		}

		static Point NewPolar(const float r, const float theta)
		{
			return { r * cos(theta), r * sin(theta) }; // Returns initializer list that autocompletes the creation of point object.
		}
	};

public:
	float x, y;

	friend std::ostream& operator<<(std::ostream& os, const Point& obj)
	{
		return os
			<< "x: " << obj.x 
			<< " "
			<< "y: " << obj.y;
	}

	static PointFactory Factory;
};

// Rename this method to main to test this out.
int mainFactoryMethod()
{
	auto p = Point::Factory.NewCartesian(1, 2);
	std::cout << p << std::endl;

	//getchar();
	return 0;
}