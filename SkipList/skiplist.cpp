#include "skiplist.h"
template <class K, class E>//初始化的时间复杂度是O(maxLevel)
skipList<K, E>::skipList(K largeKey, int maxPairs, float prob)
{//关键字小于largeKey;数对个数最多为maxPairs; 0<prob<1，prob的值是i-1级链表数对同时也是i级链表数对的概率
    cutOff = prob * RAND_MAX;//RAND_MAX 是 <stdlib.h> 中伪随机数生成函数 rand 所能返回的最大数值。
    maxLevel = (int)ceil(logf((float)maxPairs));//若初始化为课本上的层数则各个操作之间的比较次数会上升
    levels = 0;
    dSize = 0;
    tailKey = largeKey;
    incount=0;
    ficount=0;
    ercount=0;
    recount=0;
    //创建头节点、尾节点以及数组last
    pair<K, E> tailPair;
    tailPair.first = tailKey;
    headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);//头节点有maxLevel+1个指向尾节点的指针
    tailNode = new skipNode<K, E>(tailPair, 0);
    last = new skipNode<K, E> *[maxLevel + 1];//last[i]表示第i层的最后节点
    for (int i = 0; i <= maxLevel; i++)
        headerNode->next[i] = tailNode;
}
template <class K, class E>
void skipList<K, E>::find(const K& theKey) //从高级链向低级链查找，因为不涉及更改跳表结构，所以不需要去额外判断是否需要维护一些需要维护的值
//时间复杂度为O（n+levels），n为元素数，levels为最高非空跳表等级，该情况为所要查找的元素为最大元素，且除第一个元素外只存在于第0级链。但是平均复杂度为O（log n）
{
    if (theKey >= tailKey)return;
    skipNode<K, E>* beforeNode = headerNode;//是关键字为thekey的节点之前最右边的位置
    for (int i = levels; i >= 0; i--)//逐级向下
    {//在第i级链中搜索
        while (beforeNode->next[i]->element.first < theKey) {
            beforeNode = beforeNode->next[i];
            ficount++;    
        }
    }
    //检查是否下一个节点拥有关键值theKey
    if (beforeNode->next[0]->element.first == theKey) {
        cout << "YES" << endl;
    }
    else cout << "NO" << endl;
}
template <class K, class E>
skipNode<K, E>* skipList<K, E>::search(const K& theKey) //平均复杂度为O（log n），主要目的是为了返回待查找元素的，且将last的各级指针指向该元素的各级的前一个元素，便于插入函数和删除函数，
{   //搜索theKey，并保存每一级链最后查看的节点位置在数组last中
    //指针beforeNode,指向可能与theKey匹配节点的前一个节点
    skipNode<K, E>* beforeNode = headerNode;
    for (int i = levels; i >= 0; i--)
    {
        while (beforeNode->next[i]->element.first < theKey&&beforeNode->next[i]!=tailNode) {
            beforeNode = beforeNode->next[i];
            secount++;
        }
        last[i] = beforeNode;//存储在每一级链表搜索时所遇到的最后一个节点的指针
    }
    return beforeNode->next[0];//这个返回的位置是插入时theKey应该插入的位置，也是删除时theKey所在的位置
}
template <class K, class E>//级的分配方法,为新数对指定它所属的级链表
int skipList<K, E>::level() const
{   //产生一个小于等于maxLevel的随机级号
    int lev = 0;
    while (rand() <= cutOff) lev++;//rand()会返回一个从0到最大随机数的任意整数
    return (lev <= maxLevel) ? lev : maxLevel;
    //缺点是可能为某些元素分配特别大的级，从而导致一些元素的级远远超过log1/pN，其中N为字典中预期的最大数目，因此设定级数上限maxLevel
}
template <class K, class E>//首先先判断是否该元素越界，再进行查找，看是否已存在
//随后维护一下最大元素和最小元素，随后随机获取该元素的等级，判断是否超过了最大等级，再之后进行插入操作，利用search函数中提前铺垫好的last指针，直接进行插入即可,平均时间复杂度为O(log n)
void skipList<K, E>::insert(const pair<const K, E>& thePair)
{
    secount = 0;
    if (thePair.first >= tailKey)
    {
        ostringstream s;
        s << "Key=" << thePair.first << " must be <" << tailKey;
    }
    skipNode<K, E>* theNode = search(thePair.first);
    incount += secount;
    if (theNode->element.first == thePair.first)
    {
        theNode->element.second = thePair.second;
        cout << "该元素已经存在" << endl;
        return;
    }
    //不存在，确定新节点的级
    int theLevel = level();
    if (theLevel > levels)//保证theLevel<=levels+1
    {
        theLevel = ++levels;
        last[theLevel] = headerNode;
    }
    //产生新节点，并插入
    skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
    incount++;
    for (int i = 0; i <= theLevel; i++)
    {   //插入到第i级链
        newNode->next[i] = last[i]->next[i];
        last[i]->next[i] = newNode;
    }
    dSize++;
    int sum = 0;
    for (skipNode<K, E>* cur = headerNode->next[0]; cur != tailNode; cur = cur->next[0])sum = cur->element.first ^ sum;
    cout  << sum << endl;
    return;
}
template <class K, class E>
void skipList<K, E>::insert1(const pair<const K, E>& thePair)//插入元素后不产生异或和
{
    secount = 0;
    if (thePair.first >= tailKey)
    {
        ostringstream s;
        s << "Key=" << thePair.first << " must be <" << tailKey;
    }
    skipNode<K, E>* theNode = search(thePair.first);
    incount += secount;
    if (theNode->element.first == thePair.first)
    {
        theNode->element.second = thePair.second;
        return;
    }
    //不存在，确定新节点的级
    int theLevel = level();
    if (theLevel > levels)//保证theLevel<=levels+1
    {
        theLevel = ++levels;
        last[theLevel] = headerNode;
    }
    //产生新节点，并插入
    skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
    incount++;
    for (int i = 0; i <= theLevel; i++)
    {   //插入到第i级链
        newNode->next[i] = last[i]->next[i];
        last[i]->next[i] = newNode;
    }
    dSize++;
    return;
}
template <class K, class E>//通过search函数提前铺垫好的last指针，直接进行更改即可，随后再维护一下levels和size
//复杂度同insert函数，最差为O(n+levels）,平均为O（log n）
void skipList<K, E>::erase(const K& theKey)
{
    secount = 0;
    if (theKey >= tailKey) return;
    skipNode<K, E>* theNode = search(theKey);
    ercount += secount;
    ercount++;
    if (theNode->element.first != theKey) return;
    for (int i = 0; i <= levels && last[i]->next[i] == theNode; i++){
        last[i]->next[i] = theNode->next[i];
        ercount++;}
    //更新levels，从上到下更新
    while (levels > 0 && headerNode->next[levels] == tailNode){
        levels--;
        ercount++;}
    //cout << theNode->element.first << ' ' << theNode->element.second << endl;
    delete theNode;
    dSize--;
    int sum = 0;
    //输出删除元素后跳表中所有元素的异或和
    for (skipNode<K, E>* cur = headerNode->next[0]; cur != tailNode; cur = cur->next[0])sum = cur->element.first ^ sum;
    cout  << sum << endl;
    return;
}
template <class K, class E>
void skipList<K, E>::erase1(const K& theKey)//删除元素后不产生异或和
{
    secount = 0;
    if (theKey >= tailKey) return;
    skipNode<K, E>* theNode = search(theKey);
    ercount += secount;
    ercount++;
    if (theNode->element.first != theKey) return;
    for (int i = 0; i <= levels && last[i]->next[i] == theNode; i++){
        last[i]->next[i] = theNode->next[i];
        ercount++;}
    //更新levels
    while (levels > 0 && headerNode->next[levels] == tailNode){
        levels--;
        ercount++;}
    delete theNode;
    dSize--;
    //cout << "删除成功,现在跳表中还剩" << dSize << "个元素" << endl;
    return;
}
template <class K, class E>
//最差复杂度为O(n+levels)，平均为O（log n），主要体现在更新levels上
void skipList<K, E>::min()
{
    if (dSize == 0) {
        cout << "跳表为空,请重新插入数据" << endl;
        return;
    }
    skipNode<K, E>* theNode = headerNode->next[0];
    //从下到上删除指针
    for (int i = 0; i <= levels && headerNode->next[i] == theNode; i++){
        headerNode->next[i] = theNode->next[i];
        ercount++;
        }
    //更新levels
    while (levels > 0 && headerNode->next[levels] == tailNode){
        levels--;
        ercount++;
        }
    cout <<theNode->element.first << endl;
    delete theNode;
    dSize--;
    //cout << "删除成功,现在跳表中还剩" << dSize << "个元素" << endl;
}
template <class K, class E>
void skipList<K, E>::max()
{
    if (dSize == 0) {
        cout << "跳表为空" << endl;
        return;
    }
    skipNode<K, E>* beforeNode = headerNode;//从上到下每层寻找，最后一层就是最大值所在层
    for (int i = levels; i >= 0; i--)
    {
        while (beforeNode->next[i]->element.first < tailKey)
            beforeNode = beforeNode->next[i];
        last[i] = beforeNode;//i级链最后查看的节点位置
    }
    cout <<beforeNode->element.first << endl;
    erase1(beforeNode->element.first);
}
template<class K,class E>
void skipList<K,E>::resize()//整体目标是为了提高上下两层之间的联系，避免不必要的浪费
{
    bool reing = false;
    int now = levels;
    int flag = 2;
    while (flag && now >= 1)
    {
        flag--;
        skipNode<K,E>* low = headerNode;
        skipNode<K,E>* high = headerNode;
        while (low->next[now] != tailNode && low->next[now]->next[now] != tailNode &&
            high->next[now + 1] != tailNode && high->next[now + 1]->next[now + 1] != tailNode)
        {
             // high1 ----- > high2
            // low1  ----- > low2
            recount++;
            reing = true;
            //符合要删除情况说明高层链的这条链有些冗余,上下两层重复出现了，因此减少上层数对的数量
            if (low->next[now]->element.first == high->next[now + 1]->element.first &&
                low->next[now]->next[now]->element.first == high->next[now + 1]->next[now + 1]->element.first)
            {
                
                recount++;
                skipNode<K,E>* temp = high->next[now + 1]->next[now + 1];
                high->next[now + 1]->next[now + 1] = temp->next[now + 1];
                temp->next[now + 1] = tailNode;
            }
            //                       high1 ----- > high2
            // low1  ----- > low2
            //此时将low1指针移动到high1位置，增加low指针所在这一层的价值
            else if (low->next[now]->element.first < high->next[now + 1]->element.first)
            {
                while (low->next[now]->element.first < high->next[now + 1]->element.first)
                {
                    recount++;
                    low = low->next[now];
                }
            }
            // high1 ----- >  ------>  high2
            // low1  ----- > low2
            //将low1移动到high2位置，将high1移动到high2
            else
            {
                while (low->next[now]->next[now]->element.first < high->next[now + 1]->next[now + 1]->element.first)
                {
                    recount++;
                    low = low->next[now];
                }
                low = low->next[now];
                high = high->next[now + 1];
            }
        }
        --now;
    }
    for (int i = levels; i >= 0; i--)
    {//更新level
        recount++;
        if (headerNode->next[i] == tailNode)levels--;
        else  break;
    }
    if (reing)cout<<"resize"<<endl;
    else cout<<"no resize"<<endl;
}
template <class K,class E>
int skipList<K, E>::getsize() {
    return dSize;
}
template <class K,class E>
void skipList<K, E>::output() {
    cout << "插入操作中元素比较次数为" << incount << endl;
    cout << "查找操作中元素比较次数为" << ficount << endl;
    cout << "删除操作中元素比较次数为" << secount+ercount << endl;
    cout << "调整操作中元素比较次数为" << recount << endl;
}


