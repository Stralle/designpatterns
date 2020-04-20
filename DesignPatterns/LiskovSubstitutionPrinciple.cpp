/*
	Liskov Substitution Principle (LSP)

	Objects in a program should be replaceable with instances of their subtypes w/o altering the correctness of the program.
*/
#include "includes.h"

class Rectangle
{
protected:
	int m_width, m_height;
public:
	Rectangle(const int width, const int height)
		: m_width(width), m_height(height)
	{
	}

	virtual inline int GetWidth() const { return this->m_width; }

	virtual inline int GetHeight() const { return this->m_height; }

	virtual inline void SetWidth(const int width) { this->m_width = width; }

	virtual inline void SetHeight(const int height) { this->m_height = height; }

	inline int Area() const { return m_width * m_height; }
};

// Square is actually violating the rule of LSP, becase it alters correctness of the program.
class Square : public Rectangle
{
public:
	Square(int size) : Rectangle(size, size) {}
	void SetWidth(const int width) override
	{
		this->m_width = m_height = width;
	}

	void SetHeight(const int height) override
	{
		this->m_height = m_width = height;
	}
};

void process(Rectangle& rectangle)
{
	int width = rectangle.GetWidth();
	rectangle.SetHeight(10);

	std::cout << "Expect area = " << (width * 10) << ", got " << rectangle.Area() << std::endl;
}

// A violation of LSP can be overcome with factory design pattern.
struct RectangleFactory
{
	static Rectangle CreateRectangle(int w, int h);
	static Rectangle CreateSquare(int size);
};

// Change the method name to main when you want to run the example of this design pattern.
int mainLSP()
{
	Rectangle r{ 5, 5 };
	process(r);

	Square s{ 5 };
	process(s);

	return 0;
}
