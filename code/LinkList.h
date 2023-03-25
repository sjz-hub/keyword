//
// Created by �ｨ�� on 2022/12/5.
//

#ifndef ACAUTO_LINKLIST_H
#define ACAUTO_LINKLIST_H

#include <string>
#include "Hash.h"
using namespace std;
//����ĵ�һ��Ԫ�ر�ʾ����u,�������е�Ԫ�ر�ʾ����v
class LinkList {
public:
    string value;
    LinkList *next;
    int index;//��ʾ��ǰ�ڵ�value������
    int du;//��ʾ��ǰ�ڵ�value�г�ȥ�ıߵĸ���
    int weight;//Ȩ��
public:
    void setIndex(int index){this->index = index;}
    void setDu(int du){this->du = du;}
    int getWeight(){return weight;}
    int getIndex(){return index;}
    int getDu(){return du;}
    LinkList(string &value,int weight = 1);//���캯��
    bool operator<(LinkList link);
    bool operator>(LinkList link);
    void insertNode(string &str,bool p = false);//����һ���ڵ㣬�����������
    bool find(string &str);//��ѯĳ�������Ƕ�����
    int getLen();//���ص�ǰ��len������ͷ�ڵ�
    string& getValue(){return value;}
    LinkList* getNext(){return next;}
};


#endif //ACAUTO_LINKLIST_H
