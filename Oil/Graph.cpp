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

void Graph::dfs(int num,int cur){//num����������������е�num���ڵ� cur��ʾ��ǰ���õ�����Ŵ���������
    topusort();
    node[1].press=d;
    if(num>=n){
        ans=min(ans,cur);
        return;
    }
    else {
        int u=topu[num];
        int j=0;
        int flag=0;//��־��ǰ�ڵ��ѹ��ֵ�ܷ�֤��һ�εĳɹ�����
        int temppress=INT_MAX;
        for(int k=1;k<num;k++){
            int pre_node=topu[k];
            for(auto x:node[pre_node].out){
                if(x.to==u){
                    temppress=min(temppress,node[pre_node].press-x.cost);//������� x �ж������, x ����ѹ��Ϊ���� x ����ѹ�� �е���Сֵ
                }
            }
        }
        if(node[u].max_to_cost>temppress)flag=1;
        for(int j=0;j<2;j++){//0��1�ֱ�������ֵݹ����� 0�ǲ����÷Ŵ��� 1�Ƿ��÷Ŵ���
            if(j==1){
                cur++;
                node[u].press=d;
                if(cur>=ans)return;//��ʱ�Ѿ�������֮ǰ��ans�������ܸ����� ����ֱ��return����
                else dfs(num+1,cur);
            }
            else if(flag==1){//��ʱ���ŷŴ��� ���Ǹõ��ѹ��ֵ��������һ�εĳɹ����� ���ֱ�Ӽ�֦ ��·��ͨ
                continue;
            }
            //flag!=1&&j==0,�����÷Ŵ���
            else if(j==0){
                node[u].press=temppress;
                dfs(num+1,cur);
            }
        }
    }
}

void Graph::bfs(){//�൱�ں������
    memset(topu,0,sizeof topu);
    topusort();//��õ�ǰ�������������
    int sum=0;
    for(int i=n;i>=1;i--){
        int tempnode=topu[i];
        int temppress=0;
        for(int j=0;j<node[tempnode].in.size();j++){
                 int v=node[tempnode].in[j].from;//��ǰ��ߵ����
                 int w=node[tempnode].in[j].cost;//��ǰ��ߵĺķ�
                 temppress=max(node[v].press,node[tempnode].press+w);//��ߵ���������е����ķѣ����������ѹ��/��ָ��ڵ��prees+·������
                 if(temppress>d){
                    sum++;//��ʱ��Ҫ��tempnode�ĵط�����һ���Ŵ���
                    node[tempnode].press=0;
                    break;
                 }
        }
        for(int j=0;j<node[tempnode].in.size();j++){
            int v=node[tempnode].in[j].from;//��ǰ��ߵ����
            int w=node[tempnode].in[j].cost;//��ǰ��ߵĺķ�
            node[v].press=max(node[v].press,node[tempnode].press+w);//����ÿ����ߵ��������ķ�
        }
    }
    ans=sum;
    cout<<sum<<endl;
}

void Graph::solve1(){
    dfs(1,0);
    cout<<ans<<endl;
}