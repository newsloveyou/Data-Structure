#include<bits/stdc++.h>
#include "Graph.h"
using namespace std;
void Graph::topusort(){
    while(!q.empty())q.pop();
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(in_deg[i]==0){
            cnt++;
            q.push(i);
            topu[cnt]=i;
            node[i].topunum=cnt;
        }
    }
    while(!q.empty()){
        int temp=q.front();
        q.pop();
        for(int i=0;i<(int)node[temp].out.size();i++){
            int v=node[temp].out[i].to;
            if(--in_deg[v]==0){
                cnt++;
                q.push(v);
                topu[cnt]=v;
                node[v].topunum=cnt;
            }
        }
    }
}

void Graph::init(){
    memset(topu,0,sizeof(topu));
    node.clear();
    memset(in_deg,0,sizeof(in_deg));
    ans=INT_MAX;
    n=0,m=0,d=0;
}

void Graph::input(){
   cin>>n>>m>>d;
   for(int i=0;i<=n;i++){
    node.emplace_back(Node());
   }
   for(int i=1;i<=m;i++){
    int u,v,w;
    cin>>u>>v>>w;
    node[u].out.emplace_back(v,w);
    node[v].in.emplace_back(u,w);
    node[u].max_to_cost=max(node[u].max_to_cost,w);
    in_deg[v]++;
   }
}

void Graph::dfs(int num,int cur){//num代表访问了拓扑序列的num个节点 cur表示当前放置的网络放大器的数量
    topusort();
    node[1].press=d;
    if(num>=n){
        ans=min(ans,cur);
        return;
    }
    else {
        int u=topu[num];
        int j=0;
        int flag=0;//标志当前节点的压力值能否保证下一次的成功传输
        int temppress=INT_MAX;
        for(int k=1;k<num;k++){
            int pre_node=topu[k];
            for(auto x:node[pre_node].out){
                if(x.to==u){
                    temppress=min(temppress,node[pre_node].press-x.cost);//如果顶点 x 有多条入边, x 处的压力为到达 x 处的压力 中的最小值
                }
            }
        }
        if(node[u].max_to_cost>temppress)flag=1;
        for(int j=0;j<2;j++){//0和1分别代表两种递归的情况 0是不放置放大器 1是放置放大器
            if(j==1){
                cur++;
                node[u].press=d;
                if(cur>=ans)return;//此时已经超过了之前的ans，不可能更少了 所以直接return即可
                else dfs(num+1,cur);
            }
            else if(flag==1){//此时不放放大器 但是该点的压力值不允许下一次的成功传输 因此直接剪枝 此路不通
                continue;
            }
            //flag!=1&&j==0,不放置放大器
            else if(j==0){
                node[u].press=temppress;
                dfs(num+1,cur);
            }
        }
    }
}

void Graph::bfs(){//相当于后序遍历
    memset(topu,0,sizeof topu);
    topusort();//获得当前网络的拓扑序列
    int sum=0;
    for(int i=n;i>=1;i--){
        int tempnode=topu[i];
        int temppress=0;
        for(int j=0;j<node[tempnode].in.size();j++){
                 int v=node[tempnode].in[j].from;//当前入边的起点
                 int w=node[tempnode].in[j].cost;//当前入边的耗费
                 temppress=max(node[v].press,node[tempnode].press+w);//入边的起点所具有的最大耗费，是它本身的压力/其指向节点的prees+路径消耗
                 if(temppress>d){
                    sum++;//此时需要在tempnode的地方放置一个放大器
                    node[tempnode].press=0;
                    break;
                 }
        }
        for(int j=0;j<node[tempnode].in.size();j++){
            int v=node[tempnode].in[j].from;//当前入边的起点
            int w=node[tempnode].in[j].cost;//当前入边的耗费
            node[v].press=max(node[v].press,node[tempnode].press+w);//更新每个入边的起点的最大耗费
        }
    }
    ans=sum;
    cout<<sum<<endl;
}

void Graph::solve1(){
    dfs(1,0);
    cout<<ans<<endl;
}