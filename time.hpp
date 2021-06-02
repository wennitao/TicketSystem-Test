#ifndef TicketSystem_Time
#define TicketSystem_Time

#include <iostream>

#include "string.h"

class Time {

private:
    int m, d, h, min ;

public:
    Time () {}
    Time (const string &date, const string &t) {
        m = (date[0] - '0') * 10 + date[1] - '0' ;
        d = (date[3] - '0') * 10 + date[4] - '0' ;
        h = (t[0] - '0') * 10 + t[1] - '0' ;
        min = (t[3] - '0') * 10 + t[4] - '0' ;
    }
} ;

#endif