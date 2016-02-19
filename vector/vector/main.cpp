#pragma warning (disable : 4996)

#include <iostream>
#include "vector.hpp"

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
	void multi_file_test();
	multi_file_test();

	// assign, front, back, push, pop, clear
	vector<int> v1;
	{
		// default constructor
		cout << "default constructor" << endl;
		cout << "\tsize: " << v1.size() << endl;
		cout << "\tcapacity: " << v1.capacity() << endl;
		
		// empty test
		cout << "empty test" << endl;
		cout << '\t' << std::boolalpha << v1.empty() << endl;

		// assign
		cout << "assign" << endl;
		v1.assign(10, 2);
		cout << "\tsize: " << v1.size() << endl;
		cout << "\tcapacity: " << v1.capacity() << endl;
		cout << '\t';
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;

		// empty test
		cout << "empty test" << endl;
		cout << '\t' << v1.empty() << endl;

		// re-assign
		cout << "re-assign" << endl;
		v1.assign(5, 7);
		cout << "\tsize: " << v1.size() << endl;
		cout << "\tcapacity: " << v1.capacity() << endl;
		cout << '\t';
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;
		
		// front, back
		cout << "front, back" << endl;
		cout << '\t' << v1.front() << endl;
		cout << '\t' << v1.back() << endl;
		cout << '\t' << (v1.front() = 2) << endl;
		cout << '\t' << (v1.back() = 3) << endl;

		// pop
		cout << "pop" << endl;
		v1.pop_back();
		v1.pop_back();
		cout << "\tsize: " << v1.size() << endl;
		cout << "\tcapacity: " << v1.capacity() << endl;
		cout << '\t';
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;

		// push
		cout << "push" << endl;
		v1.push_back(1);
		v1.push_back(2);
		cout << "\tsize: " << v1.size() << endl;
		cout << "\tcapacity: " << v1.capacity() << endl;
		cout << '\t';
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;

		// clear
		cout << "clear" << endl;
		v1.clear();
		cout << "\tsize: " << v1.size() << endl;
		cout << "\tcapacity: " << v1.capacity() << endl;
		cout << '\t';
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;

		// empty test
		cout << "empty test" << endl;
		cout << '\t' << v1.empty() << endl;
		cout << endl;
	}

	// resize and reserve
	vector<A> v2(10);
	{
		cout << "constructor with count 10" << endl;
		cout << "\tsize: " << v2.size() << endl;
		cout << "\tcapacity: " << v2.capacity() << endl;
		cout << '\t';
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			cout << (*iter).n << ends;
		}
		cout << endl;

		// resize smaller
		cout << "resize smaller" << endl;
		v2.resize(2);
		cout << "\tsize: " << v2.size() << endl;
		cout << "\tcapacity: " << v2.capacity() << endl;
		cout << '\t';
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			cout << (*iter).n << ends;
		}
		cout << endl;

		// resize larger
		cout << "resize larger" << endl;
		v2.resize(12);
		cout << "\tsize: " << v2.size() << endl;
		cout << "\tcapacity: " << v2.capacity() << endl;
		cout << '\t';
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			cout << (*iter).n << ends;
		}
		cout << endl;

		// reserve smaller
		cout << "reserve smaller" << endl;
		v2.reserve(8);
		cout << "\tsize: " << v2.size() << endl;
		cout << "\tcapacity: " << v2.capacity() << endl;
		cout << '\t';
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			cout << (*iter).n << ends;
		}
		cout << endl;

		// reserve larger
		cout << "reserve larger" << endl;
		v2.reserve(18);
		cout << "\tsize: " << v2.size() << endl;
		cout << "\tcapacity: " << v2.capacity() << endl;
		cout << '\t';
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
		cout << "\tsize: " << v3.size() << endl;
		cout << "\tcapacity: " << v3.capacity() << endl;
		cout << '\t';
		for(vector<A>::iterator iter = v3.begin(); iter != v3.end(); ++iter)
		{
			cout << iter->n << ends;
		}
		cout << endl;

		// operator = 
		cout << "operator = " << endl;
		v3 = v2;
		cout << "\tsize: " << v3.size() << endl;
		cout << "\tcapacity: " << v3.capacity() << endl;
		cout << '\t';
		for(vector<A>::iterator iter = v3.begin(); iter != v3.end(); ++iter)
		{
			cout << (*iter).n << ends;
		}
		cout << endl;

		// operator [] 
		cout << "operator [] " << endl;
		cout << "\tsize: " << v3.size() << endl;
		cout << "\tcapacity: " << v3.capacity() << endl;
		cout << '\t';
		for(size_t i = 0; i < v3.size(); ++i)
		{
			cout << v3[i].n << ends;
		}
		cout << endl;

		// at 
		cout << "operator [] " << endl;
		cout << "\tsize: " << v3.size() << endl;
		cout << "\tcapacity: " << v3.capacity() << endl;
		cout << '\t';
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
		// iterator ++
		cout << "iterator ++" << endl;
		cout << "\tsize: " << v4.size() << endl;
		cout << "\tcapacity: " << v4.capacity() << endl;
		cout << '\t';
		for(vector<int>::iterator iter = v4.begin(); iter != v4.end(); ++iter)
		{
			cout << *iter << ends;
			//*iter = 1;	// no error
		}
		cout << endl;

		// iterator +
		cout << "iterator +" << endl;
		cout << '\t';
		for(vector<int>::iterator iter = v4.begin(); iter != v4.end(); iter += 2)
		{
			cout << *iter << ends;
			vector<int>::iterator next_iter = iter + 1;
			cout << *next_iter << ends;
		}
		cout << endl;

		// iterator --
		cout << "iterator --" << endl;
		cout << '\t';
		for(vector<int>::iterator iter = v4.end() - 1; iter != v4.begin() - 1; --iter)
		{
			cout << *iter << ends;
		}
		cout << endl;

		// iterator -
		cout << "iterator -" << endl;
		cout << '\t';
		for(vector<int>::iterator iter = v4.end() - 1; iter != v4.begin() - 1; iter -= 2)
		{
			cout << *iter << ends;
			vector<int>::iterator next_iter = iter - 1;
			cout << *next_iter << ends;
		}
		cout << endl;

		// const iterator
		cout << "const iterator" << endl;
		cout << '\t';
		for(vector<int>::const_iterator iter = v4.begin(); iter != v4.end(); ++iter)
		{
			cout << *iter << ' ';
			//*iter = 1;	// error
		}
		cout << endl;

		// const iterator ++
		cout << "const iterator ++" << endl;
		cout << "\tsize: " << v4.size() << endl;
		cout << "\tcapacity: " << v4.capacity() << endl;
		cout << '\t';
		for(vector<int>::const_iterator iter = v4.begin(); iter != v4.end(); ++iter)
		{
			cout << *iter << ends;
		}
		cout << endl;

		// const iterator +
		cout << "const iterator +" << endl;
		cout << '\t';
		for(vector<int>::const_iterator iter = v4.begin(); iter != v4.end(); iter += 2)
		{
			cout << *iter << ends;
			vector<int>::const_iterator next_iter = iter + 1;
			cout << *next_iter << ends;
		}
		cout << endl;

		// const iterator --
		cout << "const iterator --" << endl;
		cout << '\t';
		for(vector<int>::const_iterator iter = v4.end() - 1; iter != v4.begin() - 1; --iter)
		{
			cout << *iter << ends;
		}
		cout << endl;

		// const iterator -
		cout << "const iterator -" << endl;
		cout << '\t';
		for(vector<int>::const_iterator iter = v4.end() - 1; iter != v4.begin() - 1; iter -= 2)
		{
			cout << *iter << ends;
			vector<int>::const_iterator next_iter = iter - 1;
			cout << *next_iter << ends;
		}
		cout << endl;

		// reverse iterator ++ 
		cout << "reverse iterator ++" << endl;
		cout << '\t';
		for(vector<int>::reverse_iterator iter = v4.rbegin(); iter != v4.rend(); ++iter)
		{
			cout << *iter << ' ';
			//*iter = 1;	// no error
		}
		cout << endl;

		// reverse iterator +
		cout << "reverse iterator +" << endl;
		cout << '\t';
		for(vector<int>::reverse_iterator iter = v4.rbegin(); iter != v4.rend(); iter += 2)
		{
			cout << *iter << ends;
			vector<int>::reverse_iterator next_iter = iter + 1;
			cout << *next_iter << ends;
		}
		cout << endl;

		// reverse iterator --
		cout << "reverse iterator --" << endl;
		cout << '\t';
		for(vector<int>::reverse_iterator iter = v4.rend() - 1; iter != v4.rbegin() - 1; --iter)
		{
			cout << *iter << ends;
		}
		cout << endl;

		// reverse iterator -
		cout << "reverse iterator -" << endl;
		cout << '\t';
		for(vector<int>::reverse_iterator iter = v4.rend() - 1; iter != v4.rbegin() - 1; iter -= 2)
		{
			cout << *iter << ends;
			vector<int>::reverse_iterator next_iter = iter - 1;
			cout << *next_iter << ends;
		}
		cout << endl;

		// const reverse iterator ++ 
		cout << "const reverse iterator ++" << endl;
		cout << '\t';
		for(vector<int>::const_reverse_iterator iter = v4.rbegin(); iter != v4.rend(); ++iter)
		{
			cout << *iter << ' ';
			//*iter = 1;	// error
		}
		cout << endl;

		// const reverse iterator +
		cout << "const reverse iterator +" << endl;
		cout << '\t';
		for(vector<int>::const_reverse_iterator iter = v4.rbegin(); iter != v4.rend(); iter += 2)
		{
			cout << *iter << ends;
			vector<int>::const_reverse_iterator next_iter = iter + 1;
			cout << *next_iter << ends;
		}
		cout << endl;

		// const reverse iterator --
		cout << "const reverse iterator --" << endl;
		cout << '\t';
		for(vector<int>::const_reverse_iterator iter = v4.rend() - 1; iter != v4.rbegin() - 1; --iter)
		{
			cout << *iter << ends;
		}
		cout << endl;

		// const reverse iterator -
		cout << "const reverse iterator -" << endl;
		cout << '\t';
		for(vector<int>::const_reverse_iterator iter = v4.rend() - 1; iter != v4.rbegin() - 1; iter -= 2)
		{
			cout << *iter << ends;
			vector<int>::const_reverse_iterator next_iter = iter - 1;
			cout << *next_iter << ends;
		}
		cout << endl;
		
		// cbegin, cend
		cout << "cbegin, cend" << endl;
		cout << '\t';
		for(vector<int>::const_iterator iter = v4.cbegin(); iter != v4.cend(); iter += 2)
		{
			cout << *iter << ends;
			vector<int>::const_iterator next_iter = iter + 1;
			cout << *next_iter << ends;
		}
		cout << endl;

		// crbegin, crend
		cout << "crbegin, crend" << endl;
		cout << '\t';
		//vector<int>::const_reverse_iterator cr_iter1 = v4.crbegin();
		for(vector<int>::const_reverse_iterator iter = v4.crbegin(); iter != v4.crend(); iter += 2)
		{
			cout << *iter << ends;
			vector<int>::const_reverse_iterator next_iter = iter + 1;
			cout << *next_iter << ends;
		}
		cout << endl;

		// transformation between reverse and forward iterator
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

		// transformation between const reverse and const forward const iterator
		cout << "transformation between const reverse and const forward const iterator" << endl;
		vector<int>::const_reverse_iterator cr_iter = v4.rbegin();
		cout << *cr_iter << ' ';
		++cr_iter;
		cout << *cr_iter << ' ';
		++cr_iter;
		vector<int>::const_iterator c_iter = cr_iter.base();
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
		cout << "\tsize: " << v5.size() << endl;
		cout << "\tcapacity: " << v5.capacity() << endl;
		cout << '\t';
		for(vector<double>::iterator iter = v5.begin(); iter != v5.end(); ++iter)
		{
			cout << *iter << ends;
		}
		cout << endl;
	}

	// max_size
	{
		cout << "max size" << endl;
		cout << "\tv1: " << v1.max_size() << endl;
		cout << "\tv2: " << v2.max_size() << endl;
		cout << "\tv3: " << v3.max_size() << endl;
		cout << "\tv4: " << v4.max_size() << endl;
		cout << "\tv5: " << v5.max_size() << endl;
	}
	return 0;
}
