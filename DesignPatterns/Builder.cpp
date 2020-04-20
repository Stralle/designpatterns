/*
	Builder design pattern
*/

#include "includes.h"

using namespace std;

struct HtmlBuilder;

struct HtmlElement
{
	string name;
	string text;
	vector<HtmlElement> elements;
	const size_t indent_size = 2;

	HtmlElement() { }
	HtmlElement(const string& name, const string& text)
		: name{ name }, text{ text }
	{
	}

	string str(int indent = 0) const
	{
		ostringstream oss;
		string i(indent_size * indent, ' ');

		oss << i << "<" << name << ">" << endl;

		if (text.size() > 0)
		{
			oss << string(indent_size * (indent + 1), ' ') << text << endl;
		}

		for (const auto& e : elements)
		{
			oss << e.str(indent + 1);
		}

		oss << i << "</" << name << ">" << endl;
		return oss.str();
	}

	static HtmlBuilder build(string root_name);
	static unique_ptr<HtmlBuilder> create(string root_name);
};

struct HtmlBuilder
{
	HtmlBuilder(string root_name)
	{
		root.name = root_name;
	}

	HtmlBuilder& add_child(string child_name, string child_text) // Returning a reference so we can stack up adding a children. That's not possible with void.
	{
		HtmlElement e{ child_name, child_text };
		root.elements.emplace_back(e);
		return *this;
	}

	HtmlBuilder* add_child_ptr(string child_name, string child_text) // Returning a reference so we can stack up adding a children. That's not possible with void.
	{
		HtmlElement e{ child_name, child_text };
		root.elements.emplace_back(e);
		return this;
	}

	string str() const
	{
		return root.str();
	}

	operator HtmlElement() // Element automatically converted from HtmlBuilder to HtmlElement.
	{
		return root;
	}

	HtmlElement root;
};

inline HtmlBuilder HtmlElement::build(string root_name)
{
	return HtmlBuilder{ root_name };
}

unique_ptr<HtmlBuilder> HtmlElement::create(string root_name)
{
	return make_unique<HtmlBuilder>(root_name);
}

// Rename this method to main when you want to test this design pattern.
int mainBuilder()
{
	HtmlBuilder builder{ "ul" };
	builder.add_child("li", "hello")
		.add_child("li", "world");
	
	HtmlElement elementBuilderReference = HtmlElement::build("ul").add_child("li", "hello");

	HtmlElement elementBuilderPointer = *(HtmlElement::create("ul")->add_child_ptr("li", "hello")->add_child_ptr("li", "world"));
	
	cout << builder.str() << endl;
	cout << elementBuilderReference.str() << endl;
	cout << elementBuilderPointer.str() << endl;

	//getchar();
	return 0;
}

