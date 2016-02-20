#include <iostream>
#include <string>

#include "list.hpp"

using namespace xf;
using std::string;
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

class B
{
public:
	B(int a){};
};
void list_test()
{
	void multi_file_test();
	multi_file_test();

	list<B> vb;

	// assign, front, back, push, pop, clear
	list<int> v1;
	{
		// default constructor
		cout << "default constructor" << endl;
		cout << "\tsize: " << v1.size() << endl;
		
		// empty test
		cout << "empty test" << endl;
		cout << '\t' << std::boolalpha << v1.empty() << endl;

		// assign
		cout << "assign" << endl;
		v1.assign(10, 2);
		cout << "\tsize: " << v1.size() << endl;
		cout << '\t';
		//for(list<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		//{
		//	cout << (*iter) << ends;
		//}
		//cout << endl;

		//// empty test
		//cout << "empty test" << endl;
		//cout << '\t' << v1.empty() << endl;

		//// re-assign
		//cout << "re-assign" << endl;
		//v1.assign(5, 7);
		//cout << "\tsize: " << v1.size() << endl;
		//cout << "\tcapacity: " << v1.capacity() << endl;
		//cout << '\t';
		//for(list<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		//{
		//	cout << (*iter) << ends;
		//}
		//cout << endl;
		//
		//// front, back
		//cout << "front, back" << endl;
		//cout << '\t' << v1.front() << endl;
		//cout << '\t' << v1.back() << endl;
		//cout << '\t' << (v1.front() = 2) << endl;
		//cout << '\t' << (v1.back() = 3) << endl;

		//// pop
		//cout << "pop" << endl;
		//v1.pop_back();
		//v1.pop_back();
		//cout << "\tsize: " << v1.size() << endl;
		//cout << "\tcapacity: " << v1.capacity() << endl;
		//cout << '\t';
		//for(list<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		//{
		//	cout << (*iter) << ends;
		//}
		//cout << endl;

		//// push
		//cout << "push" << endl;
		//v1.push_back(1);
		//v1.push_back(2);
		//cout << "\tsize: " << v1.size() << endl;
		//cout << "\tcapacity: " << v1.capacity() << endl;
		//cout << '\t';
		//for(list<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		//{
		//	cout << (*iter) << ends;
		//}
		//cout << endl;

		//// clear
		//cout << "clear" << endl;
		//v1.clear();
		//cout << "\tsize: " << v1.size() << endl;
		//cout << "\tcapacity: " << v1.capacity() << endl;
		//cout << '\t';
		//for(list<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		//{
		//	cout << (*iter) << ends;
		//}
		//cout << endl;

		//// empty test
		//cout << "empty test" << endl;
		//cout << '\t' << v1.empty() << endl;
		//cout << endl;
	}

	// resize and reserve
	list<A> v2(10);

	// =, [], at, data
	list<A> v3(v2);
	{
		// copy constructor 
		cout << "copy constructor " << endl;
		cout << "\tsize: " << v3.size() << endl;
		cout << '\t';
		for(list<A>::iterator iter = v3.begin(); iter != v3.end(); ++iter)
		{
			cout << iter->n << ends;
		}
		cout << endl;

		// operator = 
		cout << "operator = " << endl;
		v3 = v2;
		cout << "\tsize: " << v3.size() << endl;
		cout << '\t';
		for(list<A>::iterator iter = v3.begin(); iter != v3.end(); ++iter)
		{
			cout << (*iter).n << ends;
		}
		cout << endl;

		// operator [] 
		cout << "operator [] " << endl;
		cout << '\t';
		for(size_t i = 0; i < v3.size(); ++i)
		{
			cout << v3[i].n << ends;
		}
		cout << endl;

		// at 
		cout << "operator at " << endl;
		cout << '\t';
		for(size_t i = 0; i < v3.size(); ++i)
		{
			cout << v3.at(i).n << ends;
		}
		cout << endl;

		// data
		cout << "data" << endl;
		cout << '\t';
		const list<A> v4(v3);
		A *pa = v3.data();
		size_t size = v3.size();
		const A *cpa = v4.data();
		for(size_t i = 0; i < size; ++i)
		{
			cout << pa[i].n << ends;
			pa[i].n -= 10;
		}
		cout << endl;
		cout << '\t';
		for(size_t i = 0; i < size; ++i)
		{
			cout << v3[i].n << ends;
		}
		cout << endl;
		// data const
		cout << "data const" << endl;
		cout << '\t';
		for(size_t i = 0; i < size; ++i)
		{
			cout << cpa[i].n << ends;
			//cpa[i].n -= 10;
		}
		cout << endl;
		
	}

	//// iterator
	//int a[10] = {1,3,5,7,9,2,4,6,8,10};
	//list<int> v4(a, a + 10);
	//{
	//	// iterator preorder ++
	//	cout << "iterator preorder ++" << endl;
	//	cout << "\tsize: " << v4.size() << endl;
	//	cout << "\tcapacity: " << v4.capacity() << endl;
	//	cout << '\t';
	//	for(list<int>::iterator iter = v4.begin(); iter != v4.end(); ++iter)
	//	{
	//		cout << *iter << ends;
	//		list<int>::iterator next_iter = ++iter;
	//		cout << *next_iter << ends;
	//		//*iter = 1;	// no error
	//	}
	//	cout << endl;

	//	// iterator postorder ++
	//	cout << "iterator postorder ++" << endl;
	//	cout << '\t';
	//	for(list<int>::iterator iter = v4.begin(); iter != v4.end(); iter++)
	//	{
	//		cout << *iter << ends;
	//		list<int>::iterator next_iter = (iter++) + 1;
	//		cout << *next_iter << ends;
	//		//*iter = 1;	// no error
	//	}
	//	cout << endl;

	//	// iterator +
	//	cout << "iterator +" << endl;
	//	cout << '\t';
	//	for(list<int>::iterator iter = v4.begin(); iter != v4.end(); iter += 2)
	//	{
	//		cout << *iter << ends;
	//		list<int>::iterator next_iter = iter + 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;


	//	// iterator preorder --
	//	cout << "iterator preorder --" << endl;
	//	cout << '\t';
	//	for(list<int>::iterator iter = v4.end() - 1; iter != v4.begin() - 1; --iter)
	//	{
	//		cout << *iter << ends;
	//		list<int>::iterator next_iter = --iter;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// iterator postorder --
	//	cout << "iterator postorder --" << endl;
	//	cout << '\t';
	//	for(list<int>::iterator iter = v4.end() - 1; iter != v4.begin() - 1; iter--)
	//	{
	//		cout << *iter << ends;
	//		list<int>::iterator next_iter = (iter--) - 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// iterator -
	//	cout << "iterator -" << endl;
	//	cout << '\t';
	//	for(list<int>::iterator iter = v4.end() - 1; iter != v4.begin() - 1; iter -= 2)
	//	{
	//		cout << *iter << ends;
	//		list<int>::iterator next_iter = iter - 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// const iterator preorder ++
	//	cout << "const iterator preorder ++" << endl;
	//	cout << "\tsize: " << v4.size() << endl;
	//	cout << "\tcapacity: " << v4.capacity() << endl;
	//	cout << '\t';
	//	for(list<int>::const_iterator iter = v4.begin(); iter != v4.end(); ++iter)
	//	{
	//		cout << *iter << ends;
	//		list<int>::const_iterator next_iter = ++iter;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// const iterator postorder ++
	//	cout << "const iterator postorder ++" << endl;
	//	cout << '\t';
	//	for(list<int>::const_iterator iter = v4.begin(); iter != v4.end(); iter++)
	//	{
	//		cout << *iter << ends;
	//		list<int>::const_iterator next_iter = (iter++) + 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// const iterator +
	//	cout << "const iterator +" << endl;
	//	cout << '\t';
	//	for(list<int>::const_iterator iter = v4.begin(); iter != v4.end(); iter += 2)
	//	{
	//		cout << *iter << ends;
	//		list<int>::const_iterator next_iter = iter + 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// const iterator preorder --
	//	cout << "const iterator preorder --" << endl;
	//	cout << '\t';
	//	for(list<int>::const_iterator iter = v4.end() - 1; iter != v4.begin() - 1; --iter)
	//	{
	//		cout << *iter << ends;
	//		list<int>::const_iterator next_iter = --iter;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// const iterator postorder --
	//	cout << "const iterator postorder --" << endl;
	//	cout << '\t';
	//	for(list<int>::const_iterator iter = v4.end() - 1; iter != v4.begin() - 1; iter--)
	//	{
	//		cout << *iter << ends;
	//		list<int>::const_iterator next_iter = (iter--) - 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// const iterator -
	//	cout << "const iterator -" << endl;
	//	cout << '\t';
	//	for(list<int>::const_iterator iter = v4.end() - 1; iter != v4.begin() - 1; iter -= 2)
	//	{
	//		cout << *iter << ends;
	//		list<int>::const_iterator next_iter = iter - 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// reverse iterator preorder ++ 
	//	cout << "reverse iterator preorder ++" << endl;
	//	cout << '\t';
	//	for(list<int>::reverse_iterator iter = v4.rbegin(); iter != v4.rend(); ++iter)
	//	{
	//		cout << *iter << ' ';
	//		//*iter = 1;	// no error
	//		list<int>::reverse_iterator next_iter = ++iter;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// reverse iterator postorder ++ 
	//	cout << "reverse iterator postorder ++" << endl;
	//	cout << '\t';
	//	for(list<int>::reverse_iterator iter = v4.rbegin(); iter != v4.rend(); iter++)
	//	{
	//		cout << *iter << ' ';
	//		//*iter = 1;	// no error
	//		list<int>::reverse_iterator next_iter = (iter++) + 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;
	//	// reverse iterator +
	//	cout << "reverse iterator +" << endl;
	//	cout << '\t';
	//	for(list<int>::reverse_iterator iter = v4.rbegin(); iter != v4.rend(); iter += 2)
	//	{
	//		cout << *iter << ends;
	//		list<int>::reverse_iterator next_iter = iter + 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// reverse iterator preorder --
	//	cout << "reverse iterator preorder --" << endl;
	//	cout << '\t';
	//	for(list<int>::reverse_iterator iter = v4.rend() - 1; iter != v4.rbegin() - 1; --iter)
	//	{
	//		cout << *iter << ends;
	//		list<int>::reverse_iterator next_iter = --iter;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;
	//	// reverse iterator postorder --
	//	cout << "reverse iterator postorder --" << endl;
	//	cout << '\t';
	//	for(list<int>::reverse_iterator iter = v4.rend() - 1; iter != v4.rbegin() - 1; iter--)
	//	{
	//		cout << *iter << ends;
	//		list<int>::reverse_iterator next_iter = (iter--) - 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// reverse iterator -
	//	cout << "reverse iterator -" << endl;
	//	cout << '\t';
	//	for(list<int>::reverse_iterator iter = v4.rend() - 1; iter != v4.rbegin() - 1; iter -= 2)
	//	{
	//		cout << *iter << ends;
	//		list<int>::reverse_iterator next_iter = iter - 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// const reverse iterator preorder ++ 
	//	cout << "const reverse iterator preorder ++" << endl;
	//	cout << '\t';
	//	for(list<int>::const_reverse_iterator iter = v4.rbegin(); iter != v4.rend(); ++iter)
	//	{
	//		cout << *iter << ' ';
	//		//*iter = 1;	// error
	//		list<int>::const_reverse_iterator next_iter = ++iter;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;
	//	// const reverse iterator postorder ++ 
	//	cout << "const reverse iterator postorder ++" << endl;
	//	cout << '\t';
	//	for(list<int>::const_reverse_iterator iter = v4.rbegin(); iter != v4.rend(); iter++)
	//	{
	//		cout << *iter << ' ';
	//		//*iter = 1;	// error
	//		list<int>::const_reverse_iterator next_iter = (iter++) + 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// const reverse iterator +
	//	cout << "const reverse iterator +" << endl;
	//	cout << '\t';
	//	for(list<int>::const_reverse_iterator iter = v4.rbegin(); iter != v4.rend(); iter += 2)
	//	{
	//		cout << *iter << ends;
	//		list<int>::const_reverse_iterator next_iter = iter + 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// const reverse iterator --
	//	cout << "const reverse iterator --" << endl;
	//	cout << '\t';
	//	for(list<int>::const_reverse_iterator iter = v4.rend() - 1; iter != v4.rbegin() - 1; --iter)
	//	{
	//		cout << *iter << ends;
	//	}
	//	cout << endl;

	//	// const reverse iterator -
	//	cout << "const reverse iterator -" << endl;
	//	cout << '\t';
	//	for(list<int>::const_reverse_iterator iter = v4.rend() - 1; iter != v4.rbegin() - 1; iter -= 2)
	//	{
	//		cout << *iter << ends;
	//		list<int>::const_reverse_iterator next_iter = iter - 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;
	//	
	//	// cbegin, cend
	//	cout << "cbegin, cend" << endl;
	//	cout << '\t';
	//	for(list<int>::const_iterator iter = v4.cbegin(); iter != v4.cend(); iter += 2)
	//	{
	//		cout << *iter << ends;
	//		list<int>::const_iterator next_iter = iter + 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// crbegin, crend
	//	cout << "crbegin, crend" << endl;
	//	cout << '\t';
	//	//list<int>::const_reverse_iterator cr_iter1 = v4.crbegin();
	//	for(list<int>::const_reverse_iterator iter = v4.crbegin(); iter != v4.crend(); iter += 2)
	//	{
	//		cout << *iter << ends;
	//		list<int>::const_reverse_iterator next_iter = iter + 1;
	//		cout << *next_iter << ends;
	//	}
	//	cout << endl;

	//	// transformation between reverse and forward iterator
	//	{
	//		cout << "transformation between reverse and forward iterator" << endl;
	//		list<int>::reverse_iterator r_iter = v4.rbegin();
	//		cout << '\t';
	//		cout << *r_iter << ' ';
	//		++r_iter;
	//		cout << *r_iter << ' ';
	//		++r_iter;
	//		list<int>::iterator iter = r_iter.base();
	//		cout << *iter << ' ';
	//		++iter;
	//		cout << *iter << ' ';	
	//		cout << endl;
	//	}

	//	// transformation between const reverse and const forward const iterator
	//	{
	//		cout << "transformation between const reverse and const forward const iterator" << endl;
	//		list<int>::const_reverse_iterator cr_iter = v4.rbegin();
	//		cout << '\t';
	//		cout << *cr_iter << ' ';
	//		++cr_iter;
	//		cout << *cr_iter << ' ';
	//		++cr_iter;
	//		list<int>::const_iterator c_iter = cr_iter.base();
	//		cout << *c_iter << ' ';
	//		++c_iter;
	//		cout << *c_iter << ' ';	
	//		cout << endl;
	//	}

	//	// erase
	//	{
	//		// erase(_Where)
	//		cout << "erase(_Where)" << endl;
	//		list<int>::iterator iter = v4.begin();
	//		++iter;
	//		iter = v4.erase(iter);
	//		cout << '\t';
	//		for(list<int>::const_iterator c_iter = v4.begin(); c_iter != v4.end(); ++c_iter)
	//		{
	//			cout << *c_iter << ' ';
	//		}
	//		cout << endl;
	//		cout << '\t';
	//		while(iter != v4.end())
	//		{
	//			cout << *iter++ << ' ';
	//		}
	//		cout << endl;

	//		// erase(_First, _Last)
	//		cout << "erase(_First, _Last)" << endl;
	//		iter = v4.begin();
	//		list<int>::iterator iter2 = iter + 2;
	//		iter = v4.erase(iter, iter2);
	//		cout << '\t';
	//		for(list<int>::const_iterator c_iter = v4.begin(); c_iter != v4.end(); ++c_iter)
	//		{
	//			cout << *c_iter << ' ';
	//		}
	//		cout << endl;
	//		cout << '\t';
	//		while(iter != v4.end())
	//		{
	//			cout << *iter++ << ' ';
	//		}
	//		cout << endl;
	//	}

	//	// insert
	//	{
	//		// insert(_Where, _Value)
	//		list<int> v5;
	//		cout << "insert(_Where, _Value)" << endl;
	//		list<int>::iterator iter = v5.insert(v5.begin(), 1);
	//		cout << '\t';
	//		for(list<int>::const_iterator c_iter = v5.begin(); c_iter != v5.end(); ++c_iter)
	//		{
	//			cout << *c_iter << ' ';
	//		}
	//		cout << endl;
	//		cout << '\t';
	//		while(iter != v5.end())
	//		{
	//			cout << *iter++ << ' ';
	//		}
	//		cout << endl;

	//		iter = v5.insert(v5.end(), 3);
	//		cout << '\t';
	//		for(list<int>::const_iterator c_iter = v5.begin(); c_iter != v5.end(); ++c_iter)
	//		{
	//			cout << *c_iter << ' ';
	//		}
	//		cout << endl;
	//		cout << '\t';
	//		while(iter != v5.end())
	//		{
	//			cout << *iter++ << ' ';
	//		}
	//		cout << endl;

	//		// insert(_Where, _Count, _Value)
	//		cout << "insert(_Where, _Count, _Value)" << endl;
	//		iter = v5.insert(v5.begin() + 1, 3, 333);
	//		cout << '\t';
	//		for(list<int>::const_iterator c_iter = v5.begin(); c_iter != v5.end(); ++c_iter)
	//		{
	//			cout << *c_iter << ' ';
	//		}
	//		cout << endl;
	//		cout << '\t';
	//		while(iter != v5.end())
	//		{
	//			cout << *iter++ << ' ';
	//		}
	//		cout << endl;

	//		// insert(_Where, _First, _Last)
	//		cout << "insert(_Where, _First, _Last)" << endl;
	//		int a[] = {123, 321, 213};
	//		iter = v5.insert(v5.begin() + 1, a, a + 3);
	//		cout << '\t';
	//		for(list<int>::const_iterator c_iter = v5.begin(); c_iter != v5.end(); ++c_iter)
	//		{
	//			cout << *c_iter << ' ';
	//		}
	//		cout << endl;
	//		cout << '\t';
	//		while(iter != v5.end())
	//		{
	//			cout << *iter++ << ' ';
	//		}
	//		cout << endl;
	//	}
	//}

	// another constructor
	list<double> v5(10, 1.5);
	{
		// constructor with count and value
		cout << "\nconstructor with count and value" << endl;
		cout << "\tsize: " << v5.size() << endl;
		cout << '\t';
		for(list<double>::iterator iter = v5.begin(); iter != v5.end(); ++iter)
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
		//cout << "\tv4: " << v4.max_size() << endl;
		cout << "\tv5: " << v5.max_size() << endl;
	}

	// test
	{
		list<unsigned int> vui;
		vui.assign(10, 100);
	}
	
	list<string> vs;
	vs.push_back("abc");
}