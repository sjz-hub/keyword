//
// Created by 孙建钊 on 2022/11/2.
//

#ifndef ACAUTO_ACNODE_H
#define ACAUTO_ACNODE_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class acNode {
public:
    static int m; //树的阶数
    static int stateNode; // 状态节点数
    static int stateTransition;//状态转移次数
    acNode ** ptr;  // 下一层的指针ptr[0]表示的是上一层的最后一个叶子节点
    std::string value; //存储叶子节点的字符串
    int appearCount; //叶子节点的时候表示当前字符串出现的次数
    int nodeKind; //0表示分支节点   1 表示叶子节点
    acNode * fail; // 失效指针
    int dep;
    acNode(int nodeKind);
    void insert_node(std::string value,bool flag = false);//将value插入到trie树中，只有root根节点可以调用该函数
    int query(std::string &value,ofstream &ofs, long long int nowIndex,int &wordNum,vector<string> &v,bool flag = false);//查询树中节点在value中出现的次数
    int queryWord(std::string &value); //查询一个单词出现的次数，在这之前需要调用过一次query
    void init(); //root初始化函数 只有root可以调用
    void buildFail();//使用BFS创建fail指针  只有root调用该函数
    void close();//只有root可以调用，释放树节点空间
    void dfsDestoryNode(acNode *now);// 递归删除节点
};


#endif //ACAUTO_ACNODE_H
