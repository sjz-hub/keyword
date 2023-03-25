//
// Created by 孙建钊 on 2022/12/5.
//

#ifndef ACAUTO_CLOSENESS_H
#define ACAUTO_CLOSENESS_H

#include "LinkList.h"
#include "LinkMatrix.h"
#include "LinkThreeDimMatrix.h"
#include "ELL.h"
class closeness {
private:
    int wordNum;//单词的个数
    double *wordClose;//数组，每个元素表示一个单词的中心分数， wordClose[i] 表示的是第i个单词
    LinkThreeDimMatrix *ltm;//用于处理图
    int *fa;//这个是单词索引的祖宗
    int *faNum; //这个是单词索引祖宗集合的元素个数
    int K;//表示找到前20个最大中心性分数
    double *score;//存储前20大中心性分数
    int maxWeight;//当不连通的时候认为两个点的权重 默认等于wordNum
    ELL *ell;
    long long int *distance;
public:
    closeness(LinkThreeDimMatrix *ltm,ELL *ell,int K);
    void dealAllPointWithELL();
    double dealOnePointWithELL(int index,int *dis);
    void dealAllPoint();//处理所有节点的分数
    double dealOnePoint(int index,int *dis,int *vis);//处理一个节点的分数,单词索引为index
    pair<string,double> *printCloseScores(int n,string file);//输出前n大，并且将各个分数保存在file文件中
    int find(int x);
};

#endif //ACAUTO_CLOSENESS_H
