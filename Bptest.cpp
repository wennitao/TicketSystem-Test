//
// Created by 罗皓天 on 2021/5/29.
////
#include <iostream>
#include "data.hpp"
#include "Bpt_and_database.h"
//#include "_BPlulusTree.h"
#include <string>
#include <cstring>
#include <vector>
#include <stdio.h>
#include "string.h"


using namespace std;
int s[10001000] ;
String ss[100000];
int num[5000000];
int main() {
    //for (int t = 0; ; t ++) {
    //printf("Test %d\n", t) ;
    //system ("rm *.dat") ;
//    freopen("out.txt", "w" , stdout);
    Database test ("test.txt") ;
    //int seed = time (0) ;
    int seed = 1611837369 ;
    srand (seed) ;
    memset (s, 0, sizeof s) ;
    int n = 3000;
    for (int i = 1; i <= n; i ++) {
        //ss[i] = i;
        int qq = rand() % 5001;
        num[qq] += i;
        s[i] = qq;
        for (int j = 1; j <= i; ++j) {
            test.insert (data (s[i], j));
        }
        //test.printroot();
    }
    //test.print();
//    for (int i = 1; i <= n; i ++) {
//        test.erase (data  (s[i], i)) ;
//        //test.print();
//        if (i == n) break ;
//        int j = rand() % (n - i) + i + 1;
//        int res = test.findKey (data (s[j], j)) ;
//        if (j != res) {
//            printf("seed:%d test:(%s %d) %d\n", seed, s[j], j, res) ;
//            puts ("QAQ") ;
//            return 0 ;
//        }
    for (int i = 1; i <= n; ++i) {
        vector<int> res;
        test.find(data(s[i] , i) , res);
        if (res.empty() || res.size() != num[s[i]])cout << i << endl;
        res.clear();
    }

//    char ch[60] = "A basing bape";
//    St_ring ff(ch);
//    char sh[60] = "bbbbbbb";
//    St_ring dd(sh);
//    cout << (ff > dd);
//    for (int i = 1; i <= 37; ++i) {
//        char num[3];
//        if (i <= 26)num[0] = i + 64;
//        else{
//            num[1] = i + 38;
//            num[0] = 'Z';
//        }
//        for (int j = 1; j <= i; ++j) {
//            test.insert(data(num , j));
//        }
//    }
    //test.print();
//    sjtu::vector<int> res;
//    res.push_back(100);
//    res.push_back(5);
//    res.push_back(20);
//    res.push_back(15);
//    res.sort();
//    for (int i = 0; i < 100000; ++i) {
//        res.push_back(rand());
//    }
//    res.sort();
//    res.clear();
//    for (int i = 0; i < 1000; ++i) {
//        res.push_back(rand());
//    }
//    res.sort();
//    char ch[3];
//    ch[1] = '\0';
//    ch[0] = 'Z';
//    test.find(data(ch , 1) , res);
//    res.reverse();
//    for (int i = 1; i <= 37; ++i) {
//        char ch[3];
//        if (i <= 26)ch[0] = i + 64;
//        else{
//            ch[1] = i + 38;
//            ch[0] = 'Z';
//        }
//        test.find(data(ch , 7) , res);
//        for (auto t : res){
//            cout << t << ' ';
//        }
//        res.clear();
//    }
//    res.clear();
//    test.print();
//    char num[3];
//    string dd;
//    num[1] = '\0';
//    num[0] = 'S';
//    test.erase(data(num , 19));
//    num[0] = 'A';
//    test.erase(data(num , 1));
//    num[0] = 'B';
//    test.erase(data(num , 2));
//    num[0] = 'C';
//    test.erase(data(num , 3));
//    num[0] = 'D';
//    test.erase(data(num , 4));
//    num[0] = 'E';
//    test.erase(data(num , 5));
//    for (int i = 1; i <= 26; ++i) {
//        num[0] = i + 64;
//        test.erase(data(num , i));
//    }
//    for (int i = 1; i <= 10 ; ++i) {
//        num[0] = 'Z';
//        num[1] = i + 64;
//        num[2] = '\0';
//        test.erase(data(num , i + 26));
//    }
//    for (int i = 37; i > 1 ; --i) {
//        num[2] = '\0';
//        num[1] = '\0';
//        if (i > 26){
//            num[0] = 'Z';
//            num[1] = i + 38;
//        } else num[0] = i + 64;
//        test.erase(data(num , i));
//        test.print();
//    }
    //test.print();
    //}
    //int seed = 1611818624 ;*/
    return 0 ;
}
