#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag(){}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& b) : tree_bag(b) {}
searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& b)
{
	tree_bag::operator=(b);
	return *this;
}
searchable_tree_bag::~searchable_tree_bag(){}

bool searchable_tree_bag::has(int x) const
{
	node *n = tree;
	while(n)
	{
		if (x == n->value)
			return true;
		if (x < n->value)
			n = n->l;
		else
			n = n->r;
	}
	return false;
}
