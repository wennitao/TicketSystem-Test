#ifndef data_type
#define data_type

#include <cstdio>
#include <cstring>

#include "string.h"

struct data {
    String str; int pos ;
    data () {
        pos = -1 ;
    }
    data (const char *_str, int p) {
        str = String (_str) ;
        pos = p ;
    }
    data (const String &_str, int p) {
        // std::cout << _str << std::endl ;
        str = _str; pos = p ;
    }

    data& operator = (const data &_data) {
        if (this == &_data) return *this ;
        str = _data.str; pos = _data.pos ;
        return *this ;
    }
    void print() const {
        std::cout << str << " " << pos << std::endl ;
    }
    bool operator < (const data &a) const {
        if (str == a.str) return pos < a.pos ;
        return str < a.str ;
    }
    bool operator <= (const data &a) const {
        if (str == a.str) return pos <= a.pos ;
        return str < a.str ;
    }
    bool operator == (const data &a) const {
        return str == a.str && pos == a.pos ;
    }
} ;

#endif