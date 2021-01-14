#include "mylibrary.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <libusb.h>
#include <cstring>

static int a = 0;

void MyLibrary::increment()
{
	a += 1;
}

int MyLibrary::get_value()
{
	return a;
}

static std::string device_class_to_string(uint8_t bDeviceClass)
{
	switch(bDeviceClass)
	{
	case LIBUSB_CLASS_PER_INTERFACE:
		return "ClassPerInterface";
	case LIBUSB_CLASS_AUDIO:
		return "Audio";
	case LIBUSB_CLASS_HID:
		return "Human Interface Device";
	case LIBUSB_CLASS_HUB:
		return "Hub";
	case LIBUSB_CLASS_WIRELESS:
		return "Wireless";
	default:
		return "";
	}

	return "";
}

std::vector<std::string> MyLibrary::list_usb_devices()
{
	std::vector<std::string> devices;
	
	if (libusb_init(NULL) < 0)
		return devices;
	
	libusb_device **devs;
	ssize_t n_devices = libusb_get_device_list(NULL, &devs);
		
	int i = 0, j = 0;
	uint8_t path[8];
	
	libusb_device *dev;
	
	while ((dev = devs[i++]) != NULL)
	{
		struct libusb_device_descriptor desc;
		int ret = libusb_get_device_descriptor(dev, &desc);

		if (ret < 0)
			break;

		int n_ports = libusb_get_port_numbers(dev, path, sizeof(path));						      

		unsigned char manufacturer_str[256];

		memset(manufacturer_str, 0, sizeof(manufacturer_str));

		libusb_device_handle *handle = NULL;
		
		ret = libusb_open(dev, &handle);

		std::cout << "libusb_open" << ret << std::endl;

		if (handle) 
			libusb_get_string_descriptor_ascii(handle, desc.iManufacturer, manufacturer_str, sizeof(manufacturer_str));

		libusb_config_descriptor *conf_desc;
		libusb_get_config_descriptor(dev, 0, &conf_desc);
		int n_interfaces = conf_desc->bNumInterfaces;
		
		std::ostringstream ss;
		ss << "id: " << (std::hex) << desc.idVendor
		   << manufacturer_str
		   << ":" << (std::hex) << desc.idProduct
		   << " interfaces: " << n_interfaces
		   << " Class:" << (std::hex) << (unsigned int) desc.bDeviceClass << " " << device_class_to_string(desc.bDeviceClass);

		libusb_free_config_descriptor(conf_desc);

		if (handle)
			libusb_close(handle);

		devices.push_back(ss.str());
	}

	libusb_free_device_list(devs, 1);
			
	libusb_exit(NULL);

	return devices;
}

void MyLibrary::print_usb_version()
{
	libusb_context *ctx;
	
	int ret;

	ret = libusb_init(&ctx);	

	std::cout << "ret:" << ret << std::endl;
	
	const struct libusb_version *version = libusb_get_version();

	std::cout << version->major << "."
		  << version->minor << "."
		  << version->micro
		  << std::endl;	
	
	libusb_exit(ctx);
}
