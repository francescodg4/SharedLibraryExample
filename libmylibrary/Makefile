CPPFLAGS+=-g -fPIC -I/usr/include/libusb-1.0

all: libmylibrary.so

libmylibrary.so: mylibrary.o comp_unix.o
	$(CC) -shared -o $@ $^

.PHONY: clean

clean:
	rm -rf *.o
