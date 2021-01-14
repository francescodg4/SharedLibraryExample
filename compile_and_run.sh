export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH

cp libmylibrary/libmylibrary.so .
g++ -Wall -o myapp app.cpp -Ilibmylibrary/ -L. -lmylibrary

./myapp
