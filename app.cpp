#include "mylibrary.h"
#include <stdio.h>
#include <iostream>


int main()
{
	MyLibrary::print_usb_version();

	auto devices = MyLibrary::list_usb_devices();

	std::cout << devices.size() << std::endl;

	for (std::string device : MyLibrary::list_usb_devices())
	{
		std::cout << device << std::endl;
	}

	
	// while(1) {
	// 	printf("Value = %d\n", MyLibrary::get_value());
	// 	MyLibrary::increment();
	// 	MyLibrary::wait_sleep(1);
	// }
		
	return 0;
}
