#pragma once

#include <string>
#include <vector>

namespace MyLibrary {	
	void increment();
	int get_value();
	void wait_sleep(int seconds);
	void print_usb_version();
	std::vector<std::string> list_usb_devices();
}
