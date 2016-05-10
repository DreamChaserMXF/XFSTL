#include <iostream>
#include <string>

#include "vector.hpp"
#include "_Iterator_Traits.hpp"

using namespace xf;
using std::string;
using std::cout;
using std::endl;
using std::ends;

//#include <list>
#include "list.hpp"
//using std::list;




void vector_test()
{
	class A
	{
	public:
		A():n(1){}
		A(const A &a) : n(a.n + 10)
		{
			n = a.n + 10;
		}

		void func() const
		{
			cout << "\tconst member function\n";
		}
		A& operator = (const A &a)
		{
			n = a.n + 100;
			return *this;
		}
		int n;
	};

	class NoDefaultConstructorClass
	{
	public:
		NoDefaultConstructorClass(int n){}
	};

	//void multi_file_test();
	//multi_file_test();
	cout << "\nVector Test:\n";
	{
		cout << "\tdefault constructor test(with non-default-constructor class):\n";
		vector<NoDefaultConstructorClass> v;
		assert(0 == v.size());
		assert(true == v.empty());
		NoDefaultConstructorClass c(1);
		v.push_back(c);
		v.resize(10, c);	// important for default constructor

		// constructur with iterator and assign function test
		cout <<"\tconstructur and assign function test\n";
		vector<unsigned int> vui;
		vui.assign(10, 100);

		xf::list<int> li;
		li.push_back(1);
		li.push_back(2);
		li.push_back(3);
		// µü´úÆ÷²âÊÔ
		vector<int> vv(li.begin(), li.end());
		assert(1 == vv[0]);
		assert(2 == vv[1]);
		assert(3 == vv[2]);
		vv.assign(li.begin(), li.end());
		assert(1 == vv[0]);
		assert(2 == vv[1]);
		assert(3 == vv[2]);
	
		vector<string> vs;
		vs.push_back("\tabc");
		assert("\tabc" == vs[0]);
			
	}
	// assign, front, back, push, pop, clear
	vector<int> v1;
	{
		// default constructor
		cout << "\tdefault constructor\n";
		assert(0 == v1.size());
		assert(0 == v1.capacity());
		
		// empty test
		cout << "\tempty test\n";
		assert(true == v1.empty());

		// assign
		cout << "\tassign\n";
		v1.assign(10, 2);
		assert(10 == v1.size());
		assert(10 == v1.capacity());
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			assert(*iter == 2);
		}

		// empty test
		cout << "\tempty test\n";
		assert(false == v1.empty());

		// re-assign
		cout << "\tre-assign\n";
		v1.assign(5, 7);
		assert(5 == v1.size());
		assert(10 == v1.capacity());
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			assert(7 == *iter);
		}
		
		// front, back
		cout << "\tfront, back\n";
		assert(7 == v1.front());
		assert(7 == v1.back());
		assert(2 == (v1.front() = 2));
		assert(3 == (v1.front() = 3));

		// pop
		cout << "\tpop\n";
		v1.pop_back();
		v1.pop_back();
		assert(3 == v1.size());
		assert(10 == v1.capacity());
		int banchmark1[] = {3,7,7};
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			assert(*iter == banchmark1[distance(v1.begin(), iter)]);
		}

		// push
		cout << "\tpush\n";
		v1.push_back(1);
		v1.push_back(2);
		assert(5 == v1.size());
		assert(10 == v1.capacity());
		int banchmark2[] = {3, 7, 7, 1, 2};
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			assert(*iter == banchmark2[distance(v1.begin(), iter)]);
		}

		// clear
		cout << "\tclear\n";
		v1.clear();
		assert(0 == v1.size());
		assert(10 == v1.capacity());
		for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			assert(false);
		}

		// empty test
		cout << "\tempty test\n";
		assert(true == v1.empty());
	}

	// resize and reserve
	vector<A> v2(10);
	{
		cout << "\tconstructor with count 10\n";
		assert(10 == v2.size());
		assert(10 == v2.capacity());
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			assert(iter->n == 1);
		}

		// resize smaller
		cout << "\tresize smaller\n";
		v2.resize(2);
		assert(2 == v2.size());
		assert(10 == v2.capacity());
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			assert(iter->n == 1);
		}

		// resize larger
		cout << "\tresize larger\n";
		v2.resize(12);
		assert(12 == v2.size());
		assert(12 == v2.capacity());
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			assert(iter->n == 11);
		}

		// reserve smaller
		cout << "\treserve smaller\n";
		v2.reserve(8);
		assert(12 == v2.size());
		assert(12 == v2.capacity());
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			assert(iter->n == 11);
		}

		// reserve larger
		cout << "\treserve larger\n";
		v2.reserve(18);
		assert(12 == v2.size());
		assert(18 == v2.capacity());
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			assert(iter->n == 21);
		}

		// shrink to fit
		cout << "\tshrink to fit\n";
		v2.shrink_to_fit();
		assert(12 == v2.size());
		assert(12 == v2.capacity());
		for(vector<A>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			assert(iter->n == 31);
		}
		
	}

	// =, [], at, data
	vector<A> v3(v2);
	{
		// copy constructor 
		cout << "\tcopy constructor \n";
		assert(12 == v3.size());
		assert(12 == v3.capacity());
		for(vector<A>::iterator iter = v3.begin(); iter != v3.end(); ++iter)
		{
			assert(iter->n == 41);
		}

		// operator = 
		cout << "\toperator = \n";
		v3 = v2;
		assert(12 == v3.size());
		assert(12 == v3.capacity());
		for(vector<A>::iterator iter = v3.begin(); iter != v3.end(); ++iter)
		{
			assert(iter->n == 131);
		}

		// operator [] 
		cout << "\toperator [] \n";
		for(size_t i = 0; i < v3.size(); ++i)
		{
			assert(v3[i].n == 131);
		}

		// at 
		cout << "\toperator at \n";
		
		for(size_t i = 0; i < v3.size(); ++i)
		{
			assert(v3.at(i).n == 131);
		}

		// data
		cout << "\tdata\n";
		const vector<A> v4(v3);
		A *pa = v3.data();
		size_t size = v3.size();
		const A *cpa = v4.data();
		for(size_t i = 0; i < size; ++i)
		{
			assert(131 == pa[i].n);
			pa[i].n -= 10;
		}
		for(size_t i = 0; i < size; ++i)
		{
			assert(121 == v3[i].n);	
		}
		// data const
		cout << "\tdata const\n";
		for(size_t i = 0; i < size; ++i)
		{
			assert(141 == v4[i].n);
		}
		
	}

	// iterator
	int a[10] = {1,3,5,7,9,2,4,6,8,10};
	vector<int> v4(a, a + 10);
	{
		// iterator compare
		v4.cbegin() == v4.begin();
		//v4.begin() == v4.cbegin();	// TODO friend comparer outside class definition

		// iterator preorder ++
		cout << "\titerator preorder ++\n";
		assert(10 == v4.size());
		assert(10 == v4.capacity());
		for(vector<int>::iterator iter = v4.begin(); iter != v4.end(); ++iter)
		{
			int i = distance(v4.begin(), iter);
			if(i < 5)
			{
				assert(i * 2 + 1 == *iter);
			}
			else
			{
				assert((i - 4) * 2 == *iter);
			}
			vector<int>::iterator next_iter = ++iter;
			if(i < 4)
			{
				assert(i * 2 + 3 == *next_iter);
			}
			else
			{
				assert((i - 3) * 2 == *next_iter);
			}
			//*iter = 1;	// no error
		}
		//

		// iterator postorder ++
		cout << "\titerator postorder ++\n";
		for(vector<int>::iterator iter = v4.begin(); iter != v4.end(); iter++)
		{
			int i = distance(v4.begin(), iter);
			if(i < 5)
			{
				assert(i * 2 + 1 == *iter);
			}
			else
			{
				assert((i - 4) * 2 == *iter);
			}
			
			vector<int>::iterator next_iter = (iter++) + 1;
			if(i < 4)
			{
				assert(i * 2 + 3 == *next_iter);
			}
			else
			{
				assert((i - 3) * 2 == *next_iter);
			}
			//*iter = 1;	// no error
		}
		

		// iterator +
		cout << "\titerator +\n";
		for(vector<int>::iterator iter = v4.begin(); iter != v4.end(); iter += 2)
		{
			int i = distance(v4.begin(), iter);
			if(i < 5)
			{
				assert(i * 2 + 1 == *iter);
			}
			else
			{
				assert((i - 4) * 2 == *iter);
			}
			vector<int>::iterator next_iter = iter + 1;
			if(i < 4)
			{
				assert(i * 2 + 3 == *next_iter);
			}
			else
			{
				assert((i - 3) * 2 == *next_iter);
			}
		}


		// iterator preorder --
		cout << "\titerator preorder --\n";
		
		for(vector<int>::iterator iter = v4.end() - 1; iter != v4.begin() - 1; --iter)
		{
			int i = distance(v4.begin(), iter);
			if(i < 5)
			{
				assert(i * 2 + 1 == *iter);
			}
			else
			{
				assert((i - 4) * 2 == *iter);
			}
			vector<int>::iterator next_iter = --iter;
			if(i < 6)
			{
				assert(i * 2 - 1 == *next_iter);
			}
			else
			{
				assert((i - 5) * 2 == *next_iter);
			}
		}

		// iterator postorder --
		cout << "\titerator postorder --\n";
		for(vector<int>::iterator iter = v4.end() - 1; iter != v4.begin() - 1; iter--)
		{
			int i = distance(v4.begin(), iter);
			if(i < 5)
			{
				assert(i * 2 + 1 == *iter);
			}
			else
			{
				assert((i - 4) * 2 == *iter);
			}
			vector<int>::iterator next_iter = (iter--) - 1;
			if(i < 6)
			{
				assert(i * 2 - 1 == *next_iter);
			}
			else
			{
				assert((i - 5) * 2 == *next_iter);
			}
		}

		// iterator -
		cout << "\titerator -\n";
		for(vector<int>::iterator iter = v4.end() - 1; iter != v4.begin() - 1; iter -= 2)
		{
			int i = distance(v4.begin(), iter);
			if(i < 5)
			{
				assert(i * 2 + 1 == *iter);
			}
			else
			{
				assert((i - 4) * 2 == *iter);
			}
			vector<int>::iterator next_iter = iter - 1;
			if(i < 6)
			{
				assert(i * 2 - 1 == *next_iter);
			}
			else
			{
				assert((i - 5) * 2 == *next_iter);
			}
		}

		// const iterator preorder ++
		cout << "\tconst iterator preorder ++\n";
		for(vector<int>::const_iterator iter = v4.begin(); iter != v4.end(); ++iter)
		{
			int i = distance(v4.cbegin(), iter);
			if(i < 5)
			{
				assert(i * 2 + 1 == *iter);
			}
			else
			{
				assert((i - 4) * 2 == *iter);
			}
			vector<int>::const_iterator next_iter = ++iter;
			if(i < 4)
			{
				assert(i * 2 + 3 == *next_iter);
			}
			else
			{
				assert((i - 3) * 2 == *next_iter);
			}
		}

		// const iterator postorder ++
		cout << "\tconst iterator postorder ++\n";
		for(vector<int>::const_iterator iter = v4.begin(); iter != v4.end(); iter++)
		{
			int i = distance(v4.cbegin(), iter);
			if(i < 5)
			{
				assert(i * 2 + 1 == *iter);
			}
			else
			{
				assert((i - 4) * 2 == *iter);
			}
			vector<int>::const_iterator next_iter = (iter++) + 1;
			if(i < 4)
			{
				assert(i * 2 + 3 == *next_iter);
			}
			else
			{
				assert((i - 3) * 2 == *next_iter);
			}
		}

		// const iterator +
		cout << "\tconst iterator +\n";
		
		for(vector<int>::const_iterator iter = v4.begin(); iter != v4.end(); iter += 2)
		{
			int i = distance(v4.cbegin(), iter);
			if(i < 5)
			{
				assert(i * 2 + 1 == *iter);
			}
			else
			{
				assert((i - 4) * 2 == *iter);
			}
			vector<int>::const_iterator next_iter = iter + 1;
			if(i < 4)
			{
				assert(i * 2 + 3 == *next_iter);
			}
			else
			{
				assert((i - 3) * 2 == *next_iter);
			}
		}

		// const iterator preorder --
		cout << "\tconst iterator preorder --\n";
		for(vector<int>::const_iterator iter = v4.end() - 1; iter >= v4.begin(); --iter)
		{
			int i = distance(v4.cbegin(), iter);
			if(i < 5)
			{
				assert(i * 2 + 1 == *iter);
			}
			else
			{
				assert((i - 4) * 2 == *iter);
			}
			vector<int>::const_iterator next_iter = --iter;
			if(i < 6)
			{
				assert(i * 2 - 1 == *next_iter);
			}
			else
			{
				assert((i - 5) * 2 == *next_iter);
			}
		}

		// const iterator postorder --
		cout << "\tconst iterator postorder --\n";
		for(vector<int>::const_iterator iter = v4.end() - 1; iter >= v4.begin(); iter--)
		{
			int i = distance(v4.cbegin(), iter);
			if(i < 5)
			{
				assert(i * 2 + 1 == *iter);
			}
			else
			{
				assert((i - 4) * 2 == *iter);
			}
			vector<int>::const_iterator next_iter = (iter--) - 1;
			if(i < 6)
			{
				assert(i * 2 - 1 == *next_iter);
			}
			else
			{
				assert((i - 5) * 2 == *next_iter);
			}
		}

		// const iterator -
		cout << "\tconst iterator -\n";
		for(vector<int>::const_iterator iter = v4.end() - 1; iter >= v4.begin(); iter -= 2)
		{
			int i = distance(v4.cbegin(), iter);
			if(i < 5)
			{
				assert(i * 2 + 1 == *iter);
			}
			else
			{
				assert((i - 4) * 2 == *iter);
			}
			vector<int>::const_iterator next_iter = iter - 1;
			if(i < 6)
			{
				assert(i * 2 - 1 == *next_iter);
			}
			else
			{
				assert((i - 5) * 2 == *next_iter);
			}
		}

		// reverse iterator preorder ++ 
		cout << "\treverse iterator preorder ++\n";
		for(vector<int>::reverse_iterator iter = v4.rbegin(); iter < v4.rend() - 1; ++iter)
		{
			int i = distance(v4.rbegin(), iter);
			if(i < 5)
			{
				assert((5 - i) * 2 == *iter);
			}
			else
			{
				assert((9 - i) * 2 + 1 == *iter);
			}
			vector<int>::reverse_iterator next_iter = ++iter;
			if(i < 4)
			{
				assert((4 - i) * 2 == *next_iter);
			}
			else
			{
				assert((8 - i) * 2 + 1 == *next_iter);
			}
			//*iter = 1;	// no error
		}

		// reverse iterator postorder ++ 
		cout << "\treverse iterator postorder ++\n";
		
		for(vector<int>::reverse_iterator iter = v4.rbegin(); iter < v4.rend(); iter++)
		{
			int i = distance(v4.rbegin(), iter);
			if(i < 5)
			{
				assert((5 - i) * 2 == *iter);
			}
			else
			{
				assert((9 - i) * 2 + 1 == *iter);
			}
			vector<int>::reverse_iterator next_iter = (iter++) + 1;
			if(i < 4)
			{
				assert((4 - i) * 2 == *next_iter);
			}
			else
			{
				assert((8 - i) * 2 + 1 == *next_iter);
			}
			//*iter = 1;	// no error
		}
		
		// reverse iterator +
		cout << "\treverse iterator +\n";
		
		for(vector<int>::reverse_iterator iter = v4.rbegin(); iter != v4.rend(); iter += 2)
		{
			int i = distance(v4.rbegin(), iter);
			if(i < 5)
			{
				assert((5 - i) * 2 == *iter);
			}
			else
			{
				assert((9 - i) * 2 + 1 == *iter);
			}
			vector<int>::reverse_iterator next_iter = iter + 1;
			if(i < 4)
			{
				assert((4 - i) * 2 == *next_iter);
			}
			else
			{
				assert((8 - i) * 2 + 1 == *next_iter);
			}
		}

		// reverse iterator preorder --
		cout << "\treverse iterator preorder --\n";
		for(vector<int>::reverse_iterator iter = v4.rend() - 1; iter >= v4.rbegin(); --iter)
		{
			int i = distance(v4.rbegin(), iter);
			if(i < 5)
			{
				assert((5 - i) * 2 == *iter);
			}
			else
			{
				assert((9 - i) * 2 + 1 == *iter);
			}
			vector<int>::reverse_iterator next_iter = --iter;
			if(i < 6)
			{
				assert((6 - i) * 2 == *next_iter);
			}
			else
			{
				assert((10 - i) * 2 + 1 == *next_iter);
			}
		}
		// reverse iterator postorder --
		cout << "\treverse iterator postorder --\n";
		for(vector<int>::reverse_iterator iter = v4.rend() - 1; iter != v4.rbegin() - 1; iter--)
		{
			int i = distance(v4.rbegin(), iter);
			if(i < 5)
			{
				assert((5 - i) * 2 == *iter);
			}
			else
			{
				assert((9 - i) * 2 + 1 == *iter);
			}
			vector<int>::reverse_iterator next_iter = (iter--) - 1;
			if(i < 6)
			{
				assert((6 - i) * 2 == *next_iter);
			}
			else
			{
				assert((10 - i) * 2 + 1 == *next_iter);
			}
		}

		// reverse iterator -
		cout << "\treverse iterator -\n";
		for(vector<int>::reverse_iterator iter = v4.rend() - 1; iter >= v4.rbegin(); iter -= 2)
		{
			int i = distance(v4.rbegin(), iter);
			if(i < 5)
			{
				assert((5 - i) * 2 == *iter);
			}
			else
			{
				assert((9 - i) * 2 + 1 == *iter);
			}
			vector<int>::reverse_iterator next_iter = iter - 1;
			if(i < 6)
			{
				assert((6 - i) * 2 == *next_iter);
			}
			else
			{
				assert((10 - i) * 2 + 1 == *next_iter);
			}
		}

		// const reverse iterator preorder ++ 
		cout << "\tconst reverse iterator preorder ++\n";
		for(vector<int>::const_reverse_iterator iter = v4.rbegin(); iter != v4.rend(); ++iter)
		{
			int i = distance(v4.crbegin(), iter);
			if(i < 5)
			{
				assert((5 - i) * 2 == *iter);
			}
			else
			{
				assert((9 - i) * 2 + 1 == *iter);
			}
			vector<int>::const_reverse_iterator next_iter = ++iter;
			if(i < 4)
			{
				assert((4 - i) * 2 == *next_iter);
			}
			else
			{
				assert((8 - i) * 2 + 1 == *next_iter);
			}
			//*iter = 1;	// error
		}
		// const reverse iterator postorder ++ 
		cout << "\tconst reverse iterator postorder ++\n";
		for(vector<int>::const_reverse_iterator iter = v4.rbegin(); iter != v4.rend(); iter++)
		{
			int i = distance(v4.crbegin(), iter);
			if(i < 5)
			{
				assert((5 - i) * 2 == *iter);
			}
			else
			{
				assert((9 - i) * 2 + 1 == *iter);
			}
			vector<int>::const_reverse_iterator next_iter = (iter++) + 1;
			if(i < 4)
			{
				assert((4 - i) * 2 == *next_iter);
			}
			else
			{
				assert((8 - i) * 2 + 1 == *next_iter);
			}
			//*iter = 1;	// error
		}

		// const reverse iterator +
		cout << "\tconst reverse iterator +\n";
		for(vector<int>::const_reverse_iterator iter = v4.rbegin(); iter != v4.rend(); iter += 2)
		{
			int i = distance(v4.crbegin(), iter);
			if(i < 5)
			{
				assert((5 - i) * 2 == *iter);
			}
			else
			{
				assert((9 - i) * 2 + 1 == *iter);
			}
			vector<int>::const_reverse_iterator next_iter = iter + 1;
			if(i < 4)
			{
				assert((4 - i) * 2 == *next_iter);
			}
			else
			{
				assert((8 - i) * 2 + 1 == *next_iter);
			}
		}

		// const reverse iterator preorder --
		cout << "\tconst reverse iterator preorder iterator --\n";
		for(vector<int>::const_reverse_iterator iter = v4.rend() - 1; iter != v4.rbegin() - 1; --iter)
		{
			int i = distance(v4.crbegin(), iter);
			if(i < 5)
			{
				assert((5 - i) * 2 == *iter);
			}
			else
			{
				assert((9 - i) * 2 + 1 == *iter);
			}
			vector<int>::const_reverse_iterator next_iter = --iter;
			if(i < 6)
			{
				assert((6 - i) * 2 == *next_iter);
			}
			else
			{
				assert((10 - i) * 2 + 1 == *next_iter);
			}
		}
		
		// const reverse iterator postorder --
		cout << "\tconst reverse iterator postorder iterator --\n";
		for(vector<int>::const_reverse_iterator iter = v4.rend() - 1; iter != v4.rbegin() - 1; iter--)
		{
			int i = distance(v4.crbegin(), iter);
			if(i < 5)
			{
				assert((5 - i) * 2 == *iter);
			}
			else
			{
				assert((9 - i) * 2 + 1 == *iter);
			}
			vector<int>::const_reverse_iterator next_iter = (iter--) - 1;
			if(i < 6)
			{
				assert((6 - i) * 2 == *next_iter);
			}
			else
			{
				assert((10 - i) * 2 + 1 == *next_iter);
			}
		}

		// const reverse iterator -
		cout << "\tconst reverse iterator -\n";
		for(vector<int>::const_reverse_iterator iter = v4.rend() - 1; iter != v4.rbegin() - 1; iter -= 2)
		{
			int i = distance(v4.crbegin(), iter);
			if(i < 5)
			{
				assert((5 - i) * 2 == *iter);
			}
			else
			{
				assert((9 - i) * 2 + 1 == *iter);
			}
			vector<int>::const_reverse_iterator next_iter = iter - 1;
			if(i < 6)
			{
				assert((6 - i) * 2 == *next_iter);
			}
			else
			{
				assert((10 - i) * 2 + 1 == *next_iter);
			}
		}
		

		// transformation between reverse and forward iterator
		{
			cout << "\ttransformation between reverse and forward iterator\n";
			vector<int>::reverse_iterator r_iter = v4.rbegin();
			assert(*r_iter == 10);
			++r_iter;
			assert(*r_iter == 8);
			++r_iter;
			vector<int>::iterator iter = r_iter.base();
			assert(*iter == 8);
			++iter;
			assert(*iter == 10);
		}

		// transformation between const reverse and const forward const iterator
		{
			cout << "\ttransformation between const reverse and const forward const iterator\n";
			vector<int>::const_reverse_iterator cr_iter = v4.rbegin();
			assert(*cr_iter == 10);
			++cr_iter;
			assert(*cr_iter == 8);
			++cr_iter;
			vector<int>::const_iterator c_iter = cr_iter.base();
			assert(*c_iter == 8);
			++c_iter;
			assert(*c_iter == 10);
		}

		// erase
		{
			// erase(_Where)
			cout << "\terase(_Where)\n";
			vector<int>::iterator iter = v4.begin();
			++iter;
			iter = v4.erase(iter);
			
			for(vector<int>::const_iterator c_iter = v4.begin(); c_iter != v4.end(); ++c_iter)
			{
				int i = distance(v4.cbegin(), c_iter);
				if(0 == i)
				{
					assert(1 == *c_iter);
				}
				else if(i < 4)
				{
					assert(i * 2 + 3 == *c_iter);
				}
				else
				{
					assert(i * 2 - 6 == *c_iter);
				}
			}
			while(iter != v4.end())
			{
				int i = distance(v4.begin(), iter);
				if(0 == i)
				{
					assert(1 == *iter);
				}
				else if(i < 4)
				{
					assert(i * 2 + 3 == *iter);
				}
				else
				{
					assert(i * 2 - 6 == *iter);
				}
				++iter;
			}

			// erase(_First, _Last)
			cout << "\terase(_First, _Last)\n";
			iter = v4.begin();
			vector<int>::iterator iter2 = iter + 2;
			iter = v4.erase(iter, iter2);
			int benchmark1[] = {7,9,2,4,6,8,10};
			for(vector<int>::const_iterator c_iter = v4.begin(); c_iter != v4.end(); ++c_iter)
			{
				assert(*c_iter == benchmark1[distance(v4.cbegin(), c_iter)]);
			}
			while(iter != v4.end())
			{
				assert(*iter == benchmark1[distance(v4.begin(), iter)]);
				++iter;
			}
		}

		// insert
		{
			// insert(_Where, _Value)
			vector<int> v5;
			cout << "\tinsert(_Where, _Value)\n";
			vector<int>::iterator iter = v5.insert(v5.begin(), 1);
			assert(*iter == 1);
			assert(1 == v5.size());
			v5.clear();
			iter = v5.insert(v5.end(), 1);
			assert(*iter == 1);
			assert(1 == v5.size());
			

			iter = v5.insert(v5.end(), 3);
			int benchmark1[] = {1, 3};
			for(vector<int>::const_iterator c_iter = v5.begin(); c_iter != v5.end(); ++c_iter)
			{
				assert(*c_iter == benchmark1[distance(v5.cbegin(), c_iter)]);
			}
			assert(*iter == 3);

			// insert(_Where, _Count, _Value)
			cout << "\tinsert(_Where, _Count, _Value)\n";
			iter = v5.insert(v5.begin() + 1, 3, 333);
			int benchmark2[] = {1, 333, 333, 333, 3};
			for(vector<int>::const_iterator c_iter = v5.begin(); c_iter != v5.end(); ++c_iter)
			{
				assert(*c_iter == benchmark2[distance(v5.cbegin(), c_iter)]);
			}
			assert(*iter == 333);

			// insert(_Where, _First, _Last)
			cout << "\tinsert(_Where, _First, _Last)\n";
			int a[] = {123, 321, 213};
			iter = v5.insert(v5.begin() + 1, a, a + 3);
			int benchmark3[] = {1, 123, 321, 213, 333, 333, 333, 3};
			for(vector<int>::const_iterator c_iter = v5.begin(); c_iter != v5.end(); ++c_iter)
			{
				assert(*c_iter == benchmark3[distance(v5.cbegin(), c_iter)]);
			}
			assert(*iter == 123);

			cout << "\tinsert into vector from list";
			v5.clear();
			xf::list<int> l(a, a + 3);
			v5.insert(v5.begin(), l.begin(), l.end());
			assert(3 == v5.size());
			for(int i = 0; i < 3; ++i)
			{
				//cout << v5[i] << ' ';
				assert(a[i] == v5[i]);
			}
		}

		// iterator assignment
		cout << "\titerator assignment\n";
		cout << "\titerator\n";
		for(vector<int>::iterator iter = v4.begin(); iter != v4.end(); ++iter)
		{
			*iter = 123;
		}
		for(vector<int>::iterator iter = v4.begin(); iter != v4.end(); ++iter)
		{
			assert(123 == *iter);
		}

		cout << "\treverse iterator\n";
		for(vector<int>::reverse_iterator iter = v4.rbegin(); iter != v4.rend(); ++iter)
		{
			*iter = 321;
		}
		for(vector<int>::reverse_iterator iter = v4.rbegin(); iter != v4.rend(); ++iter)
		{
			assert(321 == *iter);
		}
	}

	// another constructor
	vector<double> v5(10, 1.5);
	{
		// constructor with count and value
		cout << "\tconstructor with count and value\n";
		assert(10 == v5.size());
		assert(10 == v5.capacity());
		for(vector<double>::iterator iter = v5.begin(); iter != v5.end(); ++iter)
		{
			assert(1.5 == *iter);
		}
	}
	
	// another constructor
	vector<int> v6(10, 15);
	{
		// constructor with count and value to test the template specialization
		cout << "\tconstructor with count and value, to test the template specialization\n";
		assert(10 == v6.size());
		assert(10 == v6.capacity());
		for(vector<int>::iterator iter = v6.begin(); iter != v6.end(); ++iter)
		{
			assert(15 == *iter);
		}
	}

	// max_size
	{
		cout << "\tmax size\n";
		assert(4294967295U / sizeof(int) == v1.max_size());
		assert(4294967295U / sizeof(int) == v2.max_size());
		assert(4294967295U / sizeof(int) == v3.max_size());
		assert(4294967295U / sizeof(int) == v4.max_size());
		assert(4294967295U / sizeof(double) == v5.max_size());
	}

	
}