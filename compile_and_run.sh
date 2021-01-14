export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH

pushd libmylibrary
make -B
popd

cp libmylibrary/libmylibrary.so .
g++ -g -Wall -o myapp app.cpp -Ilibmylibrary/ -L. -lmylibrary -lusb-1.0

./myapp
