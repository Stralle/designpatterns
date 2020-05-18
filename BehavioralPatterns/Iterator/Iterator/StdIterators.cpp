/*
	Iterator - an object that facilitates the traversal of a data structure.

*/

#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

void std_iterators()
{
	vector<string> names{ "John", "Jane", "Jill", "Jack" };
	vector<string>::iterator it = names.begin();
	cout << "First name is " << *it << endl;
	++it;
	it->append(" Johnson");
	cout << "Second name is " << *it << endl;
	while (++it != names.end())
	{
		cout << "Another name " << *it << endl;
	}

	for (auto ri = rbegin(names); ri != rend(names); ++ri)
	{
		cout << *ri;
		if (ri + 1 != rend(names))
		{
			cout << ", ";
		}
	}
	cout << endl;

	// jack can't be const_reverse_iterator if we want to modify it, but this is just a showcase that there're reverse iterators
	//vector<string>::const_reverse_iterator jack = crbegin(names);
	//*jack += " Reacher";
}

// Rename this to main for testing purposes.
int stdIterators_main()
{
	std_iterators();

	return 0;
}