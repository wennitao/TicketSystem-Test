rm *.dat
sleep 0.5s
# cmake . && make

g++ -c Bpt_and_database.cpp
g++ -c string.cpp
g++ -c main.cpp
g++ -o code main.o string.o Bpt_and_database.o -std=c++11 -fsanitize=undefined -fsanitize=address