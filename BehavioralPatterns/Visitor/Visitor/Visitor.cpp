/*
	Visitor is a pattern where a component (visitor) is allowed to traverse the entire inheritance hierarchy.
	Implemented by propagating a single visit() function through the entire hierarchy.

	Dispatch
	Which function to call?

	Single dispatch: depends on name of request and type of receiver.
	Double dispatch: depends on name of request and type of two receivers. (type of visitor, type of element being visited)
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#include "Model.hpp"
#include "Visitor.hpp"

struct HtmlVisitor : Visitor
{
	void visit(const Paragraph& p) override
	{
		oss << "<p>" << p.text << "</p>\n";
	}

	void visit(const ListItem& p) override
	{
		oss << "<li>" << p.text << "</li>\n";
	}

	void visit(const List& p) override
	{
		oss << "<ul>\n";

		for (auto x: p)
		{
			x.accept(*this); // ACCEPT! NOT visit.
		}
		
		oss << "</ul>\n";
	}

	std::string str() const override
	{
		return oss.str();
	}

private:
	std::ostringstream oss;
};

// Rename this to main for testing purposes.
int mainDoubleDispatch()
{
	Paragraph p{ "Here are some colors" };
	ListItem red{ "red" };
	ListItem green{ "green" };
	ListItem blue{ "blue" };
	List colors{ red, green, blue };

	std::vector<Element*> document{ &p, &colors };
	HtmlVisitor v;

	for (auto x : document)
	{
		x->accept(v);
	}

	std::cout << v.str() << std::endl;
	
	return 0;
}