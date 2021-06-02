//
// Created by 罗皓天 on 2021/6/3.
//

#ifndef CODE_CACHE_H
#define CODE_CACHE_H
template <class Key , class Data>
class HashTable{
private:
    class List{
    private:
        struct Node{
            Node* next;
            Key key;
            Data data;
            Node() = delete;
            Node(Node *nxt , Key key1 , Data data1):next(nxt),key(key1),data(data1){};
        };
        Node* head;

    };
};
#endif //CODE_CACHE_H
