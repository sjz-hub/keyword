//
// Created by 孙建钊 on 2022/12/9.
//

#include "pageRankList.h"

#include <iostream>
#include <set>
#include <ctime>
#include <algorithm>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;

pageRankList::pageRankList(LinkThreeDimMatrix *ltm, double a, double c):ltm(ltm),a(a),c(c) {
    N = ltm->getN();
    pr = new double[N];
    for(int i = 0; i < N; ++i) pr[i] = 1.0 / N;
    du = new int[N];
    for(int i = 0; i < N; ++i) {
        du[i] = ltm->getRoot()[i][0]->getDu();
    }
}

void pageRankList::deal() {

    double s = 0;//表示两次的差值
    double sum = 0;//表示pr的和
    double *npr;
    int k = 0;
    while(true){
        s = 0;
        sum = 0;
        double time1 = clock();
        npr = dealOneIteration();
        double time2 = clock();
        cout<<(time2-time1) / CLOCKS_PER_SEC<<endl; //0.22
        for(int i = 0; i < N; ++i) {
            s += (pr[i] - npr[i]) > 0 ? (pr[i] - npr[i]) : (npr[i] - pr[i]);
            sum += npr[i];
        }
        k++;
        cout<<s<<" "<<sum<<endl;
        delete []pr;
        pr = npr;
        if(s < c) break;
    }
    cout<<"迭代次数为："<<k<<endl;
}

void print(LinkList *ll,LinkMatrix *lm){
    ll = ll->getNext();
    while(ll){
        cout<<ll->getValue()<<" "<<lm->queryIndexOfWord(ll->getValue())<<endl;
        ll = ll->getNext();
    }
    cout<<"end"<<endl;
}

double* pageRankList::dealOneIteration() {
    double* npr = new double[N];
    for(int i = 0; i < N; ++i) npr[i] = 0;
//    int *faNum = lm->getFaNum();
    double ns = 0;
    for(int i = 0; i < N; ++i){//这里不能直接使用faNum[i]=1，因为可能会自己和自己相连，此时求出来的faNum[i]=1，但其实是有边的
        if(/*faNum[i] == 1*/ltm->getRoot()[i][0]->getDu() == 0) {//对于孤立点的情况,这里得孤立点的情况是没有出度，自己和自己连的不算孤立点
            ns += (1.0/N)*(1-a)*pr[i];
        }
    }
    double s = 0;
    for(int i = 0; i < N; ++i) s+=pr[i];
    ns += (s * a / N);
    LinkList *ll;
    int v,ls;
    int M = ltm->getM();
    int *temp = new int [N];
    for(int i = 0; i < N; ++i) temp[i] =0;
    for(int i = 0; i < N; ++i){//计算新的pr
        for(int j = 0; j < M; ++j){
            ll = ltm->getRoot()[i][j]->getNext();
            while(ll){
                //优化后的代码  速度快了特别多  原先这个函数运行一次 55秒左右，优化只有一次运行0.22秒左右
                v = ll->getIndex();//获得节点索引
                ls = ll->getDu();//获得节点的度
                temp[v]++;
                npr[i] += (( 1.0/ls* (1-a)) * pr[v] );
                ll = ll->getNext();
            }
        }
//        while(ll){
//            /*v = lm->queryIndexOfWord(ll->getValue());//获得节点索引
//            // 可以考虑在LinkList中节点直接加入成员v,这样这里运行的时候可以快8倍左右
//            npr[i] += (( 1.0/lm->getRoot()[v]->getLen()* (1-a)) * pr[v] );  //这里使用getRoot()[v]比getRoot[i]竟然慢八倍，离谱
//            ll = ll->getNext();*/
//
//            //优化后的代码  速度快了特别多  原先这个函数运行一次 55秒左右，优化只有一次运行0.22秒左右
//            v = ll->getIndex();//获得节点索引
//            ls = ll->getDu();//获得节点的度
//            npr[i] += (( 1.0/ls* (1-a)) * pr[v] );
//            ll = ll->getNext();
//        }
        //对于孤立节点，认为它是对所有点都存在单向边
        //否则可能权重有问题，pr的和不为1
        npr[i] += ns;
    }

    for(int i = 0; i < N; ++i){
        if(temp[i] != ltm->getRoot()[i][0]->getDu()) {
            cout<<i << " "<< temp[i] <<" "<< ltm->getRoot()[i][0]->getDu()<<endl;
        }
    }
    return npr;
}

pair<string,double>* pageRankList::printMaxPageRankScore(int K,string pageFile) {
    pair<int,double>*p = new pair<int,double>[N];
    for(int i = 0; i < N; ++i) {
        p[i].first = i;
        p[i].second = pr[i];
    }
    sort(p,p+N,[](pair<int,double>a,pair<int,double>b) {return a.second>b.second;});
    pair<string,double> *cp = new pair<string,double>[K];
    for(int i = 0; i < K; ++i){
        int v = p[i].first;
        cp[i].first = ltm->getRoot()[v][0]->getValue();
        cp[i].second = p[i].second;
        cout<<ltm->getRoot()[v][0]->getValue()<<" "<<p[i].second<<endl;
    }
    ofstream ofs;
    ofs.open(pageFile);
    for(int i = 0; i < N; ++i){
        int v = p[i].first;

        ofs<<ltm->getRoot()[v][0]->getValue()<<" "<<p[i].second<<endl;
    }
    ofs.close();
    delete []p;
    return cp;
}