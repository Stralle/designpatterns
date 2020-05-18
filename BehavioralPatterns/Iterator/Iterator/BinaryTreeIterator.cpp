#include <cstdio>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

template <typename T> struct binary_tree;

template <typename T> struct node
{
	T value = T();
	node<T>* left = nullptr;
	node<T>* right = nullptr;
	node<T>* parent = nullptr;
	binary_tree<T>* tree = nullptr;

	explicit node(const T& value)
		: value(value)
	{
	}

	~node()
	{
		if (left)
			delete left;
		if (right)
			delete right;
	}

	node(const T& value, node<T>* const left, node<T>* const right)
		: value(value), left(left), right(right)
	{
		this->left->parent = this->right->parent = this;
	}

	void set_tree(binary_tree<T>* t)
	{
		tree = t;
		if (left)
			left->set_tree(t);
		if (right)
			right->set_tree(t);
	}
	
};

template <typename T> struct binary_tree
{
	node<T>* root = nullptr;

	template <typename U>
	struct binary_tree_iterator
	{
		node<U>* current;

		explicit binary_tree_iterator(node<U>* current)
			: current(current)
		{
		}

		bool operator!=(const binary_tree_iterator<U>& other)
		{
			return current != other.current;
		}

		node<U>& operator*()
		{
			return *current;
		}

		binary_tree_iterator<U>& operator++()
		{
			if (current->right)
			{
				current = current->right;
				while (current->left)
				{
					current = current->left;
				}
			}
			else
			{
				node<T>* p = current->parent;
				while (p && current == p->right)
				{
					current = p;
					p = p->parent;
				}
				current = p;
			}
			return *this;
		}
		
	};
	typedef binary_tree_iterator<T> iterator;
	
	explicit binary_tree(node<T>* const root)
		: root(root)
	{
		root->set_tree(this);
	}

	~binary_tree()
	{
		if (root)
			delete root;
	}

	iterator end()
	{
		return iterator{ nullptr };
	}

	iterator begin()
	{
		node<T>* n = root;
		if (n)
		{
			while (n->left)
			{
				n = n->left;
			}
		}
		return iterator{ n };
	}
};

int main()
{
	binary_tree<string> family {
		new node<string> { "me",
			new node<string>{"mother",
				new node<string>{"mother's mother"},
				new node<string>{"mother's father"}
			},
			new node<string>{"father"}
		}
	};

	for (auto it = family.begin(); it != family.end(); ++it)
	{
		cout << (*it).value << endl;
	}
	
	return 0;
}