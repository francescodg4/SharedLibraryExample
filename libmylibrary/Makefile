CPPFLAGS+=-fPIC

all: libmylibrary.so

libmylibrary.so: mylibrary.o
	$(CC) -shared -o $@ $<

.PHONY: clean

clean:
	rm -rf *.o
