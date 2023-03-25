//
// Created by 孙建钊 on 2022/12/5.
//

#include <fstream>
#include <iostream>
#include "Hash.h"

Hash::Hash(string filepath,int M):filepath(filepath),M(M){
    hashList = new linkList[M]; //动态申请一个内存空间用来做数组链表
    string str;
    std::ifstream ins;
    ins.open(filepath);
    int k = 0;
    while(getline(ins,str)){;
        if(str.empty()) break;
        unsigned int key = getHashKey(str);
        key %= M; //将计算得到的Hash值对M进行求余
//        if(str=="介绍" || str == "通过") cout<<"insert"<<str<<" "<<key<<endl;
        if(hashList[key].getValue() != -1){
            linkList *temp = new linkList;
            temp->setValue(k);
            hashList[key].addLink(temp);
        }
        else{
            hashList[key].setValue(k);
        }
        k++;
    }
}



unsigned int Hash::getHashKey(std::string &value) {
    char *str = const_cast<char *>(value.c_str());
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    while (*str){
        hash = hash * a + (*str++);
        a *= b;
    }
    return (hash & 0x7FFFFFFF);
}

pair<int*,int> Hash::query(std::string &value) {
    unsigned int key = getHashKey(value);
    key %= M;
    linkList *temp = &hashList[key];
    linkList *num = temp;
    int arrLen = 0;
    while(true){
        arrLen++;
        if(num->getNext() == nullptr) break;
        num = num->getNext();
    }
    pair<int *,int > ans;
    ans.first = new int[arrLen];
    ans.second = arrLen;
    int k = 0;
    while(true){
        ans.first[k++] = temp->getValue();
        if(temp->getNext() == nullptr){
            break;
        }
        temp = temp->getNext();
    }
    return ans;
}