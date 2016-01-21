
#include <iostream>
#include "vector.hpp"
using xf::vector;
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
	vector<int> v1(v);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	int a[10] = {1,3,5,7,9,2,4,6,8,10};
	vector<float> v2(a, a + 10);
	for(vector<int>::const_iterator iter = v1.begin(); iter != v1.end(); ++iter)
	{
		cout << *iter << ' ';
		++iter;
		--iter;
	}
	cout << endl;
	for(vector<float>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
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
	return 0;
}