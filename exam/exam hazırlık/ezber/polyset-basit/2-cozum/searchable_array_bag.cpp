#include "searchable_array_bag.hpp"

// OCF: isi array_bag yapar
searchable_array_bag::searchable_array_bag() {}
searchable_array_bag::searchable_array_bag(const searchable_array_bag& o) : array_bag(o) {}
searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag& o)
{
	array_bag::operator=(o);
	return *this;
}
searchable_array_bag::~searchable_array_bag() {}

// dizide bastan sona ara
bool searchable_array_bag::has(int x) const
{
	for (int i = 0; i < size; i++)
		if (data[i] == x)
			return true;
	return false;
}
