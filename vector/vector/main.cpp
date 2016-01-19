
#include <iostream>
#include "vector.hpp"

using std::cout;
using std::endl;
using std::ends;
#define TEST_VECTOR

template<class T>
void print_vector(const vector<T> &v)
{
	cout << "size: " << v.size() << "\t\tcapacity: " << v.capacity() << endl;
	cout << "element: ";
	for(int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << ' ';
	}
	cout << endl;
	for(vector<T>::const_iterator iter = v.begin(); iter != v.end(); ++iter)
	{
		cout << *iter << ' ';
		++iter;
		--iter;
	}
	cout << endl;
}

template<class T>
void reverse_print_vector(const vector<T> &v)
{
	cout << "size: " << v.size() << "\t\tcapacity: " << v.capacity() << endl;
	cout << "element: ";
	
	for(vector<T>::reverse_const_iterator iter = v.rbegin(); iter != v.rend(); ++iter)
	{
		cout << *iter << ' ';
		++iter;
		--iter;
	}
	cout << endl;
}

int main()
{
	vector<int> v(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	for(vector<int>::const_iterator iter = v.begin(); iter != v.end(); ++iter)
	{
		cout << *iter << ' ';
		++iter;
		--iter;
	}
	cout << endl;
	for(vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter)
	{
		cout << *iter << ' ';
		++iter;
		--iter;
	}
	cout << endl;
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
	return 0;
}