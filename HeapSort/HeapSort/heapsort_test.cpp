#include <stdio.h>
#include "heapsort.hpp"

void heapsort_test()
{
	int a[] = {1,3,5,7,9,2,4,6,8,10};
	int length = sizeof(a) / sizeof(a[0]);
	heapsort(a, a + length);
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}