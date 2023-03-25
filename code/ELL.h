//
// Created by 孙建钊 on 2022/12/11.
//

#ifndef ACAUTO_ELL_H
#define ACAUTO_ELL_H

#include "LinkThreeDimMatrix.h"

class ELL {
private:
    LinkThreeDimMatrix *ltm;
    int N;//单词数目
    int **graph;//表示ELL的图 graph[i]表示节点i所连的边 graph[i][0]表示和这个节点相连
    int **weight;//和graph对应，表示相应的权重
    int *du;//表示度
public:
    ELL(LinkThreeDimMatrix *ltm);
    void buildGraph();
    int ** getGraph(){return graph;}
    int ** getWeight(){return weight;}
    int *getDu(){return du;}
};


#endif //ACAUTO_ELL_H
