#include<cmath>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<iomanip>
#include<iostream>
#include<cstring>
#include<set>
#include<iomanip>
#include<list>
#include<cstdlib>
#include<map>
#include<stack>
#include<queue>
#include<string.h>
#include<sstream>
#include<random>
using namespace std;
template <class K, class E>
struct skipNode//每个存数对的节点都有一个存储数对的element域和个数大于自身级数的指针域
{
    typedef pair<const K, E> pairType;
    pairType element;
    skipNode<K, E>** next;//指针数组，其中next[i]表示i级链表指针
    skipNode(const pairType& thePair, int size) :element(thePair) { next = new skipNode<K, E>*[size]; }
    //构造函数把字典数对存入element，为指针数组分配空间。对于一个lev级链表数对，其size值为lev+1
};
template <class K, class E>
class skipList
{
public:
    skipList(K largeKey, int maxPairs, float prob = 0.5);
    void find(const K&) ;
    void erase(const K&);
    void erase1(const K&);
    void min();
    void max();
    void insert(const pair<const K, E>&);
    void insert1(const pair<const K, E>&);
    void resize();
    int getsize();
    void output();//显示各个操作的次数
    void clear() {
        incount = 0;
        ercount = 0;
        ficount = 0;
        secount = 0;
        recount = 0;
    }
    skipNode<K, E>* search(const K& theKey);
    int incount;//插入操作次数
    int ercount;//删除操作次数
    int ficount;//查找次数
    int secount;//寻找次数
    int recount;//整理次数
    float cutOff;//用于确定级号
    int level() const;//产生级数
    int levels;//当前最大的非空链表
    int dSize;//字典的数对个数
    int maxLevel;//允许的最大链表层数
    skipNode<K, E>* search(const K&) const;
    K tailKey;//最大关键字
    skipNode<K, E>* headerNode;//头节点指针
    skipNode<K, E>* tailNode;//尾节点指针
    skipNode<K, E>** last;//指针数组,last[i]表示i层的最后节点
};
