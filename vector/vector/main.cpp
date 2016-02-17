
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
	// assign, front, back, push, pop, clear
	vector<int> v1;
	{
		// default constructor
		cout << "default constructor" << endl;
		cout << "size: " << v1.size() << endl;
		cout << "capacity: " << v1.capacity() << endl;
		
		// assign
		cout << "assign" << endl;
		v1.assign(10, 2);
		cout << "size: " << v1.size() << endl;
		cout << "capacity: " << v1.capacity() << endl;
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;

		// re-assign
		cout << "re-assign" << endl;
		v1.assign(5, 7);
		cout << "size: " << v1.size() << endl;
		cout << "capacity: " << v1.capacity() << endl;
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;
		
		// front, back
		cout << "front, back" << endl;
		cout << v1.front() << endl;
		cout << v1.back() << endl;
		cout << (v1.front() = 2) << endl;
		cout << (v1.back() = 3) << endl;

		// pop
		cout << "pop" << endl;
		v1.pop_back();
		v1.pop_back();
		cout << "size: " << v1.size() << endl;
		cout << "capacity: " << v1.capacity() << endl;
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;

		// push
		cout << "push" << endl;
		v1.push_back(1);
		v1.push_back(2);
		cout << "size: " << v1.size() << endl;
		cout << "capacity: " << v1.capacity() << endl;
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;

		// clear
		cout << "clear" << endl;
		v1.clear();
		cout << "size: " << v1.size() << endl;
		cout << "capacity: " << v1.capacity() << endl;
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;
	}

	// resize and reserve
	vector<A> v2(10);
	{
		cout << "constructor with count 10" << endl;
		cout << "size: " << v2.size() << endl;
		cout << "capacity: " << v2.capacity() << endl;
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			cout << (*iter).n << ends;
		}
		cout << endl;

		// resize smaller
		cout << "resize smaller" << endl;
		v2.resize(2);
		cout << "size: " << v2.size() << endl;
		cout << "capacity: " << v2.capacity() << endl;
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			cout << (*iter).n << ends;
		}
		cout << endl;

		// resize larger
		cout << "resize larger" << endl;
		v2.resize(12);
		cout << "size: " << v2.size() << endl;
		cout << "capacity: " << v2.capacity() << endl;
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			cout << (*iter).n << ends;
		}
		cout << endl;

		// reserve smaller
		cout << "reserve smaller" << endl;
		v2.reserve(8);
		cout << "size: " << v2.size() << endl;
		cout << "capacity: " << v2.capacity() << endl;
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			cout << (*iter).n << ends;
		}
		cout << endl;

		// reserve larger
		cout << "reserve larger" << endl;
		v2.reserve(18);
		cout << "size: " << v2.size() << endl;
		cout << "capacity: " << v2.capacity() << endl;
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			cout << (*iter).n << ends;
		}
		cout << endl;
	}

	// =, [], at
	vector<A> v3(v2);
	{
		// copy constructor 
		cout << "copy constructor " << endl;
		cout << "size: " << v3.size() << endl;
		cout << "capacity: " << v3.capacity() << endl;
		for(vector<A>::iterator iter = v3.begin(); iter != v3.end(); ++iter)
		{
			cout << iter->n << ends;
		}
		cout << endl;

		// operator = 
		cout << "operator = " << endl;
		v3 = v2;
		cout << "size: " << v3.size() << endl;
		cout << "capacity: " << v3.capacity() << endl;
		for(vector<A>::iterator iter = v3.begin(); iter != v3.end(); ++iter)
		{
			cout << (*iter).n << ends;
		}
		cout << endl;

		// operator [] 
		cout << "operator [] " << endl;
		cout << "size: " << v3.size() << endl;
		cout << "capacity: " << v3.capacity() << endl;
		for(size_t i = 0; i < v3.size(); ++i)
		{
			cout << v3[i].n << ends;
		}
		cout << endl;

		// at 
		cout << "operator [] " << endl;
		cout << "size: " << v3.size() << endl;
		cout << "capacity: " << v3.capacity() << endl;
		for(size_t i = 0; i < v3.size(); ++i)
		{
			cout << v3.at(i).n << ends;
		}
		cout << endl;

		// reverse iterator
	}

	// iterator
	int a[10] = {1,3,5,7,9,2,4,6,8,10};
	vector<int> v4(a, a + 10);
	{
		// iterator constructor
		cout << "iterator constructor " << endl;
		cout << "size: " << v4.size() << endl;
		cout << "capacity: " << v4.capacity() << endl;
		for(vector<int>::iterator iter = v4.begin(); iter != v4.end(); ++iter)
		{
			cout << *iter << ends;
		}
		cout << endl;

		// const iterator
		cout << "const iterator" << endl;
		for(vector<int>::const_iterator iter = v4.begin(); iter != v4.end(); ++iter)
		{
			cout << *iter << ' ';
		}
		cout << endl;

		// reverse iterator
		cout << "reverse iterator" << endl;
		for(vector<int>::reverse_iterator iter = v4.rbegin(); iter != v4.rend(); ++iter)
		{
			cout << *iter << ' ';
		}
		cout << endl;

		// reverse const iterator
		cout << "reverse const iterator" << endl;
		for(vector<int>::reverse_const_iterator iter = v4.rbegin(); iter != v4.rend(); ++iter)
		{
			cout << *iter << ' ';
		}
		cout << endl;

		// transformation between reverse and forward const iterator
		cout << "transformation between reverse and forward iterator" << endl;
		vector<int>::reverse_iterator r_iter = v4.rbegin();
		cout << *r_iter << ' ';
		++r_iter;
		cout << *r_iter << ' ';
		++r_iter;
		vector<int>::iterator iter = r_iter.base();
		cout << *iter << ' ';
		++iter;
		cout << *iter << ' ';	
		cout << endl;

		// transformation between reverse and forward const iterator
		cout << "transformation between reverse and forward const iterator" << endl;
		vector<int>::reverse_const_iterator rc_iter = v4.rbegin();
		cout << *rc_iter << ' ';
		++rc_iter;
		cout << *rc_iter << ' ';
		++rc_iter;
		vector<int>::const_iterator c_iter = rc_iter.base();
		cout << *c_iter << ' ';
		++c_iter;
		cout << *c_iter << ' ';	
		cout << endl;
	}

	// another constructor
	vector<double> v5(10, 1.5);
	{
		// constructor with count and value
		cout << "constructor with count and value" << endl;
		cout << "size: " << v5.size() << endl;
		cout << "capacity: " << v5.capacity() << endl;
		for(vector<double>::iterator iter = v5.begin(); iter != v5.end(); ++iter)
		{
			cout << *iter << ends;
		}
		cout << endl;
	}

	// max_size
	{
		cout << "max size" << endl;
		cout << "v1: " << v1.max_size() << endl;
		cout << "v2: " << v2.max_size() << endl;
		cout << "v3: " << v3.max_size() << endl;
		cout << "v4: " << v4.max_size() << endl;
		cout << "v5: " << v5.max_size() << endl;
	}
	return 0;
}
