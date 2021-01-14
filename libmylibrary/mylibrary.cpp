#include "mylibrary.h"
#include <cstdlib>

int *a = NULL;

void init()
{
	if (!a)
	{
		a = new int();
	}
}

void increment()
{
	if (a) *a += 1;
}

int get_value()
{
	return (a) ? *a : 0;
}

int *accessor()
{
	return a;
}
