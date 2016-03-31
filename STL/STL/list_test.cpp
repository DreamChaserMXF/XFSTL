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
	//void multi_file_test();
	//multi_file_test();

	list<B> listb;

	// assign, front, back, push, pop, clear
	list<int> list1;
	{
		// default constructor
		cout << "default constructor" << endl;
		cout << "\tsize: " << list1.size() << endl;
		
		// empty test
		cout << "empty test" << endl;
		cout << '\t' << std::boolalpha << list1.empty() << endl;

		// assign
		cout << "assign" << endl;
		list1.assign(10, 2);
		cout << "\tsize: " << list1.size() << endl;
		cout << '\t';
		for(list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;

		// empty test
		cout << "empty test" << endl;
		cout << '\t' << list1.empty() << endl;

		// re-assign
		cout << "re-assign" << endl;
		list1.assign(5, 7);
		cout << "\tsize: " << list1.size() << endl;
		cout << '\t';
		for(list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;
		
		// front, back
		cout << "front, back" << endl;
		cout << '\t' << list1.front() << endl;
		cout << '\t' << list1.back() << endl;
		cout << '\t' << (list1.front() = 2) << endl;
		cout << '\t' << (list1.back() = 3) << endl;
		cout << '\t';
		for(list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;

		// pop
		cout << "pop" << endl;
		list1.pop_back();
		list1.pop_back();
		cout << "\tsize: " << list1.size() << endl;
		cout << '\t';
		for(list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;

		// push
		cout << "push" << endl;
		list1.push_back(1);
		list1.push_back(2);
		cout << "\tsize: " << list1.size() << endl;
		cout << '\t';
		for(list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;

		// clear
		cout << "clear" << endl;
		list1.clear();
		cout << "\tsize: " << list1.size() << endl;
		cout << '\t';
		for(list<int>::iterator iter = list1.begin(); iter != list1.end(); ++iter)
		{
			cout << (*iter) << ends;
		}
		cout << endl;

		// empty test
		cout << "empty test" << endl;
		cout << '\t' << list1.empty() << endl;
		cout << endl;
	}



	// =, [], at, data
	
	list<A> list2(3);
	list<A> list3(list2);
	{
		// _Count constructor
		cout << "_Count constructor " << endl;
		cout << "\tsize: " << list2.size() << endl;
		cout << '\t';
		for(list<A>::iterator iter = list2.begin(); iter != list2.end(); ++iter)
		{
			cout << iter->n << ends;
		}
		cout << endl;

		// copy constructor 
		cout << "copy constructor " << endl;
		cout << "\tsize: " << list3.size() << endl;
		cout << '\t';
		for(list<A>::iterator iter = list3.begin(); iter != list3.end(); ++iter)
		{
			cout << iter->n << ends;
		}
		cout << endl;
		
		// operator = 
		cout << "operator = " << endl;
		list3 = list2;
		cout << "\tsize: " << list3.size() << endl;
		cout << '\t';
		for(list<A>::iterator iter = list3.begin(); iter != list3.end(); ++iter)
		{
			cout << (*iter).n << ends;
		}
		cout << endl;
	}

	// iterator
	int a[10] = {1,3,5,7,9,2,4,6,8,10};
	list<int> list4(a, a + 10);
	{
		// iterator preorder ++
		cout << "iterator preorder ++" << endl;
		cout << "\tsize: " << list4.size() << endl;
		cout << '\t';
		for(list<int>::iterator iter = list4.begin(); iter != list4.end(); ++iter)
		{
			cout << *iter << ends;
			list<int>::iterator next_iter = ++iter;
			cout << *next_iter << ends;
			//*iter = 1;	// no error
		}
		cout << endl;

		// iterator postorder ++
		cout << "iterator postorder ++" << endl;
		cout << '\t';
		for(list<int>::iterator iter = list4.begin(); iter != list4.end(); iter++)
		{
			cout << *iter << ends;
			list<int>::iterator next_iter = ++(iter++);
			cout << *next_iter << ends;
			//*iter = 1;	// no error
		}
		cout << endl;
	

		// iterator preorder --
		cout << "iterator preorder --" << endl;
		cout << '\t';
		for(list<int>::iterator iter = --list4.end(); iter != --list4.begin(); --iter)
		{
			cout << *iter << ends;
			list<int>::iterator next_iter = --iter;
			cout << *next_iter << ends;
		}
		cout << endl;

		// iterator postorder --
		cout << "iterator postorder --" << endl;
		cout << '\t';
		for(list<int>::iterator iter = --list4.end(); iter != --list4.begin(); iter--)
		{
			cout << *iter << ends;
			list<int>::iterator next_iter = --(iter--);
			cout << *next_iter << ends;
		}
		cout << endl;

		

		// const iterator preorder ++
		cout << "const iterator preorder ++" << endl;
		cout << "\tsize: " << list4.size() << endl;
		cout << '\t';
		for(list<int>::const_iterator iter = list4.begin(); iter != list4.end(); ++iter)
		{
			cout << *iter << ends;
			list<int>::const_iterator next_iter = ++iter;
			cout << *next_iter << ends;
		}
		cout << endl;

		// const iterator postorder ++
		cout << "const iterator postorder ++" << endl;
		cout << '\t';
		for(list<int>::const_iterator iter = list4.begin(); iter != list4.end(); iter++)
		{
			cout << *iter << ends;
			list<int>::const_iterator next_iter = ++(iter++);
			cout << *next_iter << ends;
		}
		cout << endl;

		// const iterator preorder --
		cout << "const iterator preorder --" << endl;
		cout << '\t';
		for(list<int>::const_iterator iter = --list4.end(); iter != --list4.begin(); --iter)
		{
			cout << *iter << ends;
			list<int>::const_iterator next_iter = --iter;
			cout << *next_iter << ends;
		}
		cout << endl;

		// const iterator postorder --
		cout << "const iterator postorder --" << endl;
		cout << '\t';
		for(list<int>::const_iterator iter = --list4.end(); iter != --list4.begin(); iter--)
		{
			cout << *iter << ends;
			list<int>::const_iterator next_iter = --(iter--);
			cout << *next_iter << ends;
		}
		cout << endl;
		

		// reverse iterator preorder ++ 
		cout << "reverse iterator preorder ++" << endl;
		cout << '\t';
		for(list<int>::reverse_iterator iter = list4.rbegin(); iter != list4.rend(); ++iter)
		{
			cout << *iter << ' ';
			//*iter = 1;	// no error
			list<int>::reverse_iterator next_iter = ++iter;
			cout << *next_iter << ends;
		}
		cout << endl;

		// reverse iterator postorder ++ 
		cout << "reverse iterator postorder ++" << endl;
		cout << '\t';
		for(list<int>::reverse_iterator iter = list4.rbegin(); iter != list4.rend(); iter++)
		{
			cout << *iter << ' ';
			//*iter = 1;	// no error
			list<int>::reverse_iterator next_iter = ++(iter++);
			cout << *next_iter << ends;
		}
		cout << endl;

		// reverse iterator preorder --
		cout << "reverse iterator preorder --" << endl;
		cout << '\t';
		for(list<int>::reverse_iterator iter = --list4.rend(); iter != --list4.rbegin(); --iter)
		{
			cout << *iter << ends;
			list<int>::reverse_iterator next_iter = --iter;
			cout << *next_iter << ends;
		}
		cout << endl;
		// reverse iterator postorder --
		cout << "reverse iterator postorder --" << endl;
		cout << '\t';
		for(list<int>::reverse_iterator iter = --list4.rend(); iter != --list4.rbegin(); iter--)
		{
			cout << *iter << ends;
			list<int>::reverse_iterator next_iter = --(iter--);
			cout << *next_iter << ends;
		}
		cout << endl;

		

	
		// const reverse iterator preorder ++ 
		cout << "const reverse iterator preorder ++" << endl;
		cout << '\t';
		for(list<int>::const_reverse_iterator iter = list4.rbegin(); iter != list4.rend(); ++iter)
		{
			cout << *iter << ' ';
			//*iter = 1;	// error
			list<int>::const_reverse_iterator next_iter = ++iter;
			cout << *next_iter << ends;
		}
		cout << endl;
		// const reverse iterator postorder ++ 
		cout << "const reverse iterator postorder ++" << endl;
		cout << '\t';
		for(list<int>::const_reverse_iterator iter = list4.rbegin(); iter != list4.rend(); iter++)
		{
			cout << *iter << ' ';
			//*iter = 1;	// error
			list<int>::const_reverse_iterator next_iter = ++(iter++);
			cout << *next_iter << ends;
		}
		cout << endl;

		// const reverse iterator preorder --
		cout << "const reverse preorder iterator --" << endl;
		cout << '\t';
		list<int>::reverse_iterator exp_iter = list4.rbegin();
		--exp_iter;
		static_cast<list<int>::const_reverse_iterator>(exp_iter);
		for(list<int>::const_reverse_iterator iter = --list4.rend(); iter != --list4.rbegin(); --iter)
		{
			cout << *iter << ends;
			list<int>::const_reverse_iterator next_iter = --iter;
			cout << *next_iter << ends;
		}
		cout << endl;
		// const reverse iterator postorder --
		cout << "const reverse postorder iterator --" << endl;
		cout << '\t';
		for(list<int>::const_reverse_iterator iter = --list4.rend(); iter != --list4.rbegin(); iter--)
		{
			cout << *iter << ends;
			list<int>::const_reverse_iterator next_iter = --(iter--);
			cout << *next_iter << ends;
		}
		cout << endl;

		// cbegin, cend
		cout << "cbegin, cend" << endl;
		cout << '\t';
		for(list<int>::const_iterator iter = list4.cbegin(); iter != list4.cend(); ++iter)
		{
			cout << *iter << ends;
			list<int>::const_iterator next_iter = ++iter;
			cout << *next_iter << ends;
		}
		cout << endl;

		// crbegin, crend
		cout << "crbegin, crend" << endl;
		cout << '\t';
		//list<int>::const_reverse_iterator cr_iter1 = list4.crbegin();
		for(list<int>::const_reverse_iterator iter = list4.crbegin(); iter != list4.crend(); ++iter)
		{
			cout << *iter << ends;
			list<int>::const_reverse_iterator next_iter = ++iter;
			cout << *next_iter << ends;
		}
		cout << endl;

		// transformation between reverse and forward iterator
		{
			cout << "transformation between reverse and forward iterator" << endl;
			list<int>::reverse_iterator r_iter = list4.rbegin();
			cout << '\t';
			cout << *r_iter << ' ';
			++r_iter;
			cout << *r_iter << ' ';
			++r_iter;
			list<int>::iterator iter = r_iter.base();
			cout << *iter << ' ';
			++iter;
			cout << *iter << ' ';	
			cout << endl;
		}

		// transformation between const reverse and const forward const iterator
		{
			cout << "transformation between const reverse and const forward const iterator" << endl;
			list<int>::const_reverse_iterator cr_iter = list4.rbegin();
			cout << '\t';
			cout << *cr_iter << ' ';
			++cr_iter;
			cout << *cr_iter << ' ';
			++cr_iter;
			list<int>::const_iterator c_iter = cr_iter.base();
			cout << *c_iter << ' ';
			++c_iter;
			cout << *c_iter << ' ';	
			cout << endl;
		}

		

		// erase
		{
			// erase(_Where)
			cout << "erase(_Where)" << endl;
			list<int>::iterator iter = list4.begin();
			++iter;
			iter = list4.erase(iter);
			cout << '\t';
			for(list<int>::const_iterator c_iter = list4.begin(); c_iter != list4.end(); ++c_iter)
			{
				cout << *c_iter << ' ';
			}
			cout << endl;
			cout << '\t';
			while(iter != list4.end())
			{
				cout << *iter++ << ' ';
			}
			cout << endl;

			// erase(_First, _Last)
			cout << "erase(_First, _Last)" << endl;
			iter = list4.begin();
			list<int>::iterator iter2 = iter;
			++iter2;
			++iter2;
			iter = list4.erase(iter, iter2);
			cout << '\t';
			for(list<int>::const_iterator c_iter = list4.begin(); c_iter != list4.end(); ++c_iter)
			{
				cout << *c_iter << ' ';
			}
			cout << endl;
			cout << '\t';
			while(iter != list4.end())
			{
				cout << *iter++ << ' ';
			}
			cout << endl;
		}

		// insert
		{
			// insert(_Where, _Value)
			list<int> list5;
			cout << "insert(_Where, _Value)" << endl;
			list<int>::iterator iter = list5.insert(list5.begin(), 1);
			cout << '\t';
			for(list<int>::const_iterator c_iter = list5.begin(); c_iter != list5.end(); ++c_iter)
			{
				cout << *c_iter << ' ';
			}
			cout << endl;
			cout << '\t';
			while(iter != list5.end())
			{
				cout << *iter++ << ' ';
			}
			cout << endl;

			iter = list5.insert(list5.end(), 3);
			cout << '\t';
			for(list<int>::const_iterator c_iter = list5.begin(); c_iter != list5.end(); ++c_iter)
			{
				cout << *c_iter << ' ';
			}
			cout << endl;
			cout << '\t';
			while(iter != list5.end())
			{
				cout << *iter++ << ' ';
			}
			cout << endl;

			// insert(_Where, _Count, _Value)
			cout << "insert(_Where, _Count, _Value)" << endl;
			iter = list5.insert(++list5.begin(), 3, 333);
			cout << '\t';
			for(list<int>::const_iterator c_iter = list5.begin(); c_iter != list5.end(); ++c_iter)
			{
				cout << *c_iter << ' ';
			}
			cout << endl;
			cout << '\t';
			while(iter != list5.end())
			{
				cout << *iter++ << ' ';
			}
			cout << endl;

			// insert(_Where, _First, _Last)
			cout << "insert(_Where, _First, _Last)" << endl;
			int a[] = {123, 321, 213};
			iter = list5.insert(++list5.begin(), a, a + 3);
			cout << '\t';
			for(list<int>::const_iterator c_iter = list5.begin(); c_iter != list5.end(); ++c_iter)
			{
				cout << *c_iter << ' ';
			}
			cout << endl;
			cout << '\t';
			while(iter != list5.end())
			{
				cout << *iter++ << ' ';
			}
			cout << endl;
		}

		// iterator assignment
		cout << "iterator assignment" << endl;
		cout << "iterator" << endl;
		for(list<int>::iterator iter = list4.begin(); iter != list4.end(); ++iter)
		{
			*iter = 123;
		}
		cout << '\t';
		for(list<int>::iterator iter = list4.begin(); iter != list4.end(); ++iter)
		{
			cout << *iter << ' ';
		}
		cout << endl;

		cout << "reverse iterator" << endl;
		for(list<int>::reverse_iterator iter = list4.rbegin(); iter != list4.rend(); ++iter)
		{
			*iter = 321;
		}
		cout << '\t';
		for(list<int>::reverse_iterator iter = list4.rbegin(); iter != list4.rend(); ++iter)
		{
			cout << *iter << ' ';
		}
		cout << endl;
	}

	// reverse test
	{
		cout << endl;
		cout << "reverse test" << endl;
		int a[] = {1, 2, 3, 4, 5};
		list<int> rev_list(a, a + 5);
		cout << '\t';
		for(list<int>::iterator iter = rev_list.begin(); iter != rev_list.end(); ++iter)
		{
			cout << *iter << ends;
		}
		cout << endl;

		rev_list.reverse();

		cout << '\t';
		for(list<int>::iterator iter = rev_list.begin(); iter != rev_list.end(); ++iter)
		{
			cout << *iter << ends;
		}
		cout << endl;
	}

	// another constructor
	list<double> list5(10, 1.5);
	{
		// constructor with count and value
		cout << "\nconstructor with count and value" << endl;
		cout << "\tsize: " << list5.size() << endl;
		cout << '\t';
		for(list<double>::iterator iter = list5.begin(); iter != list5.end(); ++iter)
		{
			cout << *iter << ends;
		}
		cout << endl;
	}

	// max_size
	{
		cout << "max size" << endl;
		cout << "\tv1: " << list1.max_size() << endl;
		cout << "\tv2: " << list2.max_size() << endl;
		cout << "\tv3: " << list3.max_size() << endl;
		//cout << "\tv4: " << list4.max_size() << endl;
		cout << "\tv5: " << list5.max_size() << endl;
	}

	// test
	{
		list<unsigned int> vui;
		vui.assign(10, 100);
	}
	
	list<string> vs;
	vs.push_back("abc");
	cout << vs.front() << endl;
}