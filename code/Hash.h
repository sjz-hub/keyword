//
// Created by �ｨ�� on 2022/12/5.
//

#ifndef ACAUTO_HASH_H
#define ACAUTO_HASH_H

#include <string>


using namespace std;

class linkList{
private:
    linkList *next;
    int value; //-1��ʾ��λ��û�����ݣ���Ϊ��ʾ��������������valueһ�����ڵ���0
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
    int M;//hash��ĳ���
    linkList *hashList;//�����ͷ�ڵ�
    string filepath;//�ֵ������ļ���ַ
public:
    Hash(string filepath,int M);
    unsigned int getHashKey(string &value);
    pair<int*,int> query(string &value);//��ѯvalue�Ķ�Ӧ��key,<��ѯ�����飬����ĳ���>
};


#endif //ACAUTO_HASH_H
