#include "CatalogTree.h"
#include<bits/stdc++.h>
using namespace std;
vector<string>spilt(const string&str,char c){//��cΪ�ָ�������
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
    root=new node(1,"/",0);//��Ŀ¼/
    curnode=root;
}
//�г���ǰĿ¼�µ�������Ŀ¼���ļ���
//������ɨ ������� �ļ������* Ŀ¼����
//dir��������˳�����ֵ������У�����������ļ�����������ļ�����
void CatalogTree::dir(){
    map<string,int>file_mp;//�ļ�
    map<string,int>dir_mp;//Ŀ¼
    node*now=curnode->child;
    for(;now!=NULL;now=now->brother){
        if(now->file_type==0){//��ʱ���ļ�
            string temp=now->name+"*\n";//��*�����ļ�
            file_mp[temp]=0;
        }
        else if(now->file_type){//��ʱ��Ŀ¼
            string temp=now->name+"\n";
            dir_mp[temp]=1;
        }
    }
    //�����ֵ�����������ļ���Ŀ¼
for(auto s:file_mp)cout<<s.first;
for(auto s:dir_mp)cout<<s.first;
}
//�г���ǰĿ¼�ľ���·��
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
        cd_recur(now->fa);//û�еݹ鵽root�ͼ������ϵݹ�
            if(now->fa==root){
                cout<<now->name;
            }
            else if(now->fa!=root){
                cout<<"/"<<now->name;
            }
        }
    }
//�г���ǰĿ¼�ľ���·��,��������ļ�����
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
        cd_recur2(now->fa,fout);//û�еݹ鵽root�ͼ������ϵݹ�
            if(now->fa==root){
                fout<<now->name;
            }
            else if(now->fa!=root){
                fout<<"/"<<now->name;
            }
        }
    }

//��ǰĿ¼��Ϊ����Ŀ¼
void CatalogTree::cd_fa(){
    if(curnode!=root){
        curnode=curnode->fa;
    }
    else return;
}
//��ǰĿ¼���str����ʾ·����Ŀ¼
void CatalogTree::cd_str(string str){
    //�п����Ǿ���·����Ҳ�п��������·��
   node*temp;
   if(str[0]=='/'){
    //��ʱ�Ǿ���·��
    node*t=root;//����·���Ӹ�Ŀ¼����
    vector<string>res=spilt(str,'/');
    int flag=0;
    for(int i=0;i<res.size();i++){
        string s=res[i];
        if(s!=""){//res[0]��""
            flag=0;
            for(node*now=t->child;now!=NULL;now=now->brother){
                if(now->name==s&&now->file_type==1){//��ʱ�ҵ�����һ����Ҫ�õ�Ŀ¼
                    t=now;
                    flag=1;
                    break;
                }
            }
            if(!flag){//��ʱû������Ӧ��Ŀ¼
                cout<<"not found"<<endl;
                return;
            }
        }
    }
    curnode=t;//����ǰĿ¼����Ϊ�ҵ������µķ���Ҫ���Ŀ¼
}
else if(str[0]!='/'){
    node*t=curnode;//���·���ӵ�ǰĿ¼������ʼѰ��������Ŀ¼
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
    curnode=t;//����curnodeΪ��ǰ�ҵ������µ�Ŀ¼
}
}

//�ڵ�ǰĿ¼�´���һ����Ŀ¼ ����������򲻲���
void CatalogTree::mkdir(string& str){
    node*now;
    //��Ҫ������������Ŀ¼�Ƿ��Ѿ�����
    for(now=curnode->child;now!=NULL;now=now->brother){
        if(now->name==str&&now->file_type==1)return;//��ʱ�Ѿ���������ͬ��Ŀ¼
    }
    now=new node(1,str,0);
    now->fa=curnode;//�½ڵ㸸ָ��
    now->brother=curnode->child;//ͷ�巨
    curnode->child=now;
}


