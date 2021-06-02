#ifndef TicketSystem_CommandHandler
#define TicketSystem_CommandHandler

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include "main.h"
#include "Bpt_and_database.h"
#include "data.hpp"
#include "string.h"
#include "vector.h"

#include "user.hpp"
#include "train.hpp"
#include "time.hpp"

class CommandHandler {
private:
    std::string op ;
    char argument[30][10010] ;
    int key_cnt = 1 ;

public:
    CommandHandler (const std::string _op) {
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
            }
        } catch (...) {
            printf("-1\n") ;
        }
    }

    void add_user () {
        string cur_username, username, password, name, mailAddr ;
        int privilege ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'c') cur_username = string (argument[i + 1]) ;
            else if (argument[i][1] == 'u') username = string (argument[i + 1]) ;
            else if (argument[i][1] == 'p') password = string (argument[i + 1]) ;
            else if (argument[i][1] == 'n') name = string (argument[i + 1]) ;
            else if (argument[i][1] == 'm') mailAddr = string (argument[i + 1]) ;
            else if (argument[i][1] == 'g') privilege = string (argument[i + 1]).toInt() ;
        }

        if (users.empty()) {
            privilege = 10 ;
        } else {
            sjtu::vector<int> pos ;
            curUsers.find (data (cur_username, 0), pos) ;
            if (pos.empty()) throw "cur user not logged in" ;

            user cur_user = user_read (pos[0]) ;
            if (cur_user.getPrivilege() <= privilege) throw "invalid privilege" ;
        }

        sjtu::vector<int> pos ;
        users.find (data (username, 0), pos) ;
        if (!pos.empty()) throw "user already exists" ;
        user new_user = user (username, password, name, mailAddr, privilege) ;
        int write_pos = user_write (new_user) ;
        users.insert (data (username, write_pos)) ;
        printf ("0\n") ;
    }

    void login () {
        string username, password ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'u') username = string (argument[i + 1]) ;
            else if (argument[i][1] == 'p') password = string (argument[i + 1]) ;
        }

        sjtu::vector<int> pos ;
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
        string username ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'u') username = string (argument[i + 1]) ;
        }
        sjtu::vector<int> pos ;
        curUsers.find (data (username, 0), pos) ;
        if (pos.empty()) throw "cur user not logged in" ;
        int user_file_pos = pos[0] ;
        curUsers.erase (data (username, user_file_pos)) ;
        printf ("0\n") ;
    }

    void query_profile () {
        string cur_username, username ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'c') cur_username = string (argument[i + 1]) ;
            else if (argument[i][1] == 'u') username = string (argument[i + 1]) ;
        }

        sjtu::vector<int> pos ;
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
        string cur_username, username, password, name, mailAddr ;
        int privilege = -1 ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'c') cur_username = string (argument[i + 1]) ;
            else if (argument[i][1] == 'u') username = string (argument[i + 1]) ;
            else if (argument[i][1] == 'p') password = string (argument[i + 1]) ;
            else if (argument[i][1] == 'n') name = string (argument[i + 1]) ;
            else if (argument[i][1] == 'm') mailAddr = string (argument[i + 1]) ;
            else if (argument[i][1] == 'g') privilege = string (argument[i + 1]).toInt() ;
        }

        sjtu::vector<int> pos ;
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

    void split_string (string *res, char *str) {
        int cur_id = 1, cur_len = 0, len = strlen (str) ;
        for (int i = 0; i < len; i ++) {
            if (str[i] == '|') {
                res[cur_id][cur_len ++] = 0 ;
                cur_id ++, cur_len = 0 ;
            } else {
                res[cur_id][cur_len ++] = str[i] ;
            }
        }
        res[cur_id][cur_len ++] = 0 ;
    }

    void split_int (int *res, char *str) {
        int cur_id = 1, len = strlen (str) ;
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
        string trainID, stations[110] ;
        char type ;
        Time startTime, saleDate[3] ;

        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'i') trainID = string (argument[i + 1]) ;
            else if (argument[i][1] == 'n') stationNum = string (argument[i + 1]).toInt() ;
            else if (argument[i][1] == 'm') seatNum = string (argument[i + 1]).toInt() ;
            else if (argument[i][1] == 's') split_string (stations, argument[i + 1]) ;
            else if (argument[i][1] == 'p') split_int (prices, argument[i + 1]) ;
            else if (argument[i][1] == 'x') startTime = Time (string ("00-00"), argument[i + 1]) ;
            else if (argument[i][1] == 't') split_int (travelTimes, argument[i + 1]) ;
            else if (argument[i][1] == 'o') split_int (stopoverTimes, argument[i + 1]) ;
            else if (argument[i][1] == 'd') {
                string tmp = string (argument[i + 1]) ;
                saleDate[1] = Time (tmp.substr (0, 4), string ("00-00")); saleDate[2] = Time (tmp.substr (6, 10), string ("00-00")) ;
            }
            else if (argument[i][1] == 'y') type = argument[i + 1][0] ;
        }

        sjtu::vector<int> pos ;
        trains.find (data (trainID, 0), pos) ;
        if (!pos.empty()) throw "train already exists" ;
        
        train new_train = train (trainID, stationNum, stations, seatNum, prices, startTime, travelTimes, stopoverTimes, saleDate, type) ;
        int train_file_pos = train_write (new_train) ;
        trains.insert (data (trainID, train_file_pos)) ;

        printf("0\n") ;
    }

    void release_train () {
        string trainID ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'i') trainID = string (argument[i + 1]) ;
        }

        sjtu::vector<int> pos ;
        trains.find (data (trainID, 0), pos) ;
        if (pos.empty()) throw "train not found" ;
        int train_file_pos = pos[0] ;
        train cur_train = train_read (train_file_pos) ;
        cur_train.release() ;
        train_write (train_file_pos, cur_train) ;

        printf("0\n") ;
    }

    void query_train () {
        string trainID ;
        Time date ;
        for (int i = 2; i <= key_cnt; i += 2) {
            if (argument[i][1] == 'i') trainID = string (argument[i + 1]) ;
            else if (argument[i][1] == 'd') date = Time (argument[i + 1], string ("00:00")) ;
        }

        sjtu::vector<int> pos ;
        trains.find (data (trainID, 0), pos) ;
        if (pos.empty()) throw "train not found" ;
        int train_file_pos = pos[0] ;
        train cur_train = train_read (train_file_pos) ;
        if (!cur_train.runningOnDate (date)) throw "train doesn't run on this date" ;
        cur_train.print (date) ;
    }
} ;

#endif