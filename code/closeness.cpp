//
// Created by �ｨ�� on 2022/12/5.
//

#include <queue>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include "closeness.h"

closeness::closeness(LinkThreeDimMatrix *ltm,ELL *ell,int K):ltm(ltm),ell(ell),K(K) {
    fa = ltm->getFa();
    faNum = ltm->getFaNum();
    wordNum = ltm->getN();
    maxWeight = wordNum;
    wordClose = new double[wordNum];
    score = new double[K];
    distance = new long long int[wordNum];
    for(int i = 0; i < K; ++i) score[i] = 1000000000000000;
}

void closeness::dealAllPoint() {
    cout<<"�������е�ķ���"<<endl;

    double time1 = clock();
    double time2;
    int *dis = new int[wordNum];//��ʾ��̾���
    int *vis = new int[wordNum];//0��ʾû���ҵ���̾��룬1��ʾ�ҵ�����̾���

    for(int i = 0; i < wordNum;++i){
        if(i % 10 == 0){
            time2 = clock();
            cout<<i<<"ʱ�䣺"<<(time2-time1)/CLOCKS_PER_SEC<<endl;
            time1 = time2;
        }
        wordClose[i] = dealOnePoint(i,dis,vis);
        if(score[0] == -1 || score[0] > wordClose[i]) {
            score[0] = wordClose[i];
            sort(score,score+K,[](double a,double b){return a>b;});
        }
        distance[i] = wordClose[i];
        wordClose[i] = 1.0 / wordClose[i];
    }
    delete []dis;
    delete []vis;
}

void closeness::dealAllPointWithELL() {
    cout<<"�������е�ķ���"<<endl;
    double time1 = clock();
    double time2;
    int *dis = new int[wordNum];//��ʾ��̾���
    int *vis = new int[wordNum];//0��ʾû���ҵ���̾��룬1��ʾ�ҵ�����̾���
    for(int i = 0; i < wordNum;++i){
        if(i % 1000 == 0){
            time2 = clock();
            cout<<i<<"ʱ�䣺"<<(time2-time1)/CLOCKS_PER_SEC<<endl;
            time1 = time2;
        }
        wordClose[i] = dealOnePointWithELL(i,dis);
        if(score[0] == -1 || score[0] > wordClose[i]) {
            score[0] = wordClose[i];
            sort(score,score+K,[](double a,double b){return a>b;});
        }
        distance[i] = wordClose[i];
        wordClose[i] = 1.0 / wordClose[i];

    }
//    cout<<"Ĭ�����Ȩ�أ�"<<maxWeight<<endl;
    delete []dis;
    delete []vis;
}

double closeness::dealOnePointWithELL(int index, int *dis) {
    //��ʼֵΪ wordNum,�����ͨ���򲻿���ΪwordNum �� �������������ʦ��ΪȨ���ˣ���ÿ���ߵ�Ȩ�ز�Ϊ1�ˣ�����������ܲ�׼ȷ������Ҳ���ǱȽϺ�����
    for(int i = 0; i < wordNum; ++i) dis[i] = maxWeight;
    // first��ʾdis,second��ʾindex
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q; //С����
    q.push(make_pair(0,index));
    pair<int,int> now;
    pair<int,int> insert;
    int u,v,weight;
    double nowS = 0;
    nowS = (wordNum - faNum[find(index)])*(double)maxWeight;//���ﲻ��double������⣬�洦
    int *graph;
    int *Weight;
    int du = 0;
    int **tempGraph = ell->getGraph();
    int **tempWeight = ell->getWeight();
    while(!q.empty()){
        now = q.top();
        q.pop();
        if(dis[now.second] < now.first) continue;
        dis[now.second] = now.first;
        nowS +=dis[now.second];//���㵱ǰ��������Ľڵ����̾����
        if(score[0] != -1 && nowS > score[0]) {//˵����ʱ�϶����������
            return nowS;
        }
        u = now.second;
        graph = tempGraph[u];
        Weight = tempWeight[u];
        du = ell->getDu()[u];
        for(int j = 0; j < du; ++j){
            v = graph[j];
            weight = Weight[j];
            weight = 1;//��������Ϊ1
            if(dis[u] + weight < dis[v]) {
                dis[v] = dis[u] + weight;
                insert.first = dis[v];
                insert.second = v;
                q.push(insert);
            }
        }
    }
    return nowS;
}

