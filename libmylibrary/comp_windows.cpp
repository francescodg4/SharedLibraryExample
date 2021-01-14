#include "mylibrary.h"
#include <Windows.h>
#include <synchapi.h>

void MyLibrary::wait_sleep(int seconds)
{
	Sleep(seconds * 1000);
}
