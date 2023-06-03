#include "CatalogTree.h"
#include<bits/stdc++.h>
using namespace std;
vector<string>spilt(const string&str,char c){//以c为分隔符读入
    string s;
    stringstream ss(str);
    vector<string>res;
    while(getline(ss,s,c)){
        res.push_back(s);
    }
    return res;
}
CatalogTree::CatalogTree(){
    //delete root;
    root=new node(1,"/",0);//根目录/
    curnode=root;
}
//列出当前目录下的所有子目录与文件项
//从左到右扫 输出换行 文件后面加* 目录不加
//dir命令的输出顺序按照字典序排列，先输出所有文件再输出所有文件名。
void CatalogTree::dir(){
    map<string,int>file_mp;//文件
    map<string,int>dir_mp;//目录
    node*now=curnode->child;
    for(;now!=NULL;now=now->brother){
        if(now->file_type==0){//此时是文件
            string temp=now->name+"*\n";//加*代表文件
            file_mp[temp]=0;
        }
        else if(now->file_type){//此时是目录
            string temp=now->name+"\n";
            dir_mp[temp]=1;
        }
    }
    //按照字典序依次输出文件和目录
for(auto s:file_mp)cout<<s.first;
for(auto s:dir_mp)cout<<s.first;
}
//列出当前目录的绝对路径
void CatalogTree::cd(){
    cd_recur(curnode);
    cout<<endl;
}
void CatalogTree::cd_recur(node* now){
    if(now==root){
        cout<<"/";
        return ;
    }
    else if(now!=root){
        cd_recur(now->fa);//没有递归到root就继续向上递归
            if(now->fa==root){
                cout<<now->name;
            }
            else if(now->fa!=root){
                cout<<"/"<<now->name;
            }
        }
    }
//列出当前目录的绝对路径,并输出到文件当中
void CatalogTree::cd2(ofstream&fout){
    cd_recur2(curnode,fout);
    fout<<endl;
}
void CatalogTree::cd_recur2(node* now,ofstream&fout){
    if(now==root){
        fout<<"/";
        return ;
    }
    else if(now!=root){
        cd_recur2(now->fa,fout);//没有递归到root就继续向上递归
            if(now->fa==root){
                fout<<now->name;
            }
            else if(now->fa!=root){
                fout<<"/"<<now->name;
            }
        }
    }

//当前目录变为父亲目录
void CatalogTree::cd_fa(){
    if(curnode!=root){
        curnode=curnode->fa;
    }
    else return;
}
//当前目录变成str所表示路径的目录
void CatalogTree::cd_str(string str){
    //有可能是绝对路径，也有可能是相对路径
   node*temp;
   if(str[0]=='/'){
    //此时是绝对路径
    node*t=root;//绝对路径从根目录出发
    vector<string>res=spilt(str,'/');
    int flag=0;
    for(int i=0;i<res.size();i++){
        string s=res[i];
        if(s!=""){//res[0]是""
            flag=0;
            for(node*now=t->child;now!=NULL;now=now->brother){
                if(now->name==s&&now->file_type==1){//此时找到了这一层上要用的目录
                    t=now;
                    flag=1;
                    break;
                }
            }
            if(!flag){//此时没有找响应的目录
                cout<<"not found"<<endl;
                return;
            }
        }
    }
    curnode=t;//将当前目录更新为找到的最新的符合要求的目录
}
else if(str[0]!='/'){
    node*t=curnode;//相对路径从当前目录出发开始寻找它的子目录
    vector<string>res=spilt(str,'/');
    int flag=0;
    for(int i=0;i<res.size();i++){
        string s=res[i];
        if(s!=""){
            flag=0;
            for(node*now=t->child;now!=NULL;now=now->brother){
                if(now->name==s&&now->file_type==1){
                    t=now;
                    flag=1;
                    break;
                }
            }
            if(!flag){
                cout<<"not found"<<endl;
                return ;
            }

        }
    }
    curnode=t;//更新curnode为当前找到的最新的目录
}
}

//在当前目录下创建一个子目录 ，如果存在则不操作
void CatalogTree::mkdir(string& str){
    node*now;
    //先要看看创建的子目录是否已经存在
    for(now=curnode->child;now!=NULL;now=now->brother){
        if(now->name==str&&now->file_type==1)return;//此时已经存在着相同的目录
    }
    now=new node(1,str,0);
    now->fa=curnode;//新节点父指针
    now->brother=curnode->child;//头插法
    curnode->child=now;
}


