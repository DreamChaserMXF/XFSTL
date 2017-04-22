#ifndef XF_TEST_H
#define XF_TEST_H

static bool lessthan_func(const int &lhs, const int &rhs)
{
	return lhs < rhs;
}
static bool largerthan_func(const int &lhs, const int &rhs)
{
	return lhs > rhs;
}

class less_than_class
{
public:
	bool operator () (int a, int b) const
	{
		return a < b;
	}
};

class larger_than_class
{
public:
	bool operator () (int a, int b) const
	{
		return a > b;
	}
};

class NoDefaultConstructorClass
{
public:
	NoDefaultConstructorClass(int n){}
};

#endif