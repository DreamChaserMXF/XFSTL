
// @fatal error: vector静态变量初始化出错

#include "vector.hpp"
#include <memory>

void func()
{
	xf::vector<int> vi;
	xf::vector<double> vd;
}

