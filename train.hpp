#ifndef TicketSystem_Train
#define TicketSystem_Train

#include <iostream>
#include <fstream>
#include <map>

#include "string.h"
#include "time.hpp"
#include "HashMap.h"

class train {

private:
    bool released ;
    int stationNum, seatNum, seat[110][110] ;
    int priceSum[110], travelTimesSum[110], stopoverTimesSum[110] ;
    char type ;
    String trainID, stations[110] ;
    Time startTime, saleDate[3] ;

    // HashMap<String, int> stationHashMap ;

public:
    train () {}
    train (const String &_trainID, const int _stationNum, const String *_stations, const int _seatNum, const int *_prices, const Time &_startTime, const int *_travelTimes, const int *_stopoverTimes, const Time *_saleDate, const char _type) {
        trainID = _trainID ;
        stationNum = _stationNum ;
        for (int i = 1; i <= stationNum; i ++) stations[i] = _stations[i] ;
        seatNum = _seatNum ;
        startTime = _startTime ;
        saleDate[1] = _saleDate[1]; saleDate[2] = _saleDate[2] ;
        type = _type ;
        released = 0 ;

        int days = saleDate[2].daysBetweenTime (saleDate[1]) ;
        for (int i = 0; i <= days; i ++)
            for (int j = 1; j <= stationNum; j ++)
                seat[i][j] = seatNum ;

        priceSum[0] = 0 ;
        for (int i = 1; i < stationNum; i ++)
            priceSum[i] = priceSum[i - 1] + _prices[i] ;
        
        travelTimesSum[0] = 0 ;
        for (int i = 1; i < stationNum; i ++)
            travelTimesSum[i] = travelTimesSum[i - 1] + _travelTimes[i] ;
        
        stopoverTimesSum[0] = stopoverTimesSum[1] ;
        for (int i = 2; i < stationNum; i ++)
            stopoverTimesSum[i] = stopoverTimesSum[i - 1] + _stopoverTimes[i - 1] ;
        stopoverTimesSum[stationNum] = stopoverTimesSum[stationNum - 1] ;

        // for (int i = 1; i <= stationNum; i ++)
        //     stationHashMap.insert (stations[i], i) ;
    }

    String getTrainID () const {
        return trainID ;
    }

    void release () {
        if (released) throw "already released" ;
        released = 1 ;
    }

    bool isReleased () {
        return released ;
    }

    bool runningOnDate (const Time &date) const {
        return saleDate[1] <= date && date <= saleDate[2] ;
    }

    bool canDepartOnDate (const Time &date) const {
        return 0 ;
    }
    
    bool direction (const String &fromStation, const String &toStation) const {

    }

    Time getStartTime (const Time &date, const String &station) const {

    }

    Time getLeavingTime (const Time &time, const String &station) const {

    }

    Time getArrivingTime (const Time &time, const String &station) const {

    }

    int calTravellingTime (const String &fromStation, const String &toStation) const {
        
    }

    int calPrice (const String &fromStation, const String &toStation) const {

    }

    int calSeats (const String &fromStation, const String &toStation) const {

    }

    void print (const Time &date) const {
        int days = date.daysBetweenTime (saleDate[1]) ;
        Time tim = date ;
        tim.setTime (startTime) ;
        std::cout << trainID << " " << type << std::endl ;
        for (int i = 1; i <= stationNum; i ++) {
            if (i == 1) {
                std::cout << stations[i] << " xx-xx xx:xx -> " << tim << " " << priceSum[i - 1] << " " << seat[days][i] << std::endl ;
            } else if (i == stationNum) {
                std::cout << stations[i] << " " << tim + travelTimesSum[i - 1] + stopoverTimesSum[i] << " -> xx-xx xx:xx " << priceSum[i - 1] << " x" << std::endl ; 
            } else {
                std::cout << stations[i] << " " << tim + travelTimesSum[i - 1] + stopoverTimesSum[i - 1] << " -> " << tim + travelTimesSum[i - 1] + stopoverTimesSum[i] << " " << priceSum[i - 1] << " " << seat[days][i] << std::endl ;
            }
        }
    }

} ;

#endif