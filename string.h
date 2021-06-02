#ifndef CODE_ST_RING_H
#define CODE_ST_RING_H

#include <iostream>
#include <cstring>

class string {

    friend std::ostream& operator << (std::ostream &out, const string &str) ;

private:
    char str[110];
    int len = 0;//记录字母个数，有一个记一个
public:
    string(const char *ch){
        memset (str, 0, sizeof str) ;
        int i = 0;
        while (ch[i] != '\0'){
            str[i] = ch[i];
            i++;
        }
        len = i ;
    }
    string(){
        memset(str , 0 , sizeof str);
        len = 0;
    }
    string(const string &ot){
        memset (str, 0, sizeof str) ;
        for (int i = 0; i < ot.len; ++i) {
            str[i] = ot.str[i];
        }
        len = ot.len; str[len] = 0 ;
    }
    string& operator=(const string &ot){
        if (this == &ot){
            return *this;
        }
        memset (str, 0, sizeof str) ;
        len = ot.len;
        strcpy (str, ot.str);
        return *this;
    }
    void clear() {
        memset(str , 0 , sizeof str);
        len = 0;
    }
    bool operator<(const string &ot) const {
        return strcmp(this->str , ot.str) < 0;
    }
    bool operator<=(const string &ot) const {
        return strcmp(this->str , ot.str) <= 0;
    }
    bool operator==(const string &ot) const {
        return strcmp(this->str , ot.str) == 0;
    }
    bool operator != (const string &ot) const {
        return strcmp (this -> str, ot.str) != 0 ;
    }
    bool operator>(const string &ot) const {
        return strcmp(this->str , ot.str) > 0;
    }
    bool operator>=(const string &ot) const {
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

    string substr (int l, int r) {
        string res ;
        for (int i = l; i <= r; i ++) res.str[i - l] = str[i] ;
        res.len = r - l + 1 ;
        return res ;
    }
};

#endif //CODE_ST_RING_H