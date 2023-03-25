//
// Created by 孙建钊 on 2022/12/5.
//

#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <ctime>
#include "LinkList.h"
#include "acNode.h"

LinkList::LinkList(std::string &value,int weight):value(value),weight(weight) {
    next = nullptr;
}

bool LinkList::operator<(LinkList link) {
    return this->value<link.value;
}

bool LinkList::operator>(LinkList link) {
    return this->value>link.value;
}

void LinkList::insertNode(std::string &str,bool flag) {

    LinkList *now = this;
    if(flag) cout<<value<<" "<<"start:"<<str<<getLen()<<endl;
    if(now->next == nullptr){//表明当前后面没有内容
        if(flag) cout<<"a";
        LinkList *newNode = new LinkList(str);
        now->next = newNode;
        if(flag) cout<<getLen()<<endl;
        return ;
    }
    LinkList *pre = now;
    now = now->next;

    while(true){
        if(now == nullptr){//表明后面已经没有节点需要遍历了
            LinkList *newNode = new LinkList(str);
            pre->next = newNode;
            if(flag) cout<<"b";
            break;
        }
        else{
            if(flag) cout<<now->value<<" "<<str<<endl;
            if(now->value > str){
                LinkList *newNode = new LinkList(str);
                newNode->next = pre->next;
                pre->next = newNode;
                if(flag) cout<<"c";
                break;
            }
            else if(now->value == str){//有的话就不需要再添加
                if(flag) cout<<"d";
                now->weight++;
                break;
            }
            now = now->next;
            pre = pre->next;
        }
    }
    if(flag) cout<<getLen()<<endl;
}



bool LinkList::find(std::string &str) {
    LinkList *now = next;
    while(now != nullptr){
        if(now->value == str) return true;
        now = now->next;
    }
    return false;
}

int LinkList::getLen() {
    int ans = 0;
    LinkList* now = next;
    while(now!= nullptr) {
        ans++;
        now = now->next;
    }
    return ans;
}



