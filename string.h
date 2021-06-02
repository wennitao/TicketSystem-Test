#ifndef CODE_ST_RING_H
#define CODE_ST_RING_H

#include <iostream>
#include <cstring>

class String {

    friend std::ostream& operator << (std::ostream &out, const String &str) ;

public:
    char str[110];
    int len = 0;//记录字母个数，有一个记一个
public:
    String(const char *ch){
        memset (str, 0, sizeof str) ;
        int i = 0;
        while (ch[i] != '\0'){
            str[i] = ch[i];
            i++;
        }
        len = i ;
    }
    String(){
        memset(str , 0 , sizeof str);
        len = 0;
    }
    String(const String &ot){
        memset (str, 0, sizeof str) ;
        for (int i = 0; i < ot.len; ++i) {
            str[i] = ot.str[i];
        }
        len = ot.len; str[len] = '\0' ;
    }
    ~String(){
        len = 0;
        memset(str , 0 , sizeof str);
    }
    String& operator=(const String &ot){
        if (this == &ot){
            return *this;
        }
        memset (str, 0, sizeof str) ;
        len = ot.len;
        strcpy (str, ot.str);
        return *this;
    }
    String& operator += (const char _c) {
        str[len ++] = _c; str[len] = 0 ;
        return *this ;
    }
    void clear() {
        memset(str , 0 , sizeof str);
        len = 0;
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
        for (int i = 0; i < len; i ++)
            res = res * 10 + str[i] - '0' ;
        return res ;
    }

    String substr (int l, int r) const {
        String res ;
        for (int i = l; i <= r; i ++) res.str[i - l] = str[i] ;
        res.len = r - l + 1 ;
        return res ;
    }
    int hashit() const {
        int res = 0;
        for (int i = 0; i < len; ++i) {
            res = (1ll * res * 131 + str[i]) % 91815541;//-64以避免大小写
        }
        res = (res % 91815541 + 91815541) % 91815541 ;
        return res;
    }
};

#endif //CODE_ST_RING_H