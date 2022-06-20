#include <fstream>

// #include "B+Tree.hpp"
// #include "Bpt_and_database.h"
#include "BPlusTree.h"
#include "data.hpp"

extern bool isExit ;

extern Tools::BPlusTree<data, int> users ;
extern Tools::BPlusTree<data, int> curUsers ;
extern Tools::BPlusTree<data, int> trains ;
extern Tools::BPlusTree<data, int> trainStations ;
extern Tools::BPlusTree<data, int> orders ;
extern Tools::BPlusTree<data, int> pendingOrders ;

extern std::fstream userio ;
extern std::fstream trainio ;
extern std::fstream orderio ;
extern std::fstream seatio ;
extern std::fstream logio ;