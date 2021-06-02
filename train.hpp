#ifndef TicketSystem_Train
#define TicketSystem_Train

#include <iostream>
#include <fstream>
#include <map>

#include "string.h"
#include "time.hpp"

class train {

private:
    bool released ;
    int stationNum, seatNum, prices[110], travelTimes[110], stopoverTimes[110] ;
    char type ;
    string trainID, stations[110] ;
    Time startTime, saleDate[3] ;
    std::map<string, int> stationID ;

public:
    train () {}
    train (const string &_trainID, const int _stationNum, const string *_stations, const int _seatNum, const int *_prices, const Time &_startTime, const int *_travelTimes, const int *_stopoverTimes, const Time *_saleDate, const char type) {
        trainID = _trainID ;
        stationNum = _stationNum ;
        for (int i = 1; i <= stationNum; i ++) stations[i] = _stations[i] ;
        seatNum = _seatNum ;
        for (int i = 1; i < stationNum; i ++) prices[i] = _prices[i] ;
        startTime = _startTime ;
        for (int i = 1; i < stationNum; i ++) travelTimes[i] = _travelTimes[i] ;
        for (int i = 2; i < stationNum; i ++) stopoverTimes[i] = _stopoverTimes[i] ;
        stopoverTimes[0] = stopoverTimes[stationNum] = 0 ;
        saleDate[1] = _saleDate[1]; saleDate[2] = _saleDate[2] ;
        released = 0 ;

        for (int i = 1; i <= stationNum; i ++)
            stationID[stations[i]] = i ;
    }

    void release () {
        if (released) throw "already released" ;
        released = 1 ;
    }

} ;

#endif