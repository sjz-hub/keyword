//
// Created by 孙建钊 on 2022/12/10.
//

#include "LinkMatrix.h"
#include "acNode.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <ctime>
#include <algorithm>

using namespace std;

//可以对行进行hash操作，这样每次不用遍历行
// LinkMatrix
LinkMatrix::LinkMatrix(std::string keyword,std::string content,int distance){
//    wordEdgeNum = nullptr;
    len = 0;
    ifstream ifs;
    ifs.open(keyword);
    string value;
    while(getline(ifs,value)){
        len++;
    }
    ifs.close();
    ifs.open(keyword);
    root = new LinkList * [len];
    for(int i = 0; i < len; ++i){
        ifs>>value;
        root[i] = new LinkList(value);
    }
    cout<<"创建hash表"<<endl;
    hash = new Hash(keyword,len);
    cout<<"开始遍历所有边"<<endl;
    dealAllEdge(keyword,content,distance);
    cout<<"处理并查集"<<endl;
    calFa();
    calIndexAndDu();
}

void LinkMatrix::dealAllEdge(std::string keyword,std::string content,int distance) {
    acNode::m = 16;
    acNode *root = new acNode(0);//
    root->init();
    string wordsFile = keyword;    /*"./../../6.txt";*/  /*"./../../2.txt";  /*"./../../dict.txt";*/
    string contentFile = content;  //"./../../content.txt";  /*"./../../1.txt"; /* //"./../../words.txt";*/
    std::ifstream wordsStream;
    wordsStream.open(wordsFile);
    string str;
    cout<<"insert\n";
    while(true){
        getline(wordsStream,str);
        if(str.empty()) break;
        root->insert_node(str);
    }
    wordsStream.close();
    cout<<"buildFail\n";
    root->buildFail();
    cout<<"query\n";
    std::ifstream contentStream;
    contentStream.open(contentFile);
    int lines= 0;
    long long int NS = 0;
    //暂时关闭生成index
    cout<<"生成单词位置索引"<<endl;
    ofstream indexOfs;
    indexOfs.open("./../../index.txt",ios::out);
    int wordNum=0;
    long long int S = 0;
    vector<string> v;
    double time1 = clock();
    while(getline(contentStream,str)){
        if(str.empty()) break;
        lines += 1;
        if(lines % 1000 == 0) {
            double time2 = clock();
            cout<<(time2 - time1) / CLOCKS_PER_SEC<<endl;
            time1 = time2;
            cout<<lines<<endl;
        }
        root->query(str,indexOfs,S,wordNum,v);//都是从第0行开始计数
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
    cout<<"wordNum:"<<wordNum<<endl;
    indexOfs.close();
    contentStream.close();
    wordsStream.close();
    root->close();//释放空间
}

int LinkMatrix::find(int x) {
    if(x == fa[x]) return x;
    else return fa[x] = find(fa[x]);
}

void LinkMatrix::calFa() {
    faNum = new int[len];
    for(int i = 0; i < len; ++i) faNum[i] = 0;
    fa = new int[len];
    for(int i = 0; i < len; ++i) fa[i] = i;
    int v,fu,fv;
    LinkList *ll;
    for(int i = 0; i < len; ++i){
        ll = root[i];
        ll = ll->getNext();
        while(ll){
            v = queryIndexOfWord(ll->getValue());
            fu = find(i);
            fv = find(v);
            if(fu != fv){
                fa[fv] = fu;
            }
            ll = ll->getNext();
        }
    }
    for(int i = 0; i < len; ++i){
        faNum[find(i)]++;
    }
}

void LinkMatrix::calIndexAndDu() {
    for(int i = 0; i < len; ++i){
        LinkList *ll = root[i];
        while(ll){
            ll->setIndex(queryIndexOfWord(ll->getValue()));
            ll->setDu(root[ll->getIndex()]->getLen());
            ll = ll->getNext();
        }
    }
}

int LinkMatrix::queryIndexOfWord(std::string value) {
    pair<int *,int>ha = hash->query(value);
    int index = -1; //最后index不可能为-1，如果为-1表示出问题了
    for(int i = 0; i < ha.second; ++i){
        if(root[ha.first[i]]->getValue() == value){
            index = ha.first[i];
            break;
        }
    }
    delete []ha.first;
    return index;
}

void LinkMatrix::insertEdge(std::string &u, std::string &v) {
    int index = queryIndexOfWord(u);
    root[index]->insertNode(v);
}

bool cmp(pair<int,int>a,pair<int,int>b){
    return a.first>b.first;
}

void LinkMatrix::printMaxN(int n) {
    string file ="./../../du.txt";
    ofstream ofs;
    ofs.open(file);
    wordEdgeNum = new pair<int,int>[len];
    for(int i = 0; i < len; ++i){
        wordEdgeNum[i].second = i;
        wordEdgeNum[i].first = root[i]->getLen();
    }
    sort(wordEdgeNum,wordEdgeNum+len,cmp);
    for(int i = 0; i < len; ++i) {
        ofs<<root[wordEdgeNum[i].second]->getValue()<<" "<<wordEdgeNum[i].first<<endl;
    }
    ofs.close();
    for(int i = 0; i < n && i < len;i++){
        cout<<root[wordEdgeNum[i].second]->getValue()<<" "<<wordEdgeNum[i].first<<" ";
    }
    cout<<endl;
}
