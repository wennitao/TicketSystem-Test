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

    HashMap stationHashMap ;

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
            for (int j = 0; j <= stationNum; j ++)
                seat[i][j] = seatNum ;

        priceSum[0] = 0 ;
        for (int i = 1; i < stationNum; i ++)
            priceSum[i] = priceSum[i - 1] + _prices[i] ;

        travelTimesSum[0] = 0 ;
        for (int i = 1; i < stationNum; i ++)
            travelTimesSum[i] = travelTimesSum[i - 1] + _travelTimes[i] ;
        
        stopoverTimesSum[0] = stopoverTimesSum[1] = 0 ;
        for (int i = 2; i < stationNum; i ++)
            stopoverTimesSum[i] = stopoverTimesSum[i - 1] + _stopoverTimes[i - 1] ;
        stopoverTimesSum[stationNum] = stopoverTimesSum[stationNum - 1] ;

        for (int i = 1; i <= stationNum; i ++) {
            stationHashMap.insert (stations[i], i) ;
        }
        stationHashMap.sort() ;
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

    int getSeatNum () const {
        return seatNum ;
    }

    bool runningOnDate (const Time &date) const {
        return saleDate[1] <= date && date <= saleDate[2] ;
    }

    bool canDepartFromStationOnDate (const Time &date, const String &station) const {
        Time startTime = getStartTime (date, station) ;
        startTime.clearTime() ;
        return runningOnDate (startTime) ;
    }
    
    bool direction (const String &fromStation, const String &toStation) const {
        int from_id = stationHashMap.find (fromStation), to_id = stationHashMap.find (toStation) ;
        return from_id != -1 && to_id != -1 && from_id < to_id ;
    }

    Time getStartTime (const Time &date, const String &station) const {
        int stationID = stationHashMap.find (station) ;
        Time res = date ;
        res = res - travelTimesSum[stationID - 1] - stopoverTimesSum[stationID] ;
        Time tmp = res; tmp.setTime (startTime) ;
        if (tmp < res) tmp = tmp + 1440 ;
        return tmp ;
    }

    Time getStartTimeFromLeavingTime (const Time &time, const String &station) const {
        int stationID = stationHashMap.find (station) ;
        return time - travelTimesSum[stationID - 1] - stopoverTimesSum[stationID] ;
    }

    Time getLeavingTime (const Time &startTime, const String &station) const {
        int stationID = stationHashMap.find (station) ;
        return startTime + travelTimesSum[stationID - 1] + stopoverTimesSum[stationID] ;
    }

    Time getArrivingTime (const Time &startTime, const String &station) const {
        int stationID = stationHashMap.find (station) ;
        return startTime + travelTimesSum[stationID - 1] + stopoverTimesSum[stationID - 1] ;
    }

    int calTravellingTime (const String &fromStation, const String &toStation) const {
        int from_id = stationHashMap.find (fromStation), to_id = stationHashMap.find (toStation) ;
        return travelTimesSum[to_id - 1] + stopoverTimesSum[to_id - 1] - (travelTimesSum[from_id - 1] + stopoverTimesSum[from_id]) ;
    }

    int calPrice (const String &fromStation, const String &toStation) const {
        int from_id = stationHashMap.find (fromStation), to_id = stationHashMap.find (toStation) ;
        return priceSum[to_id - 1] - priceSum[from_id - 1] ;
    }

    int calSeats (const Time &startTime, const String &fromStation, const String &toStation) const {
        int days = startTime.daysBetweenTime (saleDate[1]) ;
        int from_id = stationHashMap.find (fromStation), to_id = stationHashMap.find (toStation) ;
        int seats = 1e9 ;
        for (int i = from_id; i < to_id; i ++)
            seats = std::min (seats, seat[days][i]) ;
        return seats ;
    }

    void sellSeats (const Time &startTime, const String &fromStation, const String &toStation, const int ticketNum) {
        int days = startTime.daysBetweenTime (saleDate[1]) ;
        int from_id = stationHashMap.find (fromStation), to_id = stationHashMap.find (toStation) ;
        for (int i = from_id; i < to_id; i ++)
            seat[days][i] -= ticketNum ;
    }

    void addSeats (const Time &startTime, const String &fromStation, const String &toStation, const int ticketNum) {
        int days = startTime.daysBetweenTime (saleDate[1]) ;
        int from_id = stationHashMap.find (fromStation), to_id = stationHashMap.find (toStation) ;
        for (int i = from_id; i < to_id; i ++)
            seat[days][i] += ticketNum ;
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