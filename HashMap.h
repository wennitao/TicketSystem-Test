//
// Created by 罗皓天 on 2021/6/2.
//

#ifndef CODE_HASHMAP_H
#define CODE_HASHMAP_H
#include <functional>
#include <iostream>
using namespace std;
template<class Key , class Data , class Hash = std::hash<Key>>//key是站名 ， data是车站内容，即顺序
class HashMap{
private:
    const int size = 105;
    const int mod = 291143;
    struct pair{
    public:
        int first;//站名
        int second;//序号
        pair(){
            first = 0;
            second = 0;
        }
        pair(int l , int r):first(l),second(r){};
    };
    pair order[104];
    Hash hash;
    int cur = 0;
    void sort(int l , int r){
        int left = l , right = r;
        int mid = order[(l + r) >> 1].first;
        do{
            while (order[left].first < mid) left++;
            while (order[right].first > mid) right--;
            if (left <= right){
                swap(order[left] , order[right]);
                left++;
                right--;
            }
        } while (left <= right);
        if (right > l)sort(l , right);
        if (left < r)sort(left , r);
    }
public:
    HashMap() = default;
    void insert(Key key1 , Data data1){
        pair nod(hash(key1) % mod , data1);
        order[++cur] = nod;
    }
    void sort(){
        sort(1 , cur);
    }
    int find(Key key1){
        int l = 0;
        int r = cur + 1;
        while (l + 1 < r){
            int mid = (l + r) >> 1;
            if (order[mid].first >= (hash(key1) % mod))r = mid;
            else l = mid;
        }
        if (r == cur + 1)return -1;
        else return order[r].second;
    }
};
#endif //CODE_HASHMAP_H