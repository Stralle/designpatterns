/*
	Strategy - enables the exact behavior of a system to be selected at either run-time (dynamic) or compile-time (static).
	Also known as a policy.

*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

enum class OutputFormat
{
	Markdown,
	HTML
};

struct list_strategy
{
	virtual ~list_strategy() = default;
	virtual void start(std::ostringstream& oss) = 0;
	virtual void end(std::ostringstream& oss) = 0;
	virtual void add_list_item(std::ostringstream& oss, const std::string& item) = 0;
};

struct markdown_list_strategy : list_strategy
{
	void start(std::ostringstream& oss) override
	{
		
	}
	
	void end(std::ostringstream& oss) override
	{
		
	}
	
	void add_list_item(std::ostringstream& oss, const std::string& item) override
	{
		oss << " * " << item << std::endl;
	}
};

struct html_list_strategy : list_strategy
{
	void start(std::ostringstream& oss) override
	{
		oss << "<ul>" << std::endl;
	}
	void end(std::ostringstream& oss) override
	{
		oss << "</ul>" << std::endl;
	}
	
	void add_list_item(std::ostringstream& oss, const std::string& item) override
	{
		oss << "<li> " << item << " </li>" << std::endl;
	}
};

struct dynamic_text_processor
{
	void clear()
	{
		oss.str("");
		oss.clear();
	}

	std::string str() const { return oss.str(); }
	
	void append_list(const std::vector<std::string> items)
	{
		list_strategy->start(oss);
		for (auto& item: items)
		{
			list_strategy->add_list_item(oss, item);
		}
		list_strategy->end(oss);
	}

	void set_output_format(OutputFormat format)
	{
		switch (format)
		{
		case OutputFormat::Markdown:
			list_strategy = std::make_unique<markdown_list_strategy>();
			break;
		case OutputFormat::HTML:
			list_strategy = std::make_unique<html_list_strategy>();
			break;
		default:
			// Nothing to be done
			break;
		}
	}
	
private:
	std::ostringstream oss;
	std::unique_ptr<list_strategy> list_strategy;
};

template <typename LS> // LS - list strategy
struct static_text_processor
{
	static_text_processor()
		: list_strategy(std::make_unique<LS>())
	{
		
	}
	
	void clear()
	{
		oss.str("");
		oss.clear();
	}

	std::string str() const { return oss.str(); }

	void append_list(const std::vector<std::string> items)
	{
		list_strategy->start(oss);
		for (auto& item : items)
		{
			list_strategy->add_list_item(oss, item);
		}
		list_strategy->end(oss);
	}

private:
	std::ostringstream oss;
	std::unique_ptr<LS> list_strategy;
};

int main()
{
	// This is an example of dynamic strategy pattern.
	// It's dynamic because in the run-time is defined what strategy we will use (Markdown format or HTML format).
	
	dynamic_text_processor tp;
	tp.set_output_format(OutputFormat::Markdown);
	tp.append_list({ "foo", "bar", "baz" });
	std::cout << tp.str() << std::endl;

	tp.clear();
	
	tp.set_output_format(OutputFormat::HTML);
	tp.append_list({ "abc", "xyz", "qaz", "qwerty" });
	std::cout << tp.str() << std::endl;
	
	std::cout << "-------------" << std::endl;
	// This is an example of static strategy pattern.
	// It's static because it's compile-time defined what strategy we will use.
	
	static_text_processor<markdown_list_strategy> tpm;
	tpm.append_list({ "foo", "bar", "baz" });
	std::cout << tpm.str() << std::endl;
	tpm.clear();

	static_text_processor<html_list_strategy> tph;
	tph.append_list({ "foo", "bar", "baz" });
	std::cout << tph.str() << std::endl;
	tph.clear();
	
	return 0;
}