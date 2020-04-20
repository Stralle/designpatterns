/*
	Interface Segregation Principle

	No client should be forced to depend on methods it does not use.
*/

#include "includes.h"

struct Document;

// This below is monolithic beast. Therefore you force to implement all these methods, even though you do not need them all.
//struct IMachine
//{
//	virtual void print(std::vector<Document*> docs) = 0;
//	virtual void scan(std::vector<Document*> docs) = 0;
//	virtual void fax(std::vector<Document*> docs) = 0;
//};
//
//
//struct MultiFunctionalPeripheral : IMachine
//{
//	void print(std::vector<Document*> docs) override
//	{
//
//	}
//
//	void scan(std::vector<Document*> docs) override
//	{
//
//	}
//
//	void fax(std::vector<Document*> docs) override
//	{
//
//	}
//};

// Better to do, since people can selectively implement them.

struct IPrinter
{
	virtual void print(std::vector<Document*> docs) = 0;
};

struct IScanner
{
	virtual void scan(std::vector<Document*> docs) = 0;
};

struct IFaxer
{
	virtual void fax(std::vector<Document*> docs) = 0;
};

struct Printer : IPrinter
{
	void print(std::vector<Document*> docs) override
	{
	}

};

struct Scanner : IScanner
{
	void scan(std::vector<Document*> docs) override 
	{
	}

};

struct IMachine : IPrinter, IScanner { };

struct Machine : IMachine
{

	IPrinter& printer;
	IScanner& scanner; 

	Machine(IPrinter& printer, IScanner& scanner)
		: printer(printer), scanner(scanner)
	{
	}

	void print(std::vector<Document*> docs) override
	{
		printer.print(docs);
	}

	void scan(std::vector<Document*> docs) override
	{
		scanner.scan(docs);
	}
};






