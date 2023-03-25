//
// Created by �ｨ�� on 2022/12/9.
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

    double s = 0;//��ʾ���εĲ�ֵ
    double sum = 0;//��ʾpr�ĺ�
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
    cout<<"��������Ϊ��"<<k<<endl;
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
    for(int i = 0; i < N; ++i){//���ﲻ��ֱ��ʹ��faNum[i]=1����Ϊ���ܻ��Լ����Լ���������ʱ�������faNum[i]=1������ʵ���бߵ�
        if(/*faNum[i] == 1*/ltm->getRoot()[i][0]->getDu() == 0) {//���ڹ���������,����ù�����������û�г��ȣ��Լ����Լ����Ĳ��������
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
    for(int i = 0; i < N; ++i){//�����µ�pr
        for(int j = 0; j < M; ++j){
            ll = ltm->getRoot()[i][j]->getNext();
            while(ll){
                //�Ż���Ĵ���  �ٶȿ����ر��  ԭ�������������һ�� 55�����ң��Ż�ֻ��һ������0.22������
                v = ll->getIndex();//��ýڵ�����
                ls = ll->getDu();//��ýڵ�Ķ�
                temp[v]++;
                npr[i] += (( 1.0/ls* (1-a)) * pr[v] );
                ll = ll->getNext();
            }
        }
//        while(ll){
//            /*v = lm->queryIndexOfWord(ll->getValue());//��ýڵ�����
//            // ���Կ�����LinkList�нڵ�ֱ�Ӽ����Աv,�����������е�ʱ����Կ�8������
//            npr[i] += (( 1.0/lm->getRoot()[v]->getLen()* (1-a)) * pr[v] );  //����ʹ��getRoot()[v]��getRoot[i]��Ȼ���˱�������
//            ll = ll->getNext();*/
//
//            //�Ż���Ĵ���  �ٶȿ����ر��  ԭ�������������һ�� 55�����ң��Ż�ֻ��һ������0.22������
//            v = ll->getIndex();//��ýڵ�����
//            ls = ll->getDu();//��ýڵ�Ķ�
//            npr[i] += (( 1.0/ls* (1-a)) * pr[v] );
//            ll = ll->getNext();
//        }
        //���ڹ����ڵ㣬��Ϊ���Ƕ����е㶼���ڵ����
        //�������Ȩ�������⣬pr�ĺͲ�Ϊ1
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