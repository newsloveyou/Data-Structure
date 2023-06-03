#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node{
   node*fa;//���ڵ�ָ��
   node*child;//��һ�����ӽڵ�ָ��
   node*brother;//�ֵܽڵ�ָ��
   string name;//�ļ�����Ŀ¼����
   int file_type;//�ļ�����Ŀ¼��0���ļ���1��Ŀ¼
   ll fnum;//���ļ�����Ŀ
   ll file_size;//���ļ���С
   ll all_mx;//Ŀ¼�����ļ����
   ll son_used;//���еĺ���ռ�Ĵ�С
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
   bool pre_add_size(ll size){//Ԥ�����ļ�
    if(all_mx&&son_used+size>all_mx)return false;
    return true;
   }
   void add_size(ll size){
    son_used+=size;
    fnum++;
   }
   void move_size(ll size,ll cnt){
    //size��Ҫɾ������cnt��Ҫɾ�����ļ���
       son_used-=size;
       fnum-=cnt;
   }
   void get_size(){
    if(!file_type)cout<<"File size:"<<file_size<<endl;
    else cout<<"Directory Quota Size:"<<all_mx<<" used: "<<son_used<<endl;
   }
   bool set_size(ll all){//����һ����ֻ��Ŀ¼����
    if(all<son_used)return false;
    return true;
   }
};
class CatalogTree{
    private:
     node*root;
     node*curnode;//��ǰĿ¼
     public:
     CatalogTree();
     ~CatalogTree(){delete root;}
     void dir();//�г���ǰĿ¼��������Ŀ¼���ļ�
     void cd_recur(node* now);//cd()���õĵݹ麯��
     void cd();//�г���ǰĿ¼�ľ���·��
     void cd_fa();//��ǰĿ¼��Ϊ����Ŀ¼
     void cd_str(string str);//��ǰĿ¼��Ϊstr
     void mkdir(string&str);//�ڵ�ǰĿ¼�´���һ����Ŀ¼
     void mkfile(string& str);//�ڵ�ǰĿ¼����һ���ļ�
     void deletenode(node*now);//ɾ��һ���ڵ�����������ӽڵ�
     void delet(string& str);//ɾ����ǰĿ¼��Ϊstr���ļ�����Ŀ¼
    void save(string&str);//���Ӹ��ڵ㿪ʼ��Ŀ¼���ṹ���浽�ļ���
    void save_recur(ofstream& fout,node*now,int depth);
    void load(string&str);//���ļ�
    void load_recur(ifstream&fin,int depth);

    void cd2(ofstream&out);
    void cd_recur2(node*now,ofstream&fout);
    void mkfile_size(string str,ll size);
    void mkdir_size(string str,ll size);
    void setdir_size(ll all_mx);//����ǰԭ�е�Ŀ¼�ļ��������
    void remove_size(string str);//ɾ���ļ�����Ŀ¼

    void cd_root(){curnode=root;}//�ص�root
    void Get_size(){curnode->get_size();}//��ȡ��ǰĿ¼�����

};
