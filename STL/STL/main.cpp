#include <iostream>
#include "vector.hpp"
#include "deque.hpp"
void vector_test();
void list_test();
void deque_test();
void adapter_test();
void multi_file_test();
void sort_test();
void string_test();

int main()
{
	//xf::vector<int> va;

	//std::cout << sizeof(xf::vector<int>) << std::endl;

	//xf::deque<int> d;
	//std::cout << d.size() << std::endl;
	//d.push_back(1);
	//std::cout << d.size() << std::endl;

	multi_file_test();

	vector_test();
	list_test();
	deque_test();
	adapter_test();
	sort_test();
	string_test();



	return 0;
}