int closeness::find( int x){
    if(x == fa[x]) return x;
    else return fa[x] = find(fa[x]);
}

// ���������Լ�һ���������Ż���
// ����һ��������ǰ����õķ���������̾���
// �����ǰ�ڵ��Ѿ��ҵ��Ľڵ����̾���ʹ��������̾��룬��û�б�Ҫ�������в����ˣ���Ϊ��ǰindex�ڵ�һ��������õĽڵ�
// ���ܴ��ݾ��룬�����Ǵ��ݷ�������Ϊ���������ͨͼ�Ľڵ�ĸ�����ͬ����������
double closeness::dealOnePoint(int index,int *dis,int *vis) {
    for(int i = 0; i < wordNum; ++i) vis[i] = 0;
    //��ʼֵΪ wordNum,�����ͨ���򲻿���ΪwordNum �� �������������ʦ��ΪȨ���ˣ���ÿ���ߵ�Ȩ�ز�Ϊ1�ˣ�����������ܲ�׼ȷ������Ҳ���ǱȽϺ�����
    for(int i = 0; i < wordNum; ++i) dis[i] = maxWeight;
    // first��ʾdis,second��ʾindex
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q; //С����
    q.push(make_pair(0,index));
    pair<int,int> now;
    pair<int,int> insert;
    LinkList *nowList;
    int u,v,weight;
    int M = ltm->getM();
    double nowS = 0;
    nowS = (wordNum - faNum[find(index)])*(double)maxWeight;//���ﲻ��double������⣬�洦
    while(!q.empty()){
        now = q.top();
        q.pop();
        if(vis[now.second] == 1 || dis[now.second] < now.first) continue;
        dis[now.second] = now.first;
        vis[now.second] = 1;
        nowS +=dis[now.second];//���㵱ǰ��������Ľڵ����̾����
        if(score[0] != -1 && nowS > score[0]) {//˵����ʱ�϶����������
            return nowS;
        }
        u = now.second;
        for(int j = 0; j < M; ++j){
//            nowList = ltm->getRoot()[u][j]->getNext();
            nowList = ltm->getRoot()[u][j]->next;
            while(nowList != nullptr){
//                v = nowList->getIndex();
//                weight = nowList->getWeight();
                v = nowList->index;
                weight = nowList->weight;
                if(dis[u] + weight < dis[v]) {
                    dis[v] = dis[u] + weight;
                    insert.first = dis[v];
                    insert.second = v;
                    q.push(insert);
                }
//                nowList = nowList->getNext();
                nowList = nowList->next;
            }
        }
    }
    return nowS;
}

/*10e10B = 10e7KB = 10e4MB = 10GB    320GB
 *
 * */

pair<string,double>* closeness::printCloseScores(int n, std::string file) {
    pair<int,double> *p = new pair<int,double>[wordNum];
    for(int i = 0; i < wordNum; ++i){
        p[i].first = i;
        p[i].second = wordClose[i];
    }
    sort(p,p+wordNum,[](pair<int,double> a, pair<int,double> b){return a.second>b.second;});
    ofstream ofs;
    ofs.open(file);
    for(int i = 0; i < wordNum; ++i){
        int v = p[i].first;
        ofs<<ltm->getRoot()[v][0]->getValue()<<" "<<wordClose[v]<<" "<<(double(distance[v]))/wordNum<<endl;
    }
    ofs.close();
    pair<string,double> *np = new pair<string,double>[n];
    for(int i = 0; i < n && i < wordNum; ++i){
        int v = p[i].first;
        cout<<ltm->getRoot()[v][0]->getValue()<<" "<<wordClose[v]<<" "<<(double(distance[v]))/wordNum<<endl;
        np[i].first = ltm->getRoot()[v][0]->getValue();
        np[i].second = (double(distance[v]))/wordNum;
    }
    delete []p;
    return np;
}