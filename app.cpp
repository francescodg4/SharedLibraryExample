#include "mylibrary.h"
#include <stdio.h>

int main()
{
	while(1) {
		printf("Value = %d\n", MyLibrary::get_value());
		MyLibrary::increment();
		MyLibrary::wait_sleep(1);
	}

	
	return 0;
}
