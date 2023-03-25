//
// Created by 孙建钊 on 2022/11/2.
//

#include <cstring>
#include <valarray>
#include <queue>
#include <fstream>
#include "acNode.h"
using std::string;

int acNode::m = 2;
int acNode::stateNode = 0;
int acNode::stateTransition = 0;

acNode::acNode(int nodeKind): nodeKind(nodeKind) {
    fail = nullptr;
    stateNode++;
    if(nodeKind == 0){//分支节点
        ptr = new acNode *[m+1];
        for(int i = 0; i <= m; ++i) ptr[i] = nullptr;
    }
    else {  // 叶子节点
        ptr = nullptr;
        appearCount = 0;
    }
}

//char * stringToTwoB(string &value, bool flag = false){
////    char *ch1 = new char[value.length()+1];
////    strcpy(ch1,value.c_str());
//    char *ch = new char[(value.length()+1)*2];
//    int nowJ = 0;
//    for(int i = 0; i < value.length();i++){
//        if(nowJ%2 == 0){
//            if(uint8_t(value[i]) <= 128){//说明当前是ASCII
//                ch[nowJ++] = uint8_t(0x80);
//                ch[nowJ++] = uint8_t(value[i]);
//            }
//            else{
//                ch[nowJ++] = uint8_t(value[i]);
//            }
//        }
//        else{
//            ch[nowJ++] = uint8_t(value[i]);
//        }
//    }
//    ch[nowJ] = '\0';
//    if(nowJ%2!=0) cout<<value<<endl<<"this is a error"<<nowJ<<endl;
//    return ch;
//}

pair<char *, char*> stringToCharAndArr(string &value, bool flag = false){
//    char *ch1 = new char[value.length()+1];
//    strcpy(ch1,value.c_str());
    char *ch = new char[(value.length()+1)];
    int nowJ = 0;
    char *p = new char[(value.length()+1)];
    for(int i = 0; i < value.length();i++){

        if(uint8_t(value[i]) <= 128){
            p[nowJ] = '1';
            ch[nowJ++] = uint8_t(value[i]);
        }
        else{
            p[nowJ] ='0';
            ch[nowJ++]=uint8_t(value[i]);
            ++i;
            p[nowJ]='1';
            ch[nowJ++] = uint8_t(value[i]);
        }


       /* if(nowJ%2 == 0){
            if(uint8_t(value[i]) <= 128){//说明当前是ASCII
//                ch[nowJ++] = uint8_t(0x80);
                p[nowJ] = '1';//1表示结尾
                ch[nowJ++] = uint8_t(value[i]);
            }
            else{
                p[nowJ] = '0';
                ch[nowJ++] = uint8_t(value[i]);
            }
        }
        else{
            p[nowJ] ='0';
            ch[nowJ++] = uint8_t(value[i]);
        }*/
    }
    ch[nowJ] = '\0';
    p[nowJ] = '\0';
//    cout<<nowJ<<endl;
//    cout<<value<<endl;
//    cout<<ch<<endl;
//    if(nowJ%2!=0) cout<<value<<endl<<"this is a error"<<nowJ<<endl;
    return make_pair(ch,p);
}

int acNode::queryWord(std::string &value){
    acNode *now = this;
//    char *ch = stringToTwoB(value);
    pair<char*,char*> pa = stringToCharAndArr(value);
    char *ch = pa.first;
    char *p = pa.second;
    int n = log(m)/log(2);//也就是每次移动几位
    int count = 0; //记录查询的次数
    for(int i = 0; i < strlen(ch)*8; i += n){
        count++;
        int num = 0;//表示当前n位二进制的大小
        for(int j = 0 ; j < n; j++){
            num *= 2;
            num += ( ch[(j+i)/8]>>(7-(j+i)%8) & 1 );
        }
        //因为索引0表示的是$
        num++; //所以加1
        if(now->ptr[num] == nullptr){
            delete ch;//释放空间
            delete p;
            return 0;//说明一定是找不到的情况
        }
        if(i == strlen(ch)*8 - n){//说明这是最后一次遍历了
            if(now->ptr[num]->nodeKind == 1){//叶子节点
                if(now->ptr[num]->value == value) {
                    delete ch;//释放空间

                    delete p;
                    return now->ptr[num]->appearCount;//return ++count;
                }
                else {
                    delete ch;//释放空间
                    delete p;
                    return -1;
                }
            }
            else{//内部节点
                if(now->ptr[num]->ptr[0] != nullptr && now->ptr[num]->ptr[0]->value == value) {
                    delete ch;//释放空间
                    delete p;
                    return now->ptr[num]->ptr[0]->appearCount;//return ++count;
                }
                else {
                    delete ch;//释放空间
                    delete p;
                    return -1;//找不到
                }
            }
        }
        else{//不是最后一次遍历
            if(now->ptr[num]->nodeKind == 1){//不是最后一次遍历遇到了叶子节点，说明找不到
                delete ch;//释放空间
                delete p;
                return -1;
            }
            now = now->ptr[num];
        }
    }

    delete ch;//释放空间
    delete p;
}

