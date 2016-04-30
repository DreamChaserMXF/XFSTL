#include "deque.hpp"
#include <iostream>

using xf::deque;
using std::cout;
using std::endl;


class NoDefaultConstructorClass
{
public:
	NoDefaultConstructorClass(int n){}
};

void deque_test()
{
	cout << "\ndeque test:\n";
	{
		cout << "default constructor test:\n";
		deque<NoDefaultConstructorClass> d;
		cout << "\tsize: " << d.size();
		cout << "\n\tisempty: " << std::boolalpha << d.empty() << std::noboolalpha;
		cout << endl;
		cout << "default constructor with class wihtout default constructor:\n";
		NoDefaultConstructorClass c(1);
		d.push_back(c);
	}
	{
		cout << "constructor with size:\n";
		deque<double> d(10);
		for(int i = 0; i < 10; ++i)
		{
			cout << d[i] << ' ';
		}
		cout << '\n';
	}
	{
		cout << "constructor with size and value:\n";
		deque<double> d(10, 3.3);
		for(int i = 0; i < 10; ++i)
		{
			cout << d[i] << ' ';
		}
		cout << '\n';
	}
	{
		cout << "push_back test:\n";
		deque<int> d;
		d.push_back(0);
		d.push_back(1);
		d.push_back(2);
		d.push_back(3);
		d.push_back(4);
		d.push_back(5);
		d.push_back(6);
		d.push_back(7);
		d.push_back(8);
		d.push_back(9);
		cout << '\t';
		for(int i = 0; i < 10; ++i)
		{
			cout << d[i] << ' ';
		}
		cout << '\n';
	}
	{
		cout << "push_front test:\n";
		deque<int> d;
		d.push_front(9);
		d.push_front(8);
		d.push_front(7);
		d.push_front(6);
		d.push_front(5);
		d.push_front(4);
		d.push_front(3);
		d.push_front(2);
		d.push_front(1);
		d.push_front(0);
		cout << '\t';
		for(int i = 0; i < 10; ++i)
		{
			cout << d[i] << ' ';
		}
		cout << '\n';
	}
	{
		cout << "iterator constructor test:\n";
		int a[] = {0,1,2,3,4,5,6,7,8,9,};
		deque<int> d(a, a + 10);
		cout << '\t';
		for(int i = 0; i < 10; ++i)
		{
			cout << d[i] << ' ';
		}
		cout << '\n';
		cout << "copy constructor test:\n";
		deque<int> d1(d);
		cout << '\t';
		for(int i = 0; i < 10; ++i)
		{
			cout << d1[i] << ' ';
		}
		cout << '\n';
	}

}