#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() {}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& o)
	: bag(o), tree_bag(o), searchable_bag(o) {}
searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& o)
{
	tree_bag::operator=(o);
	return *this;
}
searchable_tree_bag::~searchable_tree_bag() {}

/* BST: kucukse sola, buyukse saga */
bool searchable_tree_bag::has(int x) const
{
	node* n = tree;
	while (n)
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
