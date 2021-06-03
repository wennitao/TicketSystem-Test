#ifndef TicketSystem_CommandHandler
#define TicketSystem_CommandHandler

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

#include "main.h"
// #include "Bpt_and_database.h"
#include "B+Tree.hpp"
#include "data.hpp"
#include "string.h"
#include "vector.h"

#include "user.hpp"
#include "train.hpp"
#include "time.hpp"
#include "order.hpp"

class CommandHandler {
private:
    std::string op ;
    char argument[30][10010] ;
    int key_cnt = 1 ;

public:
    CommandHandler (const std::string _op) {
        // std::cout << _op << std::endl ;
        op = _op ;
    }

    void analyze () {
        int cur_len = 0 ;
        for (int i = 0; i < op.length(); i ++) {
            if (op[i] == ' ') {
                argument[key_cnt][cur_len ++] = 0; key_cnt ++; cur_len = 0 ;
            } else {
                argument[key_cnt][cur_len ++] = op[i] ;
            }
        }
        argument[key_cnt][cur_len ++] = 0 ;
    }

    user user_read (int pos) {
        userio.seekg (pos, std::ios::beg) ;
        user cur ;
        userio.read (reinterpret_cast<char *>(&cur), sizeof (cur)) ;
        return cur ;
    }

    int user_write (user &cur) {
        userio.seekp (0, std::ios::end) ;
        int pos = userio.tellp() ;
        userio.write (reinterpret_cast<char *>(&cur), sizeof (cur)) ;
        return pos ;
    }

    void user_write (int pos, user &cur) {
        userio.seekp (pos, std::ios::beg) ;
        userio.write (reinterpret_cast<char *>(&cur), sizeof (cur)) ;
    }

    train train_read (int pos) {
        trainio.seekg (pos, std::ios::beg) ;
        train cur ;
        trainio.read (reinterpret_cast<char *>(&cur), sizeof (cur)) ;
        return cur ;
    }

    int train_write (train &cur) {
        trainio.seekp (0, std::ios::end) ;
        int pos = trainio.tellp() ;
        trainio.write (reinterpret_cast<char *>(&cur), sizeof (cur)) ;
        return pos ;
    }

    void train_write (int pos, train &cur) {
        trainio.seekp (pos, std::ios::beg) ;
        trainio.write (reinterpret_cast<char *>(&cur), sizeof (cur)) ;
    }

    order order_read (int pos) {
        orderio.seekg (pos, std::ios::beg) ;
        order cur ;
        orderio.read (reinterpret_cast<char *>(&cur), sizeof (cur)) ;
        return cur ;
    }

    int order_write (order &cur) {
        orderio.seekp (0, std::ios::end) ;
        int pos = orderio.tellp() ;
        orderio.write (reinterpret_cast<char *>(&cur), sizeof (cur)) ;
        return pos ;
    }

    void order_write (int pos, order &cur) {
        orderio.seekp (pos, std::ios::beg) ;
        orderio.write (reinterpret_cast<char *>(&cur), sizeof (cur)) ;
    }

    void run () {
        try {
            analyze () ;
            if (strcmp (argument[1], "add_user") == 0) {
                add_user () ;
            } else if (strcmp (argument[1], "login") == 0) {
                login () ;
            } else if (strcmp (argument[1], "logout") == 0) {
                logout () ;
            } else if (strcmp (argument[1], "query_profile") == 0) {
                query_profile () ;
            } else if (strcmp (argument[1], "modify_profile") == 0) {
                modify_profile () ;
            } else if (strcmp (argument[1], "add_train") == 0) {
                add_train () ;
            } else if (strcmp (argument[1], "release_train") == 0) {
                release_train() ;
            } else if (strcmp (argument[1], "query_train") == 0) {
                query_train () ;
            } else if (strcmp (argument[1], "delete_train") == 0) {
                delete_train () ;
            } else if (strcmp (argument[1], "query_ticket") == 0) {
                query_ticket () ;
            } else if (strcmp (argument[1], "query_transfer") == 0) {
                query_transfer () ;
            } else if (strcmp (argument[1], "buy_ticket") == 0) {
                buy_ticket () ;
            } else if (strcmp (argument[1], "query_order") == 0) {
                query_order () ;
            } else if (strcmp (argument[1], "refund_ticket") == 0) {
                refund_ticket () ;
            } else if (strcmp (argument[1], "clean") == 0) {
                clean() ;
            }
        } catch (...) {
            printf("-1\n") ;
        }
    }

