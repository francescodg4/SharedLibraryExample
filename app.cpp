#include "mylibrary.h"
#include <stdio.h>
#include <unistd.h>

int main()
{
	init();
	
	// while(1) {
	// 	printf("Value = %d\n", get_value());
	// 	increment();
	// 	sleep(1);
	// }

	int *a_ptr = accessor();

	printf("a = %d\n", *a_ptr);
	increment();
	printf("a = %d\n", *a_ptr);
	
	delete a_ptr;
	
	return 0;
}
