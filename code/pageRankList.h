//
// Created by 孙建钊 on 2022/12/9.
//

#ifndef ACAUTO_PAGERANKLIST_H
#define ACAUTO_PAGERANKLIST_H

#include "LinkList.h"
#include "Hash.h"
#include "LinkMatrix.h"
#include "LinkThreeDimMatrix.h"
class pageRankList {
private:
//    LinkMatrix *lm;//存储图
    LinkThreeDimMatrix *ltm;
    double *pr;//pr分数
    int N;//单词数 这个值从lm中获取
    double a;//表示随机走向别的节点的概率
    double c;//表示小于该值则认为迭代完毕
    int *du;//表示该节点的出度
public:
    pageRankList(LinkThreeDimMatrix *ltm,double a,double c);
    void deal();//计算pageRank算法
    double * dealOneIteration();//迭代一次，返回迭代后的pr，不过这是一个new新的，需要delete[]
    pair<string,double>* printMaxPageRankScore(int K,string pageFile);
};


#endif //ACAUTO_PAGERANKLIST_H
