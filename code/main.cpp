#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <set>
#include "closeness.h"
#include "pageRankList.h"
#include "LinkThreeDimMatrix.h"
#include "ELL.h"
using namespace std;

void dealRepeatFile(string file){
    set<string> se;
    ifstream ifs;
    ifs.open(file);
    string str;
    while(getline(ifs,str)){
        se.insert(str);
    }
    ifs.close();

    ofstream ofs;
    ofs.open(file);
    for(auto s:se){
        ofs<<s<<endl;
    }
    ofs.close();
}

int main(){
    string content = "./../../content.txt";
    string keyword = /*"./../../keyword.txt";*/"./../../rank10w.txt";
    string tempKeyword = "./../../tempKeyword.txt";
    string duFile = "./../../duFile.txt";
    string results = "./../../result.txt";
    string closeScore = "./../../closeScore.txt";
    string pageRankFile = "./../../pageRankScore.txt";

//    string content = "./content.txt";
//    string keyword = "./rank10w.txt";
//    string duFile = "./duFile.txt";
//    string results = "./result.txt";
//    string closeScore = "./closeScore.txt";
//    string pageRankFile = "./pageRankScore.txt";

    dealRepeatFile(keyword);

    ofstream ofs;
    ofs.open(results);


    double time1 = clock();
    LinkThreeDimMatrix ltm(keyword,content,duFile,300);
    pair<int,string> *p = ltm.printMaxDu(20);
    for(int i = 0; i < 20; ++i) ofs<<p[i].second<<" "<<p[i].first<<endl;
    ofs<<endl;
    double time2 = clock();
    cout<<"����ȴ���ͼ��ʱ�䣺"<<(time2-time1) / CLOCKS_PER_SEC<<endl;
    ELL ell(&ltm);
    cout<<"���¹���ͼ��ʱ�䣺"<<(clock() - time2) / CLOCKS_PER_SEC<<endl;

    closeness close(&ltm,&ell,20);
    cout<<"��ʼ����ӽ�������"<<endl;
    double time3 = clock();
    close.dealAllPointWithELL();
    double time4 = clock();
    cout<<"����ӽ������Ե�ʱ��Ϊ��"<<(time4 - time3) / CLOCKS_PER_SEC<<endl;
    pair<string,double> *cp = close.printCloseScores(20,closeScore);
    for(int i = 0; i < 20; ++i) ofs<<cp[i].first<<" "<<cp[i].second<<endl;
    ofs<<endl;


    //pagerank
    pageRankList prl(&ltm,0.15,0.00001);
    cout<<"��ʼ����pageRank:"<<endl;
    double time5 = clock();
    prl.deal();
    double time6 = clock();
    cout<<"����pageRank��ʱ��Ϊ��"<<(time6-time5)/CLOCKS_PER_SEC<<endl;
    pair<string,double> *rp = prl.printMaxPageRankScore(20,pageRankFile);
    for(int i = 0; i < 20; ++i) ofs<<rp[i].first<<" "<<rp[i].second<<endl;
    ofs.close();
    return 0;
}

/*
 * 40000*100000=4e9B = 4e6KB = 4e3MB = 4GB ���int��ʾȨ�� ����128GB  Ҫ��10000����32GB 1000:3GB  200:0.6GB
 * */




