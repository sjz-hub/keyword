//
// Created by �ｨ�� on 2022/12/10.
//

#include <fstream>
#include "LinkThreeDimMatrix.h"
#include "acNode.h"
#include <iostream>
#include <ctime>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;


LinkThreeDimMatrix::LinkThreeDimMatrix(std::string keyword, std::string content,string duFile,int M):M(M) {
    //���㵥�ʵĸ���N
    N = 0;
    ifstream ifs;
    ifs.open(keyword);
    string str;
    while(getline(ifs,str)){
        ++N;
    }
    ifs.close();

    //��ʼ��root
    ifs.open(keyword);
    root = new LinkList ** [N];

    for(int i = 0; i < N; ++i){
        getline(ifs,str);
        root[i] = new LinkList * [M];
        for(int j = 0; j < M; ++j){
            root[i][j] = new LinkList(str);
        }
    }
    fa = new int[N];
    faNum = new int[N];
    //����hash��
    cout<<"����hash��"<<endl;
    double time1 = clock();
    hash = new Hash(keyword,N);
    double time2 = clock();
    cout<<"����hash���ʱ�䣺"<<(time2-time1)/CLOCKS_PER_SEC<<endl;
    //��ʼ�������еı�
    cout<<"��ʼ�����,����ͼ"<<endl;
    dealAllEdge(keyword,content);
    double time3 = clock();
    cout<<"����ͼ��ʱ��Ϊ��"<<(time3-time2)/CLOCKS_PER_SEC<<endl;
    //��������ڵ��index��du
    cout<<"��������ڵ�Ķȣ����򱣴��Լ����鼯��"<<endl;
    calIndexAndDu();
    calFa();
    SaveDuAndSort(duFile);
    double time4 = clock();
    cout<<"��������ڵ�Ķȣ����򱣴��Լ����鼯��ʱ��Ϊ��"<<(time4-time3)/CLOCKS_PER_SEC<<endl;
}

void LinkThreeDimMatrix::SaveDuAndSort(string duFile) {
    du = new pair<int,string>[N];
    for(int i = 0; i < N; ++i){
        int s = 0;
        for(int j = 0; j < M; ++j){
            s += root[i][j]->getLen();
        }
        du[i].first = s;
        du[i].second = root[i][0]->getValue();
    }
    sort(du,du+N,[](pair<int,string>a1,pair<int,string>a2){return a1.first>a2.first;});
    ofstream ofs;
    ofs.open(duFile);
    for(int i = 0; i < N; ++i){
        ofs<<du[i].second<<" "<<du[i].first<<endl;
    }
    ofs.close();
}

void LinkThreeDimMatrix::dealAllEdge(string keyword, string content) {
    acNode::m = 16;
    acNode *acRoot = new acNode(0);
    acRoot->init();
    string wordsFile = keyword;
    string contentFile = content;
    std::ifstream wordsStream;
    wordsStream.open(wordsFile);
    string str;
//    cout<<"insert\n";
    while(true){
        getline(wordsStream,str);
        if(str.empty()) break;
        acRoot->insert_node(str);
    }
    wordsStream.close();
//    cout<<"buildFail\n";
    acRoot->buildFail();
//    cout<<"query\n";
    std::ifstream contentStream;
    contentStream.open(contentFile);
    int lines= 0;
    long long int NS = 0;
    //��ʱ�ر�����index
    cout<<"���ɵ���λ������"<<endl;
    ofstream indexOfs;
    int wordNum=0;
    long long int S = 0;
    vector<string> v;
    double time1 = clock();
    while(getline(contentStream,str)){
        if(str.empty()) break;
        lines += 1;
        if(lines % 100000 == 0) {
            double time2 = clock();
            cout<<(time2 - time1) / CLOCKS_PER_SEC<<endl;
            time1 = time2;
            cout<<lines<<endl;
        }
        acRoot->query(str,indexOfs,S,wordNum,v);//���Ǵӵ�0�п�ʼ����
        for(int i = 0; i < v.size(); ++i){
            for(int j = 0; j < v.size(); ++j){
                if(i != j){
                    NS++;
                    insertEdge(v[i],v[j]);
                    insertEdge(v[j],v[i]);
                }
            }
        }

        v.clear();
        S += str.size();
    }
    cout<<NS<<endl;
    indexOfs.close();
    contentStream.close();
    wordsStream.close();
    acRoot->close();
}

int LinkThreeDimMatrix::queryIndexOfWord(std::string value) {
    pair<int *,int>ha = hash->query(value);
    int index = -1; //���index������Ϊ-1�����Ϊ-1��ʾ��������
    for(int i = 0; i < ha.second; ++i){
        if(root[ha.first[i]][0]->getValue() == value){
            index = ha.first[i];
            break;
        }
    }
    if(index == -1) cout<<"queryIndexOfWord"<<endl;
    delete []ha.first;
    return index;
}

int LinkThreeDimMatrix::find(int x) {
    if(x == fa[x]) return x;
    else return fa[x] = find(fa[x]);
}

void LinkThreeDimMatrix::calFa() {
    for(int i = 0; i < N; ++i) fa[i] = i;
    for(int i = 0; i < N; ++i) faNum[i] = 0;
    int u,v,fu,fv;
    LinkList *ll;
    for(int i = 0; i < N; ++i){
        u = i;
        for(int j = 0; j < M; ++j){
            ll = root[i][j]->getNext();
            while(ll){
                v = ll->getIndex();
                fu = find(u);
                fv = find(v);
                fa[fu] = fv;
                ll = ll->getNext();
            }
        }
    }
    for(int i = 0; i < N;++i){
        faNum[find(i)]++;
    }
}

void LinkThreeDimMatrix::insertEdge(std::string &u, std::string &v) {
    int indexU = queryIndexOfWord(u);
    int indexV = hash->getHashKey(v);
    indexV %= M;
    root[indexU][indexV]->insertNode(v);
}
// �ؼ��ʾ�Ȼ��һ����
void LinkThreeDimMatrix::calIndexAndDu() {
    int *du = new int [N];
    for(int i = 0; i < N; ++i) du[i] = 0;
    for(int i = 0; i < N; ++i){
        int s = 0;
        for(int j = 0; j < M; ++j) {
            s += root[i][j]->getLen();
        }
        du[i] = s;
    }
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j){
            LinkList *ll = root[i][j];
            while(ll){
                ll->setIndex(queryIndexOfWord(ll->getValue()));
                int s = 0;
                ll->setDu(du[ll->getIndex()]);
                ll = ll->getNext();
            }
            root[i][j]->setDu(du[i]);
            root[i][j]->setIndex(i);
        }
    }
    delete []du;
}

pair<int,string>* LinkThreeDimMatrix::printMaxDu(int K) {
    pair<int,string> *p = new pair<int,string>[K];
    for(int i = 0; i < K; ++i){
        cout<<du[i].second<<" "<<du[i].first<<endl;
        p[i].first = du[i].first;
        p[i].second = du[i].second;
    }
    return p;
}