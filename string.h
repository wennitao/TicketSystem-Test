#ifndef CODE_ST_RING_H
#define CODE_ST_RING_H

#include <iostream>
#include <cstring>
#include <assert.h>

class String {

    friend std::ostream& operator << (std::ostream &out, const String &str) ;

public:
    char str[35];
    int len = 0;//记录字母个数，有一个记一个
    unsigned long long hash_val = 0 ;
public:
    String(const char *ch) {
        strcpy (str, ch) ;
        len = strlen (ch); str[len] = '\0' ;
    }
    String(){
        memset(str , 0 , sizeof str);
        len = 0;
    }
    String(const String &ot) {
        strcpy (str, ot.str) ;
        len = ot.len; str[len] = '\0' ;
    }
    ~String() {}
    String& operator=(const String &ot){
        if (this == &ot){
            return *this;
        }
        len = ot.len;
        strcpy (str, ot.str);
        str[len] = '\0' ;
        return *this;
    }
    String& operator = (const char *_str) {
        strcpy (str, _str) ;
        len = strlen (_str) ;
        return *this ;
    }
    String& operator += (const char _c) {
        str[len ++] = _c; str[len] = 0 ;
        return *this ;
    }
    void clear() {
        len = 0; str[len] = '\0' ;
        // memset(str , 0 , sizeof str);
        // len = 0;
    }
    bool operator<(const String &ot) const {
        return strcmp(this->str , ot.str) < 0;
    }
    bool operator<=(const String &ot) const {
        return strcmp(this->str , ot.str) <= 0;
    }
    bool operator==(const String &ot) const {
        return strcmp(this->str , ot.str) == 0;
    }
    bool operator != (const String &ot) const {
        return strcmp (this -> str, ot.str) != 0 ;
    }
    bool operator>(const String &ot) const {
        return strcmp(this->str , ot.str) > 0;
    }
    bool operator>=(const String &ot) const {
        return strcmp(this->str , ot.str) >= 0;
    }

    char operator [] (const int id) const {
        return str[id] ;
    }

    char& operator [] (const int id) {
        return str[id] ;
    }

    bool empty () const {
        return len == 0 ;
    }

    int toInt () const {
        int res = 0 ;
        for (int i = 0; i < len; i ++) {
            res = res * 10 + str[i] - '0' ;
        }
        return res ;
    }

    String substr (int l, int r) const {
        String res ;
        for (int i = l; i <= r; i ++) res.str[i - l] = str[i] ;
        res.len = r - l + 1 ;
        return res ;
    }
    unsigned long long hashit() const {
        unsigned long long res = 0;
        for (int i = 0; i < len; ++i) {
            res = res * 13331 + str[i] ;//-64以避免大小写
        }
        return res;
    }
};

#endif //CODE_ST_RING_H