//在当前目录创建一个文件，如果存在则不操作
void CatalogTree::mkfile(string& str){
    node*now;
    for(now=curnode->child;now!=NULL;now=now->brother){
        if(now->name==str&&now->file_type==0)return;//此时已经存在相同类型名的文件
    }
    now=new node(0,str,0);
    now->fa=curnode;
    now->brother=curnode->child;
    curnode->child=now;
}
//删除当前目录中名字为str的文件或子目录，若不存在则不进行任何操作
void CatalogTree::delet(string& str){
    node*now;
    for(now=curnode->child;now!=NULL;now=now->brother){
        if(now->name==str){
            deletenode(now);
            return ;
        }
    }
    return ;
}
//删除某个文件或者目录
void CatalogTree::deletenode(node*t){
    if(t->file_type==0){//文件直接删除即可
    node*father=t->fa;
    if(father->child==t){
        //此时要删除的文件是第一个孩子
        father->child=t->brother;
        delete t;
        return;
    }
    else if(father->child!=t){
        //此时要删除的元素不是第一个孩子
        for(node*now=father->child;now!=NULL;now=now->brother){
            if(now->brother==t){
                now->brother=t->brother;
                delete t;
                return ;
            }
        }
    }
    }
 else if(t->file_type==1){
            //此时要删除的是一个目录
            if(t->child!=NULL)
         {
                while(t->child!=NULL)deletenode(t->child);//递归删除它的子文件和子目录
                deletenode(t);//最后删除这个已经变成空目录的目录
         }
        else if(t->child==NULL) 
            {//此时是一个空目录
    if(t->fa->child==t){//t是第一个孩子
        t->fa->child=t->brother;
        delete t;
    }
            }
        else if(t->fa->child!=t){//此时要删除的不是第一个目录
    for(node*now=t->fa->child;now!=NULL;now=now->brother){
    if(now->brother==t){
        now->brother=t->brother;
         delete t;
         break;
    }
     }
    //delete t;
    }
}
}


//将从根节点开始的目录树结构保存到名字为str的文本文件中
void CatalogTree::save(string&str){
    str=str+".txt";
    ofstream fout(str);
    //把目录树存入文件
    save_recur(fout,root,0);//使用递归来存储
    //最后插入一个END结束标志
    fout<<"END"<<endl;
    fout<<"cur:";//输出当前目录的绝对路径
    cd2(fout);//输出当前节点的绝对路径
}


void CatalogTree::save_recur(ofstream&fout,node*now,int depth){//给每一个文件或目录一个depth深度来标识它的相对位置
    if(now!=NULL){
        for(int i=0;i<=depth;i++){
            fout<<"|";//有几个'|'就是几级目录
        }
        if(now->file_type==0){//文件
            fout<<now->name<<endl;
        }
        else if(now->file_type==1){//目录
          fout<<"*"<<now->name<<endl;//目录需要输出一个星号作为标记，然后输出文件名
        }
        if(now->file_type==1){
            //目录文件此时有子文件
            for(auto t=now->child;t!=NULL;t=t->brother)save_recur(fout,t,depth+1);//根不变，深度++
        }
    }
}


//打开文件名为str的文本文件，并根据里面的目录树重新建立一个目录树
void CatalogTree::load(string&str){
    str=str+".txt";
    ifstream fin(str);
    string s;
    getline(fin,s);//第一行是根目录的名字
    delete root;
    root=new node(0,"/",0);
    curnode=root;//curnode回到根目录下
    load_recur(fin,1);
    //读入最后一行，是curnode的目录
    getline(fin,s);
    string strr=s.substr(4);//忽略cur:这四个字符
    cd_str(strr);
    fin.close();
}


