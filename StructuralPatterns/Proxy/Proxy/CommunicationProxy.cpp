#include <cstdio>
#include <ostream>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

struct Pingable
{
	virtual ~Pingable() = default;
	virtual wstring ping(const wstring& message) = 0;
};

struct Pong : Pingable
{
	wstring ping(const wstring& message) override
	{
		return message + L" pong";
	}
};

void tryit(Pingable& p)
{
	wcout << p.ping(L"ping") << "\t";
}

int main()
{
	Pong pp;
	for (size_t i = 0; i < 10; ++i)
	{
		tryit(pp);
	}
	
	return 0;
}