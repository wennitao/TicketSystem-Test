#include <iostream>
#include <fstream>
#include <cstring>

#include "main.h"
// #include "Bpt_and_database.h"
#include "Bpt_and_database.h"
#include "CommandHandler.hpp"

Database users ("users_B+Tree.dat") ;
Database curUsers ("curUsers.dat") ;
Database trains ("trains_B+Tree.dat") ;
Database trainStations ("trainStations.dat") ;
Database orders ("orders_B+Tree.dat") ;
Database pendingOrders ("pendingOrders.dat") ;

std::fstream userio, trainio, orderio, seatio ;

void init () {
    std::fstream in ("users.dat", std::ios::in | std::ios::binary) ;
    if (!in.is_open()) {
        std::fstream out ("users.dat", std::ios::out | std::ios::binary) ;
        out.close() ;
        userio.open ("users.dat", std::ios::in | std::ios::out | std::ios::binary) ;
        userio.seekp (0, std::ios::end) ;
    }
    in.close() ;
    if (!userio.is_open()) userio.open ("users.dat", std::ios::in | std::ios::out | std::ios::binary) ;

    in.open ("trains.dat", std::ios::in | std::ios::binary) ;
    if (!in.is_open()) {
        std::fstream out ("trains.dat", std::ios::out | std::ios::binary) ;
        out.close() ;
        trainio.open ("trains.dat", std::ios::in | std::ios::out | std::ios::binary) ;
        trainio.seekp (0, std::ios::end) ;
        int tmp = -1 ;
        trainio.write (reinterpret_cast<char *>(&tmp), sizeof (tmp)) ;
    }
    in.close() ;
    if (!trainio.is_open()) trainio.open ("trains.dat", std::ios::in | std::ios::out | std::ios::binary) ;

    in.open ("orders.dat", std::ios::in | std::ios::binary) ;
    if (!in.is_open()) {
        std::fstream out ("orders.dat", std::ios::out | std::ios::binary) ;
        out.close() ;
        orderio.open ("orders.dat", std::ios::in | std::ios::out | std::ios::binary) ;
        orderio.seekp (0, std::ios::end) ;
    }
    in.close() ;
    if (!orderio.is_open()) orderio.open ("orders.dat", std::ios::in | std::ios::out | std::ios::binary) ;

    in.open ("seats.dat", std::ios::in | std::ios::binary) ;
    if (!in.is_open()) {
        std::fstream out ("seats.dat", std::ios::out | std::ios::binary) ;
        out.close() ;
        seatio.open ("seats.dat", std::ios::in | std::ios::out | std::ios::binary) ;
        seatio.seekp (0, std::ios::end) ;
    }
    in.close() ;
    if (!seatio.is_open()) seatio.open ("seats.dat", std::ios::in | std::ios::out | std::ios::binary) ;
}

int main() {
    //freopen("1.in" , "r" , stdin);
    init () ;
    std::string op ;
    while (getline (std::cin, op)) {
        if (op == std::string ("exit")) {
            printf("bye\n"); break ;
        }
        CommandHandler cmd = CommandHandler (op) ;
        cmd.run () ;
    }

    userio.close() ;
    trainio.close() ;
    orderio.close() ;
    seatio.close() ;
    curUsers.clear() ;
    return 0 ;
}