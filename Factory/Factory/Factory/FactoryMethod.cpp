#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

class Point
{
	Point(const float x, const float y)
		: x{ x }, y{ y }
	{
	}

public:
	float x, y;

	static Point NewCartesian(const float x, const float y)
	{
		return { x, y }; // Returns initializer list that autocompletes the creation of point object.
	}

	static Point NewPolar(const float r, const float theta)
	{
		return { r*cos(theta), r*sin(theta) }; // Returns initializer list that autocompletes the creation of point object.
	}

	friend std::ostream& operator<<(std::ostream& os, const Point& obj)
	{
		return os
			<< "x: " << obj.x 
			<< " " <<
			<< "y: " << obj.y;
	}

};

int main()
{
	// Point p{1, 2} ;

	auto cartesianPoint = Point::NewCartesian(1, 2);
	std::cout << cartesianPoint << std::endl;

	auto polarPoint = Point::NewPolar(5, M_PI_4);
	std::cout << polarPoint << std::endl;

	//getchar();
	return 0;
}