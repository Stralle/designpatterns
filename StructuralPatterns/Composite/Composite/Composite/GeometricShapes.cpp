#include <iostream>
#include <vector>

struct GraphicObject
{
	virtual void draw() = 0;
};

struct Circle : GraphicObject
{
	void draw() override
	{
		std::cout << "Circle" << std::endl;
	}
};

struct Group : GraphicObject
{
	std::string name;
	std::vector<GraphicObject*> objects;

	Group(const std::string& name)
		:name{ name }
	{
	}

	void draw() override
	{
		std::cout << "Group " << name.c_str() << " contains:" << std::endl;
		/*
			Use auto && for the ability to modify and discard values of the sequence within the loop. 
										(That is, unless the container provides a read-only view, in which case it will be effectively an auto const &.)
			Use auto & to modify the values of the sequence in a meaningful way.
			Use auto const & for read-only access.
			Use auto to work with (modifiable) copies.
			Reference: https://stackoverflow.com/questions/29859796/c-auto-vs-auto
		*/
		for (auto&& obj : objects)
		{
			obj->draw();
		}
	}
};




// Rename this method to main to test this out.
int geometric_main()
{
	Group root("root");
	Circle c1, c2;

	root.objects.push_back(&c1);

	Group subgroup("sub");
	subgroup.objects.push_back(&c2);

	root.objects.push_back(&subgroup);

	root.draw();

	return 0;
}