//
// Created by 孙建钊 on 2022/12/5.
//

#ifndef ACAUTO_HASH_H
#define ACAUTO_HASH_H

#include <string>


using namespace std;

class linkList{
private:
    linkList *next;
    int value; //-1表示该位置没有内容，因为表示的是索引，所以value一定大于等于0
public:
    linkList() {
        next = nullptr;
        value = -1;
    }
    void addLink(linkList *nextLink){
        linkList *temp = next;
        next = nextLink;
        nextLink->setNext(temp);
    }
    void setNext(linkList * temp){
        next = temp;
    }
    linkList * getNext(){
        return next;
    }
    void setValue(int str) {
        value = str;
    }
    int getValue(){
        return value;
    }
};


class Hash {
private:
    int M;//hash表的长度
    linkList *hashList;//链表的头节点
    string filepath;//字典树的文件地址
public:
    Hash(string filepath,int M);
    unsigned int getHashKey(string &value);
    pair<int*,int> query(string &value);//查询value的对应的key,<查询的数组，数组的长度>
};


#endif //ACAUTO_HASH_H
