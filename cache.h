//
// Created by 罗皓天 on 2021/6/3.
//

#ifndef CODE_CACHE_H
#define CODE_CACHE_H
template <class Key , class Data>//通过站名返回地址
class HashTable{
private:
    class List{
    private:
        struct Node{
            Node* next;
            Key key;
            Data data;
            Node() = delete;
            Node(Node *nxt ,const Key &key1 ,const Data &data1):next(nxt),key(key1),data(data1){};
        };
        Node* head;
        int Listsize;
    public:
        List():Listsize(0),head(nullptr){};
        ~List(){
            while (head != nullptr){
                Node* tmp = head;
                head = head->next;
                delete tmp;
            }
        }
        void insert(const Key &key1 , const Data &data1){
            head = new Node(head , key1 , data1);
            ++Listsize;
        }
        Node* find(const Key &key1){
            if (Listsize == 0)return nullptr;
            Node *q = head;
            while (q != nullptr){
                if (q->key == key1)return q;
                q = q->next;
            }
            return nullptr;
        }
        void erase(const Key &key1){
            if (Listsize == 0)return;
            if (head->key == key1){
                Node* tmp = head;
                head = head->next;
                delete tmp;
                --Listsize;
                return;
            }
            Node* p = nullptr;
            Node* q = head;
            while (q != nullptr){
                if (q->key == key1)break;
                p = q;
                q = q->next;
            }
            p->next = q->next;
            delete q;
            --Listsize;
        }
    };

};
#endif //CODE_CACHE_H
