#include <stdio.h>
#include "stack.hpp"
using xf::stack;
void stack_test()
{
	printf("\tStack Test:\n");
	printf("\t\tdefault constructor test:\n");
	stack<int> stk;
	
	printf("\t\tsize & empty test:\n");
	assert(0 == stk.size());
	assert(true == stk.empty());
	
	printf("\t\tpush test:\n");
	for(size_t i = 0; i < 100; ++i)
	{
		stk.push(i);
	}
	assert(100 == stk.size());
	assert(false == stk.empty());
	
	printf("\t\tpop test:\n");
	for(size_t i = 0; i < 50; ++i)
	{
		assert(100 - i == stk.size());
		assert(99 - i == stk.top());
		stk.pop();
	}
	assert(50 == stk.size());
	assert(false == stk.empty());

	printf("\t\tcopy constructor test:\n");
	stack<int> stk2(stk);
	assert(50 == stk2.size());
	assert(false == stk2.empty());
	for(size_t i = 50; i < 100; ++i)
	{
		assert(100 - i == stk2.size());
		assert(99 - i == stk2.top());
		stk2.pop();
	}

	printf("\t\tconstructor with container:\n");
	xf::deque<int> d;
	d.push_back(1);
	d.push_back(2);
	d.push_back(3);
	xf::stack<int> stk3(d);
	assert(3 == stk3.size());
	assert(false == stk3.empty());

	printf("\t\tclear test:\n");
	assert(50 == stk.size());
	assert(false == stk.empty());
	stk.clear();
	assert(0 == stk.size());
	assert(true == stk.empty());
}