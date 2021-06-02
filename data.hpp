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
    data (const String _str, int p) {
        str = _str; pos = p ;
    }
    // void print() const {
    //     std::cout << str << " " << pos << std::endl ;
    // }
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