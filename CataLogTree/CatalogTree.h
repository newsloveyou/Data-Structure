#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node{
   node*fa;//父节点指针
   node*child;//第一个儿子节点指针
   node*brother;//兄弟节点指针
   string name;//文件或者目录名字
   int file_type;//文件还是目录，0是文件，1是目录
   ll fnum;//子文件的数目
   ll file_size;//该文件大小
   ll all_mx;//目录配额和文件配额
   ll son_used;//所有的孩子占的大小
   node(int type,string fname,ll size){
    fa=NULL;
    child=NULL;
    brother=NULL;
    name=fname;
    file_type=type;
    file_size=size;
    fnum=0;
    all_mx=0;
    son_used=0;
   }
   bool pre_add_size(ll size){//预分配文件
    if(all_mx&&son_used+size>all_mx)return false;
    return true;
   }
   void add_size(ll size){
    son_used+=size;
    fnum++;
   }
   void move_size(ll size,ll cnt){
    //size是要删除的配额，cnt是要删除的文件数
       son_used-=size;
       fnum-=cnt;
   }
   void get_size(){
    if(!file_type)cout<<"File size:"<<file_size<<endl;
    else cout<<"Directory Quota Size:"<<all_mx<<" used: "<<son_used<<endl;
   }
   bool set_size(ll all){//分配一个配额，只对目录有用
    if(all<son_used)return false;
    return true;
   }
};
class CatalogTree{
    private:
     node*root;
     node*curnode;//当前目录
     public:
     CatalogTree();
     ~CatalogTree(){delete root;}
     void dir();//列出当前目录的所有子目录和文件
     void cd_recur(node* now);//cd()调用的递归函数
     void cd();//列出当前目录的绝对路径
     void cd_fa();//当前目录变为父亲目录
     void cd_str(string str);//当前目录设为str
     void mkdir(string&str);//在当前目录下创建一个子目录
     void mkfile(string& str);//在当前目录创建一个文件
     void deletenode(node*now);//删除一个节点和他的所有子节点
     void delet(string& str);//删除当前目录名为str的文件或子目录
    void save(string&str);//将从根节点开始的目录树结构保存到文件中
    void save_recur(ofstream& fout,node*now,int depth);
    void load(string&str);//打开文件
    void load_recur(ifstream&fin,int depth);

    void cd2(ofstream&out);
    void cd_recur2(node*now,ofstream&fout);
    void mkfile_size(string str,ll size);
    void mkdir_size(string str,ll size);
    void setdir_size(ll all_mx);//给当前原有的目录文件配置配额
    void remove_size(string str);//删除文件或者目录

    void cd_root(){curnode=root;}//回到root
    void Get_size(){curnode->get_size();}//获取当前目录的配额

};
