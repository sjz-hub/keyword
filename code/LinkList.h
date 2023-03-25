//
// Created by 孙建钊 on 2022/12/5.
//

#ifndef ACAUTO_LINKLIST_H
#define ACAUTO_LINKLIST_H

#include <string>
#include "Hash.h"
using namespace std;
//链表的第一个元素表示的是u,后面所有的元素表示的是v
class LinkList {
public:
    string value;
    LinkList *next;
    int index;//表示当前节点value的索引
    int du;//表示当前节点value中出去的边的个数
    int weight;//权重
public:
    void setIndex(int index){this->index = index;}
    void setDu(int du){this->du = du;}
    int getWeight(){return weight;}
    int getIndex(){return index;}
    int getDu(){return du;}
    LinkList(string &value,int weight = 1);//构造函数
    bool operator<(LinkList link);
    bool operator>(LinkList link);
    void insertNode(string &str,bool p = false);//插入一个节点，按照升序插入
    bool find(string &str);//查询某个单词是都存在
    int getLen();//返回当前的len不包括头节点
    string& getValue(){return value;}
    LinkList* getNext(){return next;}
};


#endif //ACAUTO_LINKLIST_H
