#include "mylibrary.h"
#include <cstdlib>

static int a = 0;

void MyLibrary::increment()
{
	a += 1;
}

int MyLibrary::get_value()
{
	return a;
}
