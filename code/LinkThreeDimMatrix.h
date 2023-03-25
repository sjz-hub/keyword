//
// Created by 孙建钊 on 2022/12/10.
//

#ifndef ACAUTO_LINKTHREEDIMMATRIX_H
#define ACAUTO_LINKTHREEDIMMATRIX_H

#include "LinkList.h"

// 需要给定适当的M
class LinkThreeDimMatrix {
private:
    // root[i][j]表示的当前value，不存储别的单词，
    LinkList ***root;//root[i]表示的是索引为i的单词的所有边   root[i][j]表示的是索引为i的单词的边的hash表示
    int N;//表示单词的个数
    int M;//表示每个单词的边的列表的映射数组长度
    Hash *hash; // 对单词进行hash表示
    int *fa;
    int *faNum;
    pair<int,string> *du;
public:
    LinkThreeDimMatrix(string keyword,string content,string duFile,int M);//duFile表示存放du的文件
    void dealAllEdge(string keyword,string content);
    void insertEdge(string &u,string &v);
    int queryIndexOfWord(string value);//查询这个单词对应的root中的索引
    void calIndexAndDu();
    int getN(){return N;}
    int getM(){return M;}
    LinkList*** getRoot(){return root;}
    int *getFaNum(){return faNum;}
    int *getFa(){return fa;}
    void calFa();
    int find(int x);
    pair<int,string>* printMaxDu(int K);
    void SaveDuAndSort(string duFile);//保存du文件
};


#endif //ACAUTO_LINKTHREEDIMMATRIX_H
