#ifndef TicketSystem_Time
#define TicketSystem_Time

#include <iostream>
#include <iomanip>

#include "string.h"

int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} ;

class Time {

    friend std::ostream& operator << (std::ostream &out, const Time &_time) ;

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

    void setTime (const Time &_t) {
        h = _t.h; min = _t.min ;
    }

    bool operator < (const Time &_time) const {
        if (m == _time.m && d == _time.d && h == _time.h) return min < _time.h ;
        if (m == _time.m && d == _time.d) return h < _time.h ;
        if (m == _time.m) return d < _time.d ;
        return m < _time.m ;
    }

    bool operator <= (const Time &_time) const {
        if (m == _time.m && d == _time.d && h == _time.h) return min <= _time.h ;
        if (m == _time.m && d == _time.d) return h <= _time.h ;
        if (m == _time.m) return d <= _time.d ;
        return m <= _time.m ;
    }

    Time operator + (const int _min) {
        Time res = *this ;
        res.min += _min ;
        res.h += res.min / 60; res.min %= 60 ;
        res.d += res.h / 24; res.h %= 24 ;
        if (res.d > days[res.m]) res.d -= days[res.m], res.m ++ ;
        return res ;
    }

    int daysBetweenTime (const Time &_time) const {
        int res = d - _time.d ;
        for (int i = _time.m; i < m; i ++) res += days[i] ;
        return res ;
    }
} ;

std::ostream& operator << (std::ostream &out, const Time &_time) {
    out << std::setw (2) << std::setfill ('0') << _time.m << '-' << std::setw (2) << std::setfill ('0') << _time.d << ' ' << std::setw (2) << std::setfill ('0') << _time.h << ':' << std::setw (2) << std::setfill ('0') << _time.min ;
    return out ;
}

#endif