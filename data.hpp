#ifndef data_type
#define data_type

#include <cstdio>
#include <cstring>

#include "string.h"

struct data {
    String str; int pos ;
    data () {
        //memset(str.str , 0 , sizeof str);
        pos = -1 ;
    }
    data (const char *_str, int p) {
        //memset(str.str , 0 , sizeof str.str);
        str = String (_str) ;
        pos = p ;
    }
    data (const String& _str, int p) {
        str = _str; pos = p ;
    }
    // void print() const {
    //     std::cout << str << " " << pos << std::endl ;
    // }
    data& operator=(const data &ot){
        if (this == &ot)return *this;
        memset(str.str , 0 , sizeof str.str);
        strcpy(str.str , ot.str.str);
        str.len = ot.str.len;
        pos = ot.pos;
        return *this;
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