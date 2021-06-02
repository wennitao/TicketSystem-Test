#ifndef TrainSystem_order
#define TrainSystem_order

#include <iostream>

#include "string.h"

enum Status {success, pending, refunded} ;
const char status_str[3][20] = {"[success]", "[pending]", "[refunded]"} ;

class order {

    friend std::ostream& operator << (std::ostream &out, const order &_order) ;

private:
    String trainID, fromStation, toStation ;
    Time leavingTime, arrivingTime ;
    int price, seat, travellingTime ;
    Status status ;

public:
    order () {}
    order (const String &_trainID, const String &_fromStation, const String &_toStation, const Time &_leavingTime, const Time &_arrivingTime, const int _price, const int _seat, const int _travellingTime) {
        trainID = _trainID ;
        fromStation = _fromStation; toStation = _toStation ;
        leavingTime = _leavingTime; arrivingTime = _arrivingTime ;
        price = _price; seat = _seat; travellingTime = _travellingTime ;
    }

    void print () {
        std::cout << trainID << " " << fromStation << " " << leavingTime << " -> " << arrivingTime << " " << price << " " << seat << std::endl ;
    }

    String getTrainID () const {
        return trainID ;
    }

    Status getStatus () const {
        return status ;
    }

    Time getLeavingTime () const {
        return leavingTime ;
    }

    String getFromStation () const {
        return fromStation ;
    }

    String getToStation () const {
        return toStation ;
    }

    int getTravellingTime () const {
        return travellingTime ;
    }

    int getPrice () const {
        return price ;
    }

    int getSeatNum () const {
        return seat ;
    }

    void setStatus (Status _status) {
        status = _status ;
    }
} ;

std::ostream& operator << (std::ostream &out, const order &_order) {
    out << status_str[_order.status] << " " << _order.trainID << " " << _order.fromStation << " " << _order.leavingTime << " -> " << _order.arrivingTime << " " << _order.price << " " << _order.seat ;
    return out ;
}

#endif