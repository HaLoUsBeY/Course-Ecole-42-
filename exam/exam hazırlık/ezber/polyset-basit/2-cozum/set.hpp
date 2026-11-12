#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set
{
private:
	searchable_bag* bag;           // disaridan gelen bag (delete etmiyoruz)

public:
	set();
	set(searchable_bag& b);
	set(const set& o);
	set& operator=(const set& o);
	~set();

	void insert(int x);
	void insert(int* arr, int n);
	bool has(int x) const;
	void print() const;
	void clear();
	searchable_bag& get_bag();
};

#endif
