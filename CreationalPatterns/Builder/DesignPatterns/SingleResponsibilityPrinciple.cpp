/*
	Single Responsibility Principle
	Divide jobs (like saving of the object) to different classes for different purposes.
*/

#include "includes.h"

// Journal keeps track of journal title and entries only.
struct Journal
{
	std::string title;
	std::vector<std::string> entries;

	Journal(const std::string& title)
		: title{ title }
	{

	}

	void add(const std::string& entry)
	{
		entries.push_back(entry);
	}
};

// PersistenceManager does the saving part/stuff.
struct PersistenceManager
{
	static void save(const Journal& journal, const std::string& filename)
	{
		std::ofstream ofs(filename);
		for (auto& entry : journal.entries)
		{
			ofs << entry << std::endl;
		}
	}
};