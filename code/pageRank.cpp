//
// Created by Ëï½¨îÈ on 2022/12/9.
//

#include <fstream>
#include "pageRank.h"

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;


pageRank::pageRank(double d,double c, int N):d(d),c(c),N(N) {
    p = new double [N];
    for(int i = 0; i < N; ++i) p[i] = 1.0 / N;
    A = new double*[N];
    for(int i = 0; i < N; ++i) A[i] = new double[N];
}

void pageRank::deal(){

    double *np;
    while(true){
        np = diedai();
        double s = 0;
        double sum = 0 ;
        for(int i = 0; i < N; ++i){
            s+= (np[i] - p[i]) > 0 ? (np[i] - p[i]) : (p[i] - np[i]);
            sum+=np[i];
        }
        std::cout<<"s:"<<s<<" "<<sum<<std::endl;
        if(s<c) break;
        double *temp = p;
        p = np;
        delete []temp;

    }
    cout<<"*--------------------------"<<endl;
    for(int i = 0; i < N;++i) std::cout<<p[i]<<std::endl;

}

void pageRank::inputEdge(std::string filepath) {
    int **a = new int*[N];
    for(int i = 0; i < N; ++i) a[i] = new int[N];
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            a[i][j]=0;
        }
    }

    std::ifstream ins;
    ins.open(filepath);
    int u,v;
    int *s = new int [N];
    for(int i = 0; i < N; ++i) s[i] = 0;
    std::cout<<filepath<<std::endl;
    string str;
    while(ins){
        ins>>u>>v;
        std::cout<<u<<"qwe"<<v<<" "<<str<<std::endl;
        a[v][u]=1;
        s[u]++;
        std::cout<<u<<" "<<s[u]<<std::endl;
        if(u == 3 && v == 4) break;
    }

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            std::cout<<a[i][j] <<" ";
        }
        std::cout<<std::endl;
    }
    for(int i = 0; i < N; ++i) std::cout<<s[i]<<" ";std::cout<<std::endl;

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            if(s[j] == 0) {
                A[i][j] =  d/N;
            }
            else{
                A[i][j] =  (1-d)*((double)a[i][j])/s[j] + d/N;
            }

        }
    }
    std::cout<<"*********************"<<std::endl;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            std::cout<<A[i][j] <<" ";
        }
        std::cout<<std::endl;
    }


    delete []s;
    for(int i = 0; i < N; ++i) delete[] a[i];
    delete []a;
}

double *pageRank::diedai() {
    double *np = new double[N];
//    for(int i = 0; i < N; ++i) np[i] = 0;
    for(int i = 0; i < N; ++i){
        np[i] = 0;
        for(int j = 0; j < N; ++j){
            np[i] += ( A[i][j] * p[j] );
        }
    }
    return np;
}