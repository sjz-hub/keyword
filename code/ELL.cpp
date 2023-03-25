//
// Created by ÀÔΩ®Ó» on 2022/12/11.
//

#include "ELL.h"

#include <iostream>
using namespace std;

ELL::ELL(LinkThreeDimMatrix *ltm):ltm(ltm) {
    N = ltm->getN();
    du = new int [N];
    for(int i = 0; i < N; ++i) du[i] = ltm->getRoot()[i][0]->getDu();
    graph = new int* [N];
    weight = new int*[N];
    for(int i = 0; i < N; ++i){
        graph[i] = new int[du[i]];
        weight[i] = new int[du[i]];
    }
    buildGraph();
}

void ELL::buildGraph() {
    int M = ltm->getM();
    for(int i = 0; i < N; ++i){
        int k = 0;
        LinkList *ll;
        for(int j = 0; j < M ;++j){
            ll = ltm->getRoot()[i][j]->getNext();
            while(ll){
                graph[i][k] = ll->getIndex();
                weight[i][k] = ll->getWeight();
                ++k;
                ll = ll->getNext();
            }
        }
        if(k != du[i]) {
            cout<<"this is a error"<<i<<" "<<k<<" "<<du[i]<<endl;
        }
    }
}

