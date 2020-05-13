/*
	Proxy - A class that is functioning as an interface to a particular resource.
	That resource may be remote, expensive to construct, or may require logging or some other added functionality.

	A difference between Proxy and Decorator is that proxy provides an identical interface; decorator provides an enhanced interface.
	Also, decorator typically aggregates (or has a reference to) what it is decorating; proxy doesn't have to.
	Proxy might not even be working with a materialized object.
*/

#include <cstdio>
#include <iostream>
#include <memory>
#include <ostream>

using namespace std;

struct BankAccount
{
	virtual ~BankAccount() = default;
	virtual void deposit(int amount) = 0;
	virtual void withdraw(int amount) = 0;
};

struct CurrentAccount : BankAccount
{
	explicit CurrentAccount(const int balance)
		: balance(balance)
	{
		
	}

	void deposit(int amount) override
	{
		balance += amount;
	}

	void withdraw(int amount) override
	{
		if (balance >= amount)
		{
			balance -= amount;
		}
	}

	friend ostream& operator<<(ostream& os, const CurrentAccount obj)
	{
		return os
			<< "Balance: " << obj.balance;
	}

private:
	int balance;
};

/*
 * Standard Library Smart Pointers are a good example of a proxy.
 * They have all of the functionalities as a pointer and overrides the operations and everything.
 * You can put * in front of them or use them without it and similar + they handle memory and stuff as an extension to usual pointers.
 */
void smart_pointers()
{
	BankAccount* a = new CurrentAccount{ 123 };
	a->deposit(321);
	delete a;

	shared_ptr<CurrentAccount> b = make_shared<CurrentAccount>(123);
	b->deposit(321);

	CurrentAccount* underlying = b.get();

	cout << *b << endl;
}

// Virtual Proxy
struct Image
{
	virtual ~Image() = default;
	virtual void draw() = 0;
};

struct Bitmap : Image
{
	Bitmap(const string& filename)
	{
		cout << "Loading a file from " << filename << endl;
	}
	
	void draw() override
	{
		cout << "Drawing image" << endl;
	}
};

// Lazy Bitmap is a proxy to a bitmap. It has the same functionality it just doesn't load the image on the beginning so it's better for memory management.
struct LazyBitmap : Image
{
	LazyBitmap(const string& filename)
		: bmp{ nullptr }, filename(filename)
	{
		
	}

	void draw() override
	{
		if (!bmp)
		{
			bmp = new Bitmap{ filename };
		}
		bmp->draw();
	}

	~LazyBitmap()
	{
		delete bmp;
	}
private:
	Bitmap* bmp;
	string filename;
};

void draw_image(Image& img)
{
	cout << "About to draw the image" << endl;
	img.draw();
	cout << "Done drawing an image" << endl;
}

void virtual_proxy()
{
	LazyBitmap bmp{ "pokemon.png" };
	draw_image(bmp);
	draw_image(bmp);
}

// Rename this to main to test it out.
int proxy_main()
{
	// smart_pointers();

	virtual_proxy();
	
	return 0;
}
