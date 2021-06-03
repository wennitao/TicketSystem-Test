rm *.dat
sleep 0.5s
# cmake . && make

g++ -c Bpt_and_database.cpp -std=c++11
g++ -c string.cpp -std=c++11
g++ -c main.cpp -std=c++11
g++ -o code main.o string.o Bpt_and_database.o -std=c++11 -fsanitize=undefined -fsanitize=address