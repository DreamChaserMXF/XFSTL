
// @fatal error: vector静态变量初始化出错
#include <iostream>
#include "vector.hpp"
// initialize static member alc
//
void func()
{
	xf::vector<double> vd;
	xf::vector<int> vi;
}