int getLenValue(string &value){
    char *ch = new char[(value.length()+1)*2];
    int nowJ = 0;
    for(int i = 0; i < value.length();i++){
        if(nowJ%2 == 0){
            if(uint8_t(value[i]) <= 128){//说明当前是ASCII
                ch[nowJ++] = uint8_t(0x80);
                ch[nowJ++] = uint8_t(value[i]);
            }
            else{
                ch[nowJ++] = uint8_t(value[i]);
            }
        }
        else{
            ch[nowJ++] = uint8_t(value[i]);
        }
    }
    ch[nowJ] = '\0';
    if(nowJ%2!=0) cout<<value<<endl<<"this is a error"<<nowJ<<endl;
    int ans = strlen(ch);
    delete []ch;
    return ans;
}
struct Node{
    string value;
    long long int start,end;
    Node(string &word,long long int start,long long int end):value(word),start(start),end(end){}
};
bool cmp(struct Node a1, struct Node a2){
    if(a1.start == a2.start) return a1.end < a2.end;
    else return a1.start < a2.start;
}

int acNode::query(string &value,ofstream &ofs,long long int nowIndex,int &wordNum,vector<string> &vec, bool flag){
    acNode *now = this;
    int valueLen = value.size();
    pair<char*,char*> pa = stringToCharAndArr(value);
    char *ch = pa.first;
    char *p = pa.second;
    if(flag) cout<<ch<<" "<<strlen(ch)<<endl;
    int n = log(m)/log(2);//也就是每次移动几位



    vector<struct Node> v;
    bool rootK = false;//标识当前是否需要i += n
    for(int i = 0; i < strlen(ch)*8; i += n){
        int num = 0;//表示当前n位二进制的大小
        for(int j = 0 ; j < n; j++){
            num *= 2;
            num += ( ch[(j+i)/8]>>(7-(j+i)%8) & 1 );
        }
        //因为索引0表示的是$
        num++; //所以加1
        if(flag) cout<<i<<" "<<now->dep<<" "<<num<<endl;
        if(now->ptr[num] == nullptr) {//说明当前单词找不到了
            acNode *temp = now;
            now = now->fail;
            stateTransition++;
            if(flag) cout<<"a";
            if(now == this) { //这里好像now  now->fail都不对     now的话可能会出现一直没有该节点的情况    now->fail可能会出现 改形改形 掠过的情况
                if(flag) cout<<rootK<<"b";
                if(rootK){
                    i += n;
                    rootK= false;
                }
                else rootK= true;
            }
            else{
                if(flag) cout<<"c";
                rootK = false;
            }
            i -= n;
            continue;
        }
        rootK = false;
        //到这说明ptr[num]可以找到，并且一定是内部节点，因为这里不会存叶子节点
        if((i+n) % 8 == 0  && p[(i+n)/8-1] == '1' /*true*/){
            acNode *pa = now->ptr[num]->fail;
            while(pa != this){
                if(pa->ptr[0] != nullptr) {
                    pa->ptr[0]->appearCount++;
                    wordNum++;
                    vec.push_back(pa->ptr[0]->value);
                    //单词 行号 开始字节位置  结束位置  [)  本行的字节数
                    //ofs<<pa->ptr[0]->value<<" "<<lines<<" "<<to_string((i+n)/8- pa->ptr[0]->value.length())<<" "<<to_string((i+n)/8)<<" "<<valueLen<<endl;
                    v.push_back(Node(pa->ptr[0]->value,nowIndex + (i+n)/8- pa->ptr[0]->value.length(),nowIndex + (i+n)/8));
                    if(flag) cout<<"*"<<pa->ptr[0]->value<<" "<<pa->ptr[0]->appearCount<<" "<<i<<endl;
                }
                pa = pa->fail;
            }
            if(now->ptr[num]->ptr[0] != nullptr){//说明找到了一个单词
                now->ptr[num]->ptr[0]->appearCount++;
                wordNum++;
                vec.push_back(now->ptr[num]->ptr[0]->value);
//                ofs<<now->ptr[num]->ptr[0]->value<<" "<<lines<<" "<<to_string((i+n)/8- now->ptr[num]->ptr[0]->value.length())<<" "<<to_string((i+n)/8)<<" "<<valueLen<<endl;
                v.push_back(Node(now->ptr[num]->ptr[0]->value,nowIndex + (i+n)/8- now->ptr[num]->ptr[0]->value.length(),nowIndex + (i+n)/8));
                if(flag) cout<<"ko"<<now->ptr[num]->ptr[0]->value<<" "<<now->ptr[num]->ptr[0]->appearCount<<" "<<i<<endl;
            }
        }
        now = now->ptr[num];
    }

    sort(v.begin(),v.end(),cmp);
    for(int i = 0; i < v.size(); ++i) {
        ofs<<v[i].value<<" "<<v[i].start<<" "<<v[i].end<<endl;
    }
    delete ch;//释放空间
    delete p;
}

/*0 2 4 6 8 10 12 14 16
 * 0 4 8 12 16
 * 0 8 16
 *
 *
 * */

