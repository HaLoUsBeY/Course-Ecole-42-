#include "set.hpp"
#include <cstddef>

// OCF: sadece isaretciyi kopyala
set::set() : bag(NULL) {}
set::set(searchable_bag& b) : bag(&b) {}
set::set(const set& o) : bag(o.bag) {}
set& set::operator=(const set& o) { bag = o.bag; return *this; }
set::~set() {}

// set = ayni sayi iki kez girmez
void set::insert(int x)
{
	if (!bag->has(x))
		bag->insert(x);
}
void set::insert(int* arr, int n)
{
	for (int i = 0; i < n; i++)
		insert(arr[i]);
}

// gerisi bag'e yonlendir
bool set::has(int x) const { return bag->has(x); }
void set::print() const { bag->print(); }
void set::clear() { bag->clear(); }
searchable_bag& set::get_bag() { return *bag; }