    void add_user () {
        String cur_username, username, password, name, mailAddr ;
        int privilege ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'c') cur_username = argument[i + 1] ;
            else if (argument[i][1] == 'u') username = argument[i + 1] ;
            else if (argument[i][1] == 'p') password = argument[i + 1] ;
            else if (argument[i][1] == 'n') name = argument[i + 1] ;
            else if (argument[i][1] == 'm') mailAddr = argument[i + 1] ;
            else if (argument[i][1] == 'g') privilege = String (argument[i + 1]).toInt() ;
        }

        if (users.empty()) {
            privilege = 10 ;
        } else {
            std::vector<int> pos ;
            curUsers.find (data (cur_username, 0), pos) ;
            if (pos.empty()) throw "cur user not logged in" ;

            user cur_user = user_read (pos[0]) ;
            if (cur_user.getPrivilege() <= privilege) throw "invalid privilege" ;
        }

        std::vector<int> pos ;
        users.find (data (username, 0), pos) ;
        if (!pos.empty()) throw "user already exists" ;
        user new_user = user (username, password, name, mailAddr, privilege) ;
        int write_pos = user_write (new_user) ;
        users.insert (data (username, write_pos)) ;
        printf ("0\n") ;
    }

    void login () {
        String username, password ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'u') username = argument[i + 1] ;
            else if (argument[i][1] == 'p') password = argument[i + 1] ;
        }

        std::vector<int> pos ;
        curUsers.find (data (username, 0), pos) ;
        if (!pos.empty()) throw "already logged in" ;
        users.find (data (username, 0), pos) ;
        if (pos.empty()) throw "username not exists" ;

        int user_file_pos = pos[0] ;
        user cur_user = user_read (user_file_pos) ;
        cur_user.login (password) ;
        curUsers.insert (data (username, user_file_pos)) ;
        printf ("0\n") ;
    }

    void logout () {
        String username ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'u') username = argument[i + 1] ;
        }
        std::vector<int> pos ;
        curUsers.find (data (username, 0), pos) ;
        if (pos.empty()) throw "cur user not logged in" ;
        int user_file_pos = pos[0] ;
        curUsers.erase (data (username, user_file_pos)) ;
        printf ("0\n") ;
    }

    void query_profile () {
        String cur_username, username ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'c') cur_username = argument[i + 1] ;
            else if (argument[i][1] == 'u') username = argument[i + 1] ;
        }

        std::vector<int> pos ;
        curUsers.find (data (cur_username, 0), pos) ;
        if (pos.empty()) throw "cur user not logged in" ;
        int cur_user_file_pos = pos[0] ;
        user cur_user = user_read (cur_user_file_pos) ;

        pos.clear() ;
        users.find (data (username, 0), pos) ;
        if (pos.empty()) throw "user not found" ;
        int query_user_file_pos = pos[0] ;
        user query_user = user_read (query_user_file_pos) ;
        if (!(cur_user.getPrivilege() > query_user.getPrivilege() || cur_username == username)) throw "invalid privilege" ;
        
        std::cout << query_user << std::endl ;
    }

    void modify_profile () {
        String cur_username, username, password, name, mailAddr ;
        int privilege = -1 ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'c') cur_username = argument[i + 1] ;
            else if (argument[i][1] == 'u') username = argument[i + 1] ;
            else if (argument[i][1] == 'p') password = argument[i + 1] ;
            else if (argument[i][1] == 'n') name = argument[i + 1] ;
            else if (argument[i][1] == 'm') mailAddr = argument[i + 1] ;
            else if (argument[i][1] == 'g') privilege = String (argument[i + 1]).toInt() ;
        }

        std::vector<int> pos ;
        curUsers.find (data (cur_username, 0), pos) ;
        if (pos.empty()) throw "user enot logged in" ;
        int cur_user_file_pos = pos[0] ;
        user cur_user = user_read (cur_user_file_pos) ;
        
        pos.clear() ;
        users.find (data (username, 0), pos) ;
        if (pos.empty()) throw "user not found" ;
        int modify_user_file_pos = pos[0] ;
        user modify_user = user_read (modify_user_file_pos) ;

        if (!(cur_user.getPrivilege() > modify_user.getPrivilege() || cur_username == username)) throw "invalid privilege" ;
        if (privilege != -1 && privilege >= cur_user.getPrivilege()) throw "invalid privilege" ;

        if (!password.empty()) modify_user.modifyPassword (password) ;
        if (!name.empty()) modify_user.modifyName (name) ;
        if (!mailAddr.empty()) modify_user.modifyMailAddress (mailAddr) ;
        if (privilege != -1) modify_user.modifyPrivilege (privilege) ;
        user_write (modify_user_file_pos, modify_user) ;

        std::cout << modify_user << std::endl ;
    }

    void split_String (String *res, char *str) {
        int cur_id = 1, cur_len = 0, len = strlen (str) ;
        String tmp ;
        for (int i = 0; i < len; i ++) {
            if (str[i] == '|') {
                res[cur_id] = tmp ;
                tmp.clear() ;
                cur_id ++, cur_len = 0 ;
            } else {
                tmp += str[i] ;
            }
        }
        res[cur_id] = tmp ;
    }

    void split_int (int *res, char *str) {
        int cur_id = 1, len = strlen (str) ;
        res[cur_id] = 0 ;
        for (int i = 0; i < len; i ++) {
            if (str[i] == '|') {
                cur_id ++; res[cur_id] = 0 ;
            } else {
                res[cur_id] = res[cur_id] * 10 + str[i] - '0' ;
            }
        }
    }

    void add_train() {
        int stationNum, seatNum, prices[110], travelTimes[110], stopoverTimes[110] ;
        String trainID, stations[110] ;
        char type ;
        Time startTime, saleDate[3] ;

        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'i') trainID = argument[i + 1] ;
            else if (argument[i][1] == 'n') stationNum = String (argument[i + 1]).toInt() ;
            else if (argument[i][1] == 'm') seatNum = String (argument[i + 1]).toInt() ;
            else if (argument[i][1] == 's') split_String (stations, argument[i + 1]) ;
            else if (argument[i][1] == 'p') split_int (prices, argument[i + 1]) ;
            else if (argument[i][1] == 'x') startTime = Time (0, argument[i + 1]) ;
            else if (argument[i][1] == 't') split_int (travelTimes, argument[i + 1]) ;
            else if (argument[i][1] == 'o') split_int (stopoverTimes, argument[i + 1]) ;
            else if (argument[i][1] == 'd') {
                String tmp = argument[i + 1] ;
                saleDate[1] = Time (tmp.substr (0, 4), 0); saleDate[2] = Time (tmp.substr (6, 10), 0) ;
            }
            else if (argument[i][1] == 'y') type = argument[i + 1][0] ;
        }

        std::vector<int> pos ;
        trains.find (data (trainID, 0), pos) ;
        if (!pos.empty()) throw "train already exists" ;
        
        train new_train = train (trainID, stationNum, stations, seatNum, prices, startTime, travelTimes, stopoverTimes, saleDate, type) ;
        int train_file_pos = train_write (new_train) ;
        trains.insert (data (trainID, train_file_pos)) ;

        for (int i = 1; i <= stationNum; i ++) {
            trainStations.insert (data (stations[i], train_file_pos)) ;
        }

        printf("0\n") ;
    }

    void release_train () {
        String trainID ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'i') trainID = argument[i + 1] ;
        }

        std::vector<int> pos ;
        trains.find (data (trainID, 0), pos) ;
        if (pos.empty()) throw "train not found" ;
        int train_file_pos = pos[0] ;
        train cur_train = train_read (train_file_pos) ;
        cur_train.release() ;
        train_write (train_file_pos, cur_train) ;

        printf("0\n") ;
    }

    void query_train () {
        String trainID ;
        Time date ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'i') trainID = argument[i + 1] ;
            else if (argument[i][1] == 'd') date = Time (argument[i + 1], 0) ;
        }

        std::vector<int> pos ;
        trains.find (data (trainID, 0), pos) ;
        if (pos.empty()) throw "train not found" ;
        int train_file_pos = pos[0] ;
        train cur_train = train_read (train_file_pos) ;
        if (!cur_train.runningOnDate (date)) throw "train doesn't run on this date" ;
        cur_train.print (date) ;
    }

    void delete_train () {
        String trainID ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'i') trainID = argument[i + 1] ;
        }

        std::vector<int> pos ;
        trains.find (data (trainID, 0), pos) ;
        if (pos.empty()) throw "train not found" ;
        int train_file_pos = pos[0] ;
        train cur_train = train_read (train_file_pos) ;
        if (cur_train.isReleased()) throw "already released" ;

        trains.erase (data (trainID, train_file_pos)) ;
        printf("0\n") ; 
    }

    static bool cmp_time (const order &a, const order &b) {
        if (a.getTravellingTime() == b.getTravellingTime()) return a.getTrainID() < b.getTrainID() ;
        return a.getTravellingTime() < b.getTravellingTime() ;
    }

    static bool cmp_cost (const order &a, const order &b) {
        if (a.getPrice() == b.getPrice()) return a.getTrainID() < b.getTrainID() ;
        return a.getPrice() < b.getPrice() ;
    }

    void query_ticket () {
        String fromStation, toStation ;
        Time date ;
        int priority = 0 ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 's') fromStation = argument[i + 1] ;
            else if (argument[i][1] == 't') toStation = argument[i + 1] ;
            else if (argument[i][1] == 'd') date = Time (argument[i + 1], 0) ;
            else if (argument[i][1] == 'p') priority = strcmp (argument[i + 1], "time") == 0 ? 0 : 1 ;
        }

        std::vector<int> train1, train2 ;
        std::vector<int> pos ;
        trainStations.find (data (fromStation, 0), train1) ;
        trainStations.find (data (toStation, 0), train2) ;

        std::sort (train1.begin(), train1.end()) ;
        std::sort (train2.begin(), train2.end()) ;
        std::vector<int> possible_trains ;
        int train1_id = 0, train2_id = 0 ;
        while (train1_id < train1.size() && train2_id < train2.size()) {
            if (train1[train1_id] < train2[train2_id]) train1_id ++ ;
            else if (train1[train1_id] > train2[train2_id]) train2_id ++ ;
            else {
                possible_trains.push_back (train1[train1_id]) ;
                train1_id ++; train2_id ++ ;
            }
        }

        if (possible_trains.empty()) {
            printf("0\n"); return ;
        }

        std::vector<order> orders ;
        int order_cnt = 0 ;
        for (int i = 0; i < possible_trains.size(); i ++) {
            train cur_train = train_read (possible_trains[i]) ;
            if (!cur_train.isReleased()) continue ;
            if (!cur_train.direction (fromStation, toStation)) continue ;
            if (!cur_train.canDepartFromStationOnDate (date, fromStation)) continue ;
            Time trainStartTime = cur_train.getStartTime (date, fromStation) ;
            orders.push_back (order (cur_train.getTrainID(), fromStation, toStation, 
            cur_train.getLeavingTime (trainStartTime, fromStation), 
            cur_train.getArrivingTime (trainStartTime, toStation), 
            cur_train.calPrice (fromStation, toStation), 
            cur_train.calSeats (trainStartTime, fromStation, toStation), 
            cur_train.calTravellingTime (fromStation, toStation))) ;
        }

        if (priority == 0) sort (orders.begin(), orders.end(), cmp_time) ;
        else sort (orders.begin(), orders.end(), cmp_cost) ;

        std::cout << orders.size() << std::endl ;
        for (int i = 0; i < orders.size(); i ++)
            orders[i].print() ;
    }

    void query_transfer () {
        String fromStation, toStation ;
        Time date ;
        bool priority = 0 ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 's') fromStation = argument[i + 1] ;
            else if (argument[i][1] == 't') toStation = argument[i + 1] ;
            else if (argument[i][1] == 'd') date = Time (argument[i + 1], 0) ;
            else if (argument[i][1] == 'p') priority = strcmp (argument[i + 1], "time") == 0 ? 0 : 1 ;
        }

        std::vector<int> train1_pos, train2_pos ;
        trainStations.find (data (fromStation, 0), train1_pos) ;
        trainStations.find (data (toStation, 0), train2_pos) ;

        int cost = 1e9 ;
        order order_1, order_2 ;

        for (int i = 0; i < train1_pos.size(); i ++) {
            train train1 = train_read (train1_pos[i]) ;
            if (!train1.isReleased()) continue ;
            if (!train1.canDepartFromStationOnDate (date, fromStation)) continue ;
            Time train1_startTime = train1.getStartTime (date, fromStation) ;
            int train1_stationNum = train1.getStationNum() ;
            for (int stationID = train1.getStationID (fromStation) + 1; stationID <= train1_stationNum; stationID ++) {
                String midStation = train1.getStation (stationID) ;
                if (midStation == toStation) continue ;
                Time train1_leavingTime = train1.getLeavingTime (train1_startTime, fromStation) ;
                Time train1_arrivingTime = train1.getArrivingTime (train1_startTime, midStation) ;
                int train1_travellingTime = train1.calTravellingTime (fromStation, midStation) ;
                int train1_price = train1.calPrice (fromStation, midStation) ;
                int train1_seat = train1.calSeats (train1_startTime, fromStation, midStation) ;

                for (int j = 0; j < train2_pos.size(); j ++) {
                    if (train1_pos[i] == train2_pos[j]) continue ;
                    train train2 = train_read (train2_pos[j]) ;
                    if (!train2.isReleased()) continue ;
                    if (!train2.direction (midStation, toStation)) continue ;
                    if (!train2.canDepartFromStationAferTime (train1_arrivingTime, midStation)) continue ;

                    Time train2_startTime = train2.getStartTimeAfterTime (train1_arrivingTime, midStation) ;
                    Time train2_leavingTime = train2.getLeavingTime (train2_startTime, midStation) ;
                    Time train2_arrivingTime = train2.getArrivingTime (train2_startTime, toStation) ;
                    int train2_travellingTime = train2.calTravellingTime (midStation, toStation) ;
                    int train2_price = train2.calPrice (midStation, toStation) ;
                    int train2_seat = train2.calSeats (train2_startTime, midStation, toStation) ;

                    int travellingTime = train2_arrivingTime - train1_leavingTime ;
                    if (priority == 0 && (travellingTime < cost || (travellingTime == cost && train1_travellingTime < order_1.getTravellingTime()))) {
                        cost = travellingTime ;
                        order_1 = order (train1.getTrainID(), fromStation, midStation, train1_leavingTime, train1_arrivingTime, train1_price, train1_seat, train1_travellingTime) ;
                        order_2 = order (train2.getTrainID(), midStation, toStation, train2_leavingTime, train2_arrivingTime, train2_price, train2_seat, train2_travellingTime) ;
                    }
                    if (priority == 1 && (train1_price + train2_price < cost || (train1_price + train2_price == cost && train1_travellingTime < order_1.getTravellingTime()))) {
                        cost = train1_price + train2_price ;
                        order_1 = order (train1.getTrainID(), fromStation, midStation, train1_leavingTime, train1_arrivingTime, train1_price, train1_seat, train1_travellingTime) ;
                        order_2 = order (train2.getTrainID(), midStation, toStation, train2_leavingTime, train2_arrivingTime, train2_price, train2_seat, train2_travellingTime) ;
                    }
                }
            }
        }
        if (cost == 1e9) printf("0\n") ;
        else {
            order_1.print(); order_2.print() ;
        }
    }

    void buy_ticket () {
        String username, trainID, fromStation, toStation ;
        Time date ;
        int ticketNum ;
        bool queue = 0 ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'u') username = argument[i + 1] ;
            else if (argument[i][1] == 'i') trainID = argument[i + 1] ;
            else if (argument[i][1] == 'd') date = Time (argument[i + 1], 0) ;
            else if (argument[i][1] == 'n') ticketNum = String (argument[i + 1]).toInt() ;
            else if (argument[i][1] == 'f') fromStation = argument[i + 1] ;
            else if (argument[i][1] == 't') toStation = argument[i + 1] ;
            else if (argument[i][1] == 'q') queue = strcmp (argument[i + 1], "false") == 0 ? 0 : 1 ;
        }

        std::vector<int> pos ;
        curUsers.find (data (username, 0), pos) ;
        if (pos.empty()) throw "user not logged in" ;
        int user_file_pos = pos[0] ;
        user cur_user = user_read (user_file_pos) ;

        pos.clear() ;
        trains.find (data (trainID, 0), pos) ;
        if (pos.empty()) throw "train not found" ;
        int train_file_pos = pos[0] ;
        train cur_train = train_read (train_file_pos) ;

        if (!cur_train.isReleased()) throw "train not released" ;
        if (!cur_train.direction (fromStation, toStation)) throw "cannot depart" ;
        if (!cur_train.canDepartFromStationOnDate (date, fromStation)) throw "cannot depart" ;
        if (ticketNum > cur_train.getSeatNum()) throw "no enough tickets" ;

        Time trainStartTime = cur_train.getStartTime (date, fromStation) ;
        int remainingSeats = cur_train.calSeats (trainStartTime, fromStation, toStation) ;
        
        if (!queue && remainingSeats < ticketNum) throw "no enough tickets" ;

        order cur_order = order (trainID, fromStation, toStation, 
        cur_train.getLeavingTime (trainStartTime, fromStation), 
        cur_train.getArrivingTime (trainStartTime, toStation), 
        cur_train.calPrice (fromStation, toStation), ticketNum, 
        cur_train.calTravellingTime (fromStation, toStation)) ;

        if (remainingSeats >= ticketNum) {
            cur_order.setStatus (success) ;
            cur_train.sellSeats (trainStartTime, fromStation, toStation, ticketNum) ;
            int order_file_pos = order_write (cur_order) ;
            orders.insert (data (username, order_file_pos)) ;
            printf("%lld\n", 1ll * ticketNum * cur_train.calPrice (fromStation, toStation)) ;
        } else {
            cur_order.setStatus (pending) ;
            int order_file_pos = order_write (cur_order) ;
            orders.insert (data (username, order_file_pos)) ;
            pendingOrders.insert (data (trainID, order_file_pos)) ;
            printf("queue\n") ;
        }

        train_write (train_file_pos, cur_train) ;
    }

    void query_order () {
        String username ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'u') username = argument[i + 1] ;
        }

        std::vector<int> pos ;
        curUsers.find (data (username, 0), pos) ;
        if (pos.empty()) throw "user not logged in" ;

        pos.clear() ;
        orders.find (data (username, 0), pos) ;
        std::reverse (pos.begin(), pos.end()) ;
        std::cout << pos.size() << std::endl ;
        for (int i = 0; i < pos.size(); i ++) {
            order cur_order = order_read (pos[i]) ;
            std::cout << cur_order << std::endl ;
        }
    }

    void refund_ticket () {
        String username ;
        int num = 1 ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'u') username = argument[i + 1] ;
            else if (argument[i][1] == 'n') num = String (argument[i + 1]).toInt() ;
        }

        std::vector<int> pos ;
        curUsers.find (data (username, 0), pos) ;
        if (pos.empty()) throw "user not logged in" ;

        pos.clear() ;
        orders.find (data (username, 0), pos) ;
        if (pos.size() < num) throw "no nth order" ;
        std::reverse (pos.begin(), pos.end()) ;
        int order_file_pos = pos[num - 1] ;
        order cur_order = order_read (pos[num - 1]) ;
        if (cur_order.getStatus() == refunded) throw "cannot refund" ;

        String trainID = cur_order.getTrainID() ;
        if (cur_order.getStatus() == pending) {
            pendingOrders.erase (data (trainID, order_file_pos)) ;
        } else {
            std::vector<int> tmp ;
            trains.find (data (trainID, 0), tmp) ;
            int train_file_pos = tmp[0] ;
            train cur_train = train_read (train_file_pos) ;
            Time trainStartTime = cur_train.getStartTimeFromLeavingTime (cur_order.getLeavingTime(), cur_order.getFromStation()) ;
            cur_train.addSeats (trainStartTime, cur_order.getFromStation(), cur_order.getToStation(), cur_order.getSeatNum()) ;

            tmp.clear() ;
            pendingOrders.find (data (trainID, 0), tmp) ;
            for (int i = 0; i < tmp.size(); i ++) {
                order pending_order = order_read (tmp[i]) ;
                Time pending_startTime = cur_train.getStartTimeFromLeavingTime (pending_order.getLeavingTime(), pending_order.getFromStation()) ;
                if (pending_order.getSeatNum() <= cur_train.calSeats (pending_startTime, pending_order.getFromStation(), pending_order.getToStation())) {
                    cur_train.sellSeats (pending_startTime, pending_order.getFromStation(), pending_order.getToStation(), pending_order.getSeatNum()) ;
                    pending_order.setStatus (success) ;
                    order_write (tmp[i], pending_order) ;
                    pendingOrders.erase (data (trainID, tmp[i])) ;
                }
            }
            train_write (train_file_pos, cur_train) ;
        }
        cur_order.setStatus (refunded) ;
        order_write (order_file_pos, cur_order) ;

        printf("0\n") ;
    }

    void clean () {
        users.clear() ;
        curUsers.clear() ;
        trains.clear() ;
        trainStations.clear() ;
        orders.clear() ;
        pendingOrders.clear() ;

        printf("0\n") ;
    }
} ;

#endif