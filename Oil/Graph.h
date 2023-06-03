#include<bits/stdc++.h>
using namespace std;
struct inedge{
   int from;
   int cost;
   inedge(int ff,int cc){
    from=ff;
    cost=cc;
   }
};
struct outedge{
    int to;
    int cost;
    outedge(int tt,int cc){
        to=tt;
        cost=cc;
    }
};
class Node{
public:
vector<inedge>in;
vector<outedge>out;
int max_to_cost;
int topunum;
int press;
Node(){
    max_to_cost=0;
    press=0;
    in.clear();
    out.clear();
}
};
class Graph{
    public:
      void solve1(); 
      void bfs();
      void topusort(); 
      void input(); 
      void init(); 
      void dfs(int num,int cnt); 
      int getAns()const{return ans;} 
      int n,m,d; 
    private: 
       int ans; 
       queue<int> q; 
       vector<Node> node; //所有的点 
        int topu[40]; //拓扑序列 
       int in_deg[40]; 

};
