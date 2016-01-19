
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
	/*for(vector<T>::const_iterator iter = v.begin(); iter != v.end(); ++iter)
	{
		cout << *iter << ' ';
	}*/
	cout << endl;
}

int main()
{
	//_Iter<int> i;
	vector<int> v(1 << 3);
//	vector<int> v(5);
	print_vector(v);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	print_vector(v);
	v.pop_back();
	v.pop_back();
	v.pop_back();
	print_vector(v);
	v.reserve(10);
	print_vector(v);
	v.reserve(2);
	print_vector(v);
	v.resize(10);
	print_vector(v);
	v.resize(1);
	print_vector(v);
	v.resize(10);
	print_vector(v);
	cout << v.max_size() << endl; 
	//example<int> e;

	return 0;
}