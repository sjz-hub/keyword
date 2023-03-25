//
// Created by 孙建钊 on 2022/12/10.
//

#ifndef ACAUTO_LINKMATRIX_H
#define ACAUTO_LINKMATRIX_H

#include "LinkList.h"

class LinkMatrix{
private:
    LinkList **root;
    int len;//行数  关键词的个数
    Hash *hash;
    pair<int,int> *wordEdgeNum;//边的个数  <个数，对应value的key>
    int *fa;//表示集合，fa[i]表示索引为i的单词的父亲
    int *faNum;//集合的大小
public:
    LinkList** getRoot(){return root;}
    LinkMatrix(string keyword,string content,int distance);//构造函数，传入一个文件表示关键词文件
    void insertEdge(string &u,string &v);//插入一条边
    void printMaxN(int n);//输出度数前n大
    void dealAllEdge(string keyword,string content,int distance);
    int getLen(){return len;}
    int queryIndexOfWord(string value);//查询这个单词对应的root中的索引
    void calFa();//计算父亲，进行并查集操作   closeness好像重复写了这一个功能，应该将其删除，使用这里的calFa
    int find(int x);//并查集的find
    int* getFaNum(){return faNum;}
    void calIndexAndDu();//计算所有节点的du和index
};

#endif //ACAUTO_LINKMATRIX_H