void acNode::init() {
    fail = this;  // root的fail指针指向自身
    dep = 0;
    stateNode = 0;
    stateTransition = 0;
}




//都指向ptr[1]~ptr[m]，不指向ptr[0]
void acNode::buildFail() {
    acNode * root = this;  //root节点
    this->fail = this;
    std::queue<acNode *> q;

    for(int i = 1; i <= m; ++i){//遍历root节点的孩子节点  root的孩子节点都必须直接指向root
        if(root->ptr[i] == nullptr) continue;
        root->ptr[i]->fail = root;
        root->ptr[i]->dep = root->dep+1;
        if(root->ptr[i]->nodeKind == 0) q.push(root->ptr[i]);
        else cout<<"ad";
    }
    //从第2层开始进行BFS遍历
    while(!q.empty()){//开始BFS遍历
        acNode *now = q.front();
        q.pop();
        //开始遍历当前节点的孩子节点
        for(int i = 1; i <= m; ++i){
            if(now->ptr[i] == nullptr) continue;
            now->ptr[i]->dep = now->dep + 1;
            q.push(now->ptr[i]); //只有内部节点才会放入
            acNode *parentFail = now->fail;
            //设置fail
            if(parentFail->ptr[i] != nullptr) {//说明父亲节点的fail的孩子存在当前相同的内容
                now->ptr[i]->fail = parentFail->ptr[i];
            }
            else{//没有找到
                while(true){
                    parentFail = parentFail->fail;
                    //之前这里的两个if写反了，就会导致出问题
                    if(parentFail->ptr[i]!= nullptr) {
                        now->ptr[i]->fail = parentFail->ptr[i];
                        break;
                    }
                    if(parentFail == parentFail->fail) {//说明到了root节点了都
                        now->ptr[i]->fail = parentFail;
                        break;
                    }

                }
            }

        }

    }
}




//将叶子节点都放在ptr[0]中

void acNode::insert_node(string value, bool flag){
//    saveKeyNum ++;
    acNode *now = this;
    /*char *ch = new char[value.length()+1];
    strcpy(ch,value.c_str());*/
//    char *ch = stringToTwoB(value,flag);
    pair<char*,char*> pa = stringToCharAndArr(value);
    char *ch = pa.first;
    char *p = pa.second;

    if(flag) cout<<ch<<" "<<strlen(ch)<<endl;
    int n = log(m)/log(2);//也就是每次移动几位
    for(int i = 0; i < strlen(ch)*8; i += n){
        int num = 0;//表示当前n位二进制的大小
        for(int j = 0 ; j < n; j++){
            num *= 2;
            num += ( ch[(j+i)/8]>>(7-(j+i)%8) & 1 );
        }
        //因为索引0表示的是$
        num++; //所以加1
        if(flag)
        cout<<num<<" ";
//        if(value == "表棓儿茶素棓酸酯") cout<<"S";
        if(i == strlen(ch)*8 - n){//说明这是最后一次遍历了
            if(now->ptr[num] == nullptr){//为空，则可以直接插入叶子节点
                acNode *new_node = new acNode(1);//
                new_node->value = value;//设置叶子节点的值
//                now->ptr[num] = new_node;    //这里进行了更改，设置为了ptr[0]
                now->ptr[num] = new acNode(0);
                now->ptr[num]->ptr[0] = new_node;
            }
            else{//不为空，说明已经有了内部节点
                if(now->ptr[num]->nodeKind == 1){//若是叶子节点，则表明刚插入的这个值，之前就存在
                    //这里在那时不进行操作，也就是不重复进行插入
                }
                else{//将该节点放到下一层对应节点的ptr[0]上
                    acNode *new_node = new acNode(1);//
                    new_node->value = value;//设置叶子节点的值
                    now->ptr[num]->ptr[0] = new_node;
                }
            }
        }
        else{
            if(now->ptr[num] == nullptr){//说明还没有进行开辟
                now->ptr[num] = new acNode(0);//开辟为内部节点
                now = now->ptr[num];//更改now,指向下一层
            }
            else{//说明已经开辟了，查看其next是叶子还是内部
                acNode *temp = now->ptr[num];
                if(temp->nodeKind == 1){//叶子节点
                    //创建新的分支节点
                    acNode *new_node = new acNode(0);
                    new_node->ptr[0] = now->ptr[num];//将叶子节点放到下一层的node中的ptr的第一个位置
                    now->ptr[num] = new_node;
                    now = now->ptr[num];//更改now的值，用于下次循环
                }
                else{//内部节点
                    now = now->ptr[num];//更改now，指向下一层
                }
            }
        }
    }
    delete ch;//释放空间
    delete p;
}


void acNode::dfsDestoryNode(acNode *now){
    if(now->ptr!= nullptr){
        for(int i = 0; i <= m; ++i){
            if(now->ptr[i] == nullptr) continue;
            dfsDestoryNode(now->ptr[i]);
        }
    }
    delete now;
}

void acNode::close() {
    acNode* root = this;
    dfsDestoryNode(root);
}


