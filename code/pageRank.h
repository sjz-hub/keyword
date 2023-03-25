//
// Created by 孙建钊 on 2022/12/9.
//

#ifndef ACAUTO_PAGERANK_H
#define ACAUTO_PAGERANK_H
#include <String>


class pageRank {
public:
    int N;//节点个数
    double d;//默认值为0.15
    double c;//迭代最小插值
    double **A;//矩阵
    double *p;//pr向量  按照列向量处理
    pageRank(double d,double c,int N);
    double * diedai();
    void inputEdge(std::string filepath);
    void deal();
};


#endif //ACAUTO_PAGERANK_H
