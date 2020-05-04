/*

	Open-Closed-Principle:
	Open for extension and closed for modification.

*/

#include "includes.h"

enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

struct Product
{
	std::string name;
	Color color;
	Size size;
};

struct ProductFilter
{
	typedef std::vector<Product*> Items;
	static Items by_color(Items items, Color color)
	{
		Items result;
		for (auto& item : items)
		{
			if (item->color == color)
			{
				result.push_back(item);
			}
		}
		return result;
	}

	static Items by_color_and_size(Items items, Size size, Color color)
	{
		Items result;
		for (auto& item : items)
		{
			if (item->size == size && item->color == color)
			{
				result.push_back(item);
			}
		}
		return result;
	}
};


// Specification Pattern - not a gang of four pattern, but commonly used.

template <typename T> struct ISpecification
{
	virtual bool is_satisfied(T* item) = 0;
};

template <typename T> struct IFilter
{
	virtual std::vector<T*> filter(std::vector<T*> items, ISpecification<T>& specification) = 0;
};

struct BetterFilter : IFilter<Product>
{
	typedef std::vector<Product*> Items;
	std::vector<Product*> filter(std::vector<Product*> items, ISpecification<Product>& specification) override
	{
		Items result;

		for (auto& product : items)
		{
			if (specification.is_satisfied(product))
			{
				result.push_back(product);
			}
		}
		return result;
	}

};

struct ColorSpecification : ISpecification<Product>
{
	Color color;

	ColorSpecification(const Color color)
		: color(color)
	{

	}

	bool is_satisfied(Product* item) override
	{
		return item->color == color;
	}

};

struct SizeSpecification : ISpecification<Product>
{
	Size size;

	SizeSpecification(const Size size)
		: size(size)
	{

	}

	bool is_satisfied(Product* item) override
	{
		return item->size == size;
	}

};

template <typename T> struct AndSpecification : ISpecification<T>
{
	ISpecification<T>& first;
	ISpecification<T>& second;

	AndSpecification(ISpecification<T>& first, ISpecification<T>& second)
		: first(first), second(second)
	{

	}

	bool is_satisfied(T* item) override
	{
		return first.is_satisfied(item) && second.is_satisfied(item);
	}

};

// Change the method name to main when you want to run the example of this design pattern.
int mainOCP()
{
	Product apple { "Apple", Color::Green, Size::Small };
	Product tree { "Tree", Color::Green, Size::Large };
	Product pink_lady { "Pink Lady", Color::Red, Size::Small };
	Product house { "House", Color::Blue, Size::Large };

	std::vector<Product*> all{ &apple, &tree, &pink_lady, &house };

	BetterFilter better_filter;
	ColorSpecification green{ Color::Green };

	auto green_things = better_filter.filter(all, green);

	for (auto& x : green_things)
	{
		std::cout << x->name << " is green." << std::endl;
	}

	SizeSpecification large{ Size::Large };
	AndSpecification<Product> green_and_large{ large, green };

	auto green_and_large_things = better_filter.filter(all, green);

	for (auto& x : green_and_large_things)
	{
		std::cout << x->name << " is green and large." << std::endl;
	}

	return 0;
}


