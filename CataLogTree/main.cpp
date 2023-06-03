#include"CatalogTree.cpp"
#include<bits/stdc++.h>
using namespace std;
int main()
{

        cout <<" *********************************"<<endl;
		cout <<" Virtual File System"<<endl;
		cout <<" created_time:2023.4.14"<<endl;
        cout <<" creator:yyw"<<endl;
		cout <<" *********************************"<<endl;
     ifstream fin("in0.txt");
     ofstream fout("out0.txt");
 	streambuf *cinbackup;
     streambuf *coutbackup;
 	coutbackup= cout.rdbuf(fout.rdbuf()); //用 rdbuf() 重新定向
     cinbackup= cin.rdbuf(fin.rdbuf()); //用 rdbuf() 重新定向
     CatalogTree tree;
     string p;
     while(getline(cin,p)){
     stringstream ss(p); //从流中读取每一行的命令
     string op;
     getline(ss,op,' ');
     if(op=="dir")tree.dir();
     else if(op=="cd"){
     string str;
     if(getline(ss,str))
  {
     if(str=="..")tree.cd_fa();
      else tree.cd_str(str);
  }
      else tree.cd();
  }
      else if(op=="mkdir"){
     string str;
     getline(ss,str);
     tree.mkdir(str);
  }
     else if(op=="mkfile"){
     string str;
     getline(ss,str);
     tree.mkfile(str);
  }
     else if(op=="delete"){
     string str;
     getline(ss,str);
     tree.delet(str);
  }
     else if(op=="save"){
     string str;
     getline(ss,str);
     tree.save(str);
  }
      else if(op=="load"){
     string str;
     getline(ss,str);
     tree.load(str);
  }
  else if(op=="quit"){
     cin.rdbuf(cinbackup); // 取消，恢复键盘输入
     cout.rdbuf(coutbackup); //取消，恢复屏幕输出
     cout<<"The output file has been generated"<<endl;
     return 0;
  }
  }
  return 0;
//     CatalogTree temp;
//     temp.setdir_size(100);
//     temp.mkfile_size("file1",20);
//     temp.mkfile_size("file2",11);
//     temp.remove_size("file2");
//     temp.setdir_size(10);
//    temp.mkfile_size("file1",1);
//    temp.mkdir_size("dir1",10);
//    //temp.remove_size("file1");
//    //temp.remove_size("dir1");
//    temp.cd_str("/dir1");
//    temp.cd();
//    temp.Get_size();
//   temp.dir();
//    return 0;
} 