void CatalogTree::load_recur(ifstream &fin,int depth){ 
    string s; 
    getline(fin,s); 
    if(s!="END"){ //如果还没读到文件末尾 
    int deep=0; //记录它的实际深度
     for (int i=0;i<s.size();i++) { 
     if(s[i]=='|')deep++; 
     else break; 
 } 
 // 得到的deep是当前文件或目录的深度 
 //由于cd_str函数会使得curnode到达depth深度的节点，因此depth变量记录的是它如果是上一个被load的子目录时应该具有的深度，但是它的实际深度是deep
    for(int i=deep;i<depth;i++){ 
    cd_fa(); //当前节点沿着父亲指针上升,将curnode返回到它本来的目录
    } 
   if(s[deep]=='*'){ 
    //目录名字
    string str=s.substr(deep+1); 
     mkdir(str); 
     cd_str(str);//当前目录设置为str
      //进入该目录继续进行递归 
   load_recur(fin,deep+1); //deep+1 是下一层本来应该的深度 但如果变短了说明回溯到了更高层的目录 
 } 
    else{ //文件 
       string str=s.substr(deep); 
       mkfile(str);
       load_recur(fin,deep); //此时并不需要deep++,因为文件是在同一目录中
 } 

 } 
 else return ; //读到末尾就直接返回 
}


void CatalogTree::mkfile_size(string str, ll size){
 //在当前目录下边创建一个新的文件
//带配额的文件 必须从根开始判断 
          node* now = curnode->child; 
          for (now = curnode->child; now != NULL; now = now->brother) { 
 //在兄弟链表上搜索 
          if (now->name == str && now->file_type == 0){//重名了 
            cout << "existed!\n"; 
             return; 
     } 
     } 
            //能不能满足 root 路径上所有目录的配额 
             if (curnode->son_used+size > curnode->all_mx) { //当前目录下的配额不满足
              cout << "too large!\n"; 
            return; 
         } 
       for(now=curnode;now!=NULL;now=now->fa){ 
         if(now->pre_add_size(size)==false){ //说明这个目录配额太少 不符合要求 
         cout << "too large!\n"; 
         return; 
         } 
   } 
               for(now=root;now!=curnode;now=now->child){ //给所有祖先目录加入了这个 size 
                    now->add_size(size); 
             } 
              now = new node(0, str, size); 
              now->fa = curnode; 
              now->brother = curnode->child;//还是头插法
              curnode->add_size(size); 
             curnode->child = now; 
} 


void CatalogTree::mkdir_size(string str, ll size){ 
 //在当前目录下创建一个新的目录 名字是 str 配额是 size 
              node* now = curnode->child; 
              for (now = curnode->child; now != NULL; now = now->brother) { 
 //在兄弟链表上搜索 
            if (now->name == str && now->file_type == 1){//重名了 
            cout << "existed!\n"; 
            return;
                } 
 } 
 //目录的 size=0 所以不用考虑配额问题 
        for(now=curnode;now!=NULL;now=now->fa){ 
//祖先的 fnum++; 
          now->add_size(0); 
 } 
            now = new node(1,str,0); 
            now->fa=curnode; 
            now->brother=curnode->child; 
            curnode->child=now; 
            now->file_size=0; 
            now->all_mx=size; 
} 

void CatalogTree::setdir_size(ll all_mx){ 
//为当前目录设置新的后代配额，需要判断当前all_mx是否比新的后代配额小，如果比新的后代配额大，则放弃操作，否则将后代配额修改，操作成功
       if (curnode->file_type != 1) { 
            cout << "only!\n"; 
               return; 
            } 
     if (curnode->son_used > all_mx) { 
           cout << "too small \n"; 
            return; 
           } 
         curnode->all_mx = all_mx; 
         cout << "successfully setting!\n"; 
        return; 
} 

void CatalogTree::remove_size(string str){ 
//删除当前目录的一个子文件或者子目录，然后调用 delete 函数删除这个子文件或这个子目录以及它的所有孩子节点即可
          node* now = curnode->child; 
          for (now = curnode->child; now != NULL; now = now->brother) { 
 //在兄弟链表上搜索 
        if (now->name == str ){ //先找到要删除的目录或文件 
          if(now->file_type==0){ //文件 
            for(node * temp=curnode;temp!=NULL;temp=temp->fa){ 
 //更改祖先节点们的一些参数 
             temp->move_size(now->file_size,1); //修改从 curnode 到 root 路径上所有目录的已用配额和后代文件数目
 } 
 } 
        else if(now->file_type==1){ //目录 
           for(node * temp=curnode;temp!=NULL;temp=temp->fa){ 
 //更改祖先节点们的一些参数 
            temp->move_size(now->son_used,now->fnum+1); //每个目录需要删除被删除目录的文件数目以及包括其自身的目录数目
 } 
 } 
          deletenode(now); 
          return ; 
 } 
 } 
        cout<<"404 not found!"<<endl; 
}
