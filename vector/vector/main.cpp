
#include <iostream>
#include "vector.hpp"
#pragma warning (disable : 4996)

//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace xf;
using std::cout;
using std::endl;
using std::ends;
class A
{
public:
	A():n(1){}
	A(const A &a) : n(a.n+1)
	{
	}

	void func() const
	{
		cout << "const member function" << endl;
	}
	A& operator = (const A &a)
	{
		n = a.n + 100;
		return *this;
	}
	int n;
};

int main()
{
	{
	vector<A> v;
	A a;
	cout << a.n << endl;
	v.push_back(a);
	v.push_back(a);
	v.push_back(a);
	v.push_back(a);
	cout << v[1].n << endl;
	for(vector<A>::iterator iter = v.begin(); iter != v.end(); ++iter)
	{
		cout << (iter->n) << ends;
	}
	cout << endl;

	vector<A> v2(v);
	for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
	{
		cout << (iter->n) << ends;
	}
	cout << endl;

	vector<A> v3 = v;
	for(vector<A>::iterator iter = v3.begin(); iter != v3.end(); ++iter)
	{
		cout << (iter->n) << ends;
	}
	cout << endl;
	v3.reserve(10);
	v.push_back(a);
	v3 = v;
	for(vector<A>::iterator iter = v3.begin(); iter != v3.end(); ++iter)
	{
		cout << (iter->n) << ends;
	}
	cout << endl;
	}

	{
		vector<int> v(0);
		v.push_back(1);
		v.push_back(2);
		vector<int> v1(v);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		int a[10] = {1,3,5,7,9,2,4,6,8,10};
		vector<int> v2(a, a + 10);
		vector<int> v3 = v2;
    
		for(vector<int>::const_iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			cout << *iter << ' ';
			++iter;
			--iter;
		}
		cout << endl;
		for(vector<int>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			cout << *iter << ' ';
			++iter;
			--iter;
		}
		cout << endl << v.capacity() << endl;
		for(vector<int>::reverse_iterator iter = v.rbegin(); iter != v.rend(); ++iter)
		{
			cout << *iter << ' ';
			++iter;
			--iter;
		}
		cout << endl;
		for(vector<int>::reverse_const_iterator iter = v.rbegin(); iter != v.rend(); ++iter)
		{
			cout << *iter << ' ';
			++iter;
			--iter;
		}
		cout << endl;
		cout << v.max_size() << endl;
		vector<double> vv;
		cout << vv.max_size() << endl;
	}
	return 0;
}
