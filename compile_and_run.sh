export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH

cp libmylibrary/libmylibrary.so .
g++ -o myapp app.cpp -Ilibmylibrary/ -L. -lmylibrary

./myapp