//�ڵ�ǰĿ¼����һ���ļ�����������򲻲���
void CatalogTree::mkfile(string& str){
    node*now;
    for(now=curnode->child;now!=NULL;now=now->brother){
        if(now->name==str&&now->file_type==0)return;//��ʱ�Ѿ�������ͬ���������ļ�
    }
    now=new node(0,str,0);
    now->fa=curnode;
    now->brother=curnode->child;
    curnode->child=now;
}
//ɾ����ǰĿ¼������Ϊstr���ļ�����Ŀ¼�����������򲻽����κβ���
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
//ɾ��ĳ���ļ�����Ŀ¼
void CatalogTree::deletenode(node*t){
    if(t->file_type==0){//�ļ�ֱ��ɾ������
    node*father=t->fa;
    if(father->child==t){
        //��ʱҪɾ�����ļ��ǵ�һ������
        father->child=t->brother;
        delete t;
        return;
    }
    else if(father->child!=t){
        //��ʱҪɾ����Ԫ�ز��ǵ�һ������
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
            //��ʱҪɾ������һ��Ŀ¼
            if(t->child!=NULL)
         {
                while(t->child!=NULL)deletenode(t->child);//�ݹ�ɾ���������ļ�����Ŀ¼
                deletenode(t);//���ɾ������Ѿ���ɿ�Ŀ¼��Ŀ¼
         }
        else if(t->child==NULL) 
            {//��ʱ��һ����Ŀ¼
    if(t->fa->child==t){//t�ǵ�һ������
        t->fa->child=t->brother;
        delete t;
    }
            }
        else if(t->fa->child!=t){//��ʱҪɾ���Ĳ��ǵ�һ��Ŀ¼
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


//���Ӹ��ڵ㿪ʼ��Ŀ¼���ṹ���浽����Ϊstr���ı��ļ���
void CatalogTree::save(string&str){
    str=str+".txt";
    ofstream fout(str);
    //��Ŀ¼�������ļ�
    save_recur(fout,root,0);//ʹ�õݹ����洢
    //������һ��END������־
    fout<<"END"<<endl;
    fout<<"cur:";//�����ǰĿ¼�ľ���·��
    cd2(fout);//�����ǰ�ڵ�ľ���·��
}


void CatalogTree::save_recur(ofstream&fout,node*now,int depth){//��ÿһ���ļ���Ŀ¼һ��depth�������ʶ�������λ��
    if(now!=NULL){
        for(int i=0;i<=depth;i++){
            fout<<"|";//�м���'|'���Ǽ���Ŀ¼
        }
        if(now->file_type==0){//�ļ�
            fout<<now->name<<endl;
        }
        else if(now->file_type==1){//Ŀ¼
          fout<<"*"<<now->name<<endl;//Ŀ¼��Ҫ���һ���Ǻ���Ϊ��ǣ�Ȼ������ļ���
        }
        if(now->file_type==1){
            //Ŀ¼�ļ���ʱ�����ļ�
            for(auto t=now->child;t!=NULL;t=t->brother)save_recur(fout,t,depth+1);//�����䣬���++
        }
    }
}


//���ļ���Ϊstr���ı��ļ��������������Ŀ¼�����½���һ��Ŀ¼��
void CatalogTree::load(string&str){
    str=str+".txt";
    ifstream fin(str);
    string s;
    getline(fin,s);//��һ���Ǹ�Ŀ¼������
    delete root;
    root=new node(0,"/",0);
    curnode=root;//curnode�ص���Ŀ¼��
    load_recur(fin,1);
    //�������һ�У���curnode��Ŀ¼
    getline(fin,s);
    string strr=s.substr(4);//����cur:���ĸ��ַ�
    cd_str(strr);
    fin.close();
}


void CatalogTree::load_recur(ifstream &fin,int depth){ 
    string s; 
    getline(fin,s); 
    if(s!="END"){ //�����û�����ļ�ĩβ 
    int deep=0; //��¼����ʵ�����
     for (int i=0;i<s.size();i++) { 
     if(s[i]=='|')deep++; 
     else break; 
 } 
 // �õ���deep�ǵ�ǰ�ļ���Ŀ¼����� 
 //����cd_str������ʹ��curnode����depth��ȵĽڵ㣬���depth������¼�������������һ����load����Ŀ¼ʱӦ�þ��е���ȣ���������ʵ�������deep
    for(int i=deep;i<depth;i++){ 
    cd_fa(); //��ǰ�ڵ����Ÿ���ָ������,��curnode���ص���������Ŀ¼
    } 
   if(s[deep]=='*'){ 
    //Ŀ¼����
    string str=s.substr(deep+1); 
     mkdir(str); 
     cd_str(str);//��ǰĿ¼����Ϊstr
      //�����Ŀ¼�������еݹ� 
   load_recur(fin,deep+1); //deep+1 ����һ�㱾��Ӧ�õ���� ����������˵�����ݵ��˸��߲��Ŀ¼ 
 } 
    else{ //�ļ� 
       string str=s.substr(deep); 
       mkfile(str);
       load_recur(fin,deep); //��ʱ������Ҫdeep++,��Ϊ�ļ�����ͬһĿ¼��
 } 

 } 
 else return ; //����ĩβ��ֱ�ӷ��� 
}


void CatalogTree::mkfile_size(string str, ll size){
 //�ڵ�ǰĿ¼�±ߴ���һ���µ��ļ�
//�������ļ� ����Ӹ���ʼ�ж� 
          node* now = curnode->child; 
          for (now = curnode->child; now != NULL; now = now->brother) { 
 //���ֵ����������� 
          if (now->name == str && now->file_type == 0){//������ 
            cout << "existed!\n"; 
             return; 
     } 
     } 
            //�ܲ������� root ·��������Ŀ¼����� 
             if (curnode->son_used+size > curnode->all_mx) { //��ǰĿ¼�µ�������
              cout << "too large!\n"; 
            return; 
         } 
       for(now=curnode;now!=NULL;now=now->fa){ 
         if(now->pre_add_size(size)==false){ //˵�����Ŀ¼���̫�� ������Ҫ�� 
         cout << "too large!\n"; 
         return; 
         } 
   } 
               for(now=root;now!=curnode;now=now->child){ //����������Ŀ¼��������� size 
                    now->add_size(size); 
             } 
              now = new node(0, str, size); 
              now->fa = curnode; 
              now->brother = curnode->child;//����ͷ�巨
              curnode->add_size(size); 
             curnode->child = now; 
} 


void CatalogTree::mkdir_size(string str, ll size){ 
 //�ڵ�ǰĿ¼�´���һ���µ�Ŀ¼ ������ str ����� size 
              node* now = curnode->child; 
              for (now = curnode->child; now != NULL; now = now->brother) { 
 //���ֵ����������� 
            if (now->name == str && now->file_type == 1){//������ 
            cout << "existed!\n"; 
            return;
                } 
 } 
 //Ŀ¼�� size=0 ���Բ��ÿ���������� 
        for(now=curnode;now!=NULL;now=now->fa){ 
//���ȵ� fnum++; 
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
//Ϊ��ǰĿ¼�����µĺ������Ҫ�жϵ�ǰall_mx�Ƿ���µĺ�����С��������µĺ��������������������򽫺������޸ģ������ɹ�
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
//ɾ����ǰĿ¼��һ�����ļ�������Ŀ¼��Ȼ����� delete ����ɾ��������ļ��������Ŀ¼�Լ��������к��ӽڵ㼴��
          node* now = curnode->child; 
          for (now = curnode->child; now != NULL; now = now->brother) { 
 //���ֵ����������� 
        if (now->name == str ){ //���ҵ�Ҫɾ����Ŀ¼���ļ� 
          if(now->file_type==0){ //�ļ� 
            for(node * temp=curnode;temp!=NULL;temp=temp->fa){ 
 //�������Ƚڵ��ǵ�һЩ���� 
             temp->move_size(now->file_size,1); //�޸Ĵ� curnode �� root ·��������Ŀ¼���������ͺ���ļ���Ŀ
 } 
 } 
        else if(now->file_type==1){ //Ŀ¼ 
           for(node * temp=curnode;temp!=NULL;temp=temp->fa){ 
 //�������Ƚڵ��ǵ�һЩ���� 
            temp->move_size(now->son_used,now->fnum+1); //ÿ��Ŀ¼��Ҫɾ����ɾ��Ŀ¼���ļ���Ŀ�Լ������������Ŀ¼��Ŀ
 } 
 } 
          deletenode(now); 
          return ; 
 } 
 } 
        cout<<"404 not found!"<<endl; 
}
