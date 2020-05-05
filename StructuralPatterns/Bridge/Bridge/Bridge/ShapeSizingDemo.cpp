#include <iostream>

// This abstract renderer is a bridge between concrete renderers and shapes.
struct Renderer
{
	virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRenderer : Renderer
{
	void render_circle(float x, float y, float radius) override
	{
		std::cout << "Drawing a vector circle of radius " << radius << std::endl;
	}
};

struct RasterRenderer : Renderer
{
	void render_circle(float x, float y, float radius) override
	{
		std::cout << "Rasterizing a circle of radius " << radius << std::endl;
	}
};

// This abstract shape is a bridge between concrete shapes and renderers.
struct Shape
{
protected:
	Renderer& renderer;
	Shape(Renderer& renderer)
		: renderer{ renderer } 
	{
	}

public:
	virtual void draw() = 0;
	virtual void resize(float factor) = 0;
};

struct Circle : Shape
{
	float x, y, radius;

	void draw() override
	{
		renderer.render_circle(x, y, radius);
	}

	void resize(float factor) override
	{
		radius *= factor;
	}

	Circle(Renderer& renderer, const float x, const float y, const float radius)
		: Shape{ renderer },
		x{ x },
		y{ y },
		radius{ radius }
	{
	}
};


// Shape Sizing Demo. Rename this method to main to test it out.
int main()
{
	RasterRenderer rr;
	Circle raster_circle{ rr, 10, 10, 5 };
	raster_circle.draw();
	raster_circle.resize(2);
	raster_circle.draw();

	return 0;
}