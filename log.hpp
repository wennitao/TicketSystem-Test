#ifndef TicketSystem_log
#define TicketSystem_log

#include <iostream>

class log {
public:
    char str[10010] ;
    int timeStamp, preFilePos ;

    log () {}
    log (const char* _str, int _timeStamp, int _preFilePos) {
        strcpy (str, _str) ;
        timeStamp = _timeStamp ;
        preFilePos = _preFilePos ;
    }

    void print () {
        // printf("filePos: %d timeStamp: %d %s\n", preFilePos, timeStamp, str) ;
        printf("%s\n", str) ;
    }
} ;

#endif