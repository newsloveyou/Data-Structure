#include "skiplist.cpp"
#include <ostream>
#include<fstream>
int main()
{
    cout<<"欢迎使用跳表"<<endl;
    cout<<"创作者"<<"yyw"<<endl;
    cout<<"创作时间"<<"2023-3-10"<<endl;
    cout<<endl;
    cout<<"首先从文件中读入                     "<<endl;
    int n,m;
	ifstream fin("input7.txt");
    ofstream fout("output7.txt");
	streambuf *cinbackup;
    streambuf *coutbackup; 
	coutbackup= cout.rdbuf(fout.rdbuf()); //用 rdbuf() 重新定向
    cinbackup= cin.rdbuf(fin.rdbuf()); //用 rdbuf() 重新定向
	skipList<int, int>a(1e+9, 10000);
	cin>>n>>m;
		for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        a.insert1({ x,1 });
    }
    while (n--) {
        int flag = 0; cin >> flag;
        if (flag == 1) {
            int k;
            cin >> k;
            a.find(k);
        }
        if (flag == 2) {
            int k;
             cin >> k;
            a.insert({ k,1 });
        }
        if (flag == 3) {
            int k;
             cin >> k;
            a.erase(k);
        }
        if (flag == 4) {
            a.min();
        }
        if (flag == 5)a.max();
        if (flag == 6)a.resize();
        if (flag == 7) {
           // a.output();
            cout<<a.getsize();
        }
    }
    cin.rdbuf(cinbackup); // 取消，恢复键盘输入
    cout.rdbuf(coutbackup); //取消，恢复屏幕输出
    a.output();
    cout<<endl;
    cout<<"手动输入数据                         "<<endl;
   cin>>n>>m;
   cout<<"请插入元素"<<endl;
		for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        a.insert1({ x,1 });
    }
    while (n--) {
        int flag = 0; cin >> flag;
        if (flag == 1) {
            int k;
            cout<<"请输入需要查找的元素"<<endl;
            cin >> k;
            a.find(k);
        }
        if (flag == 2) {
            int k;
             cout<<"请输入需要插入的元素"<<endl;
             cin >> k;
            a.insert({ k,1 });
        }
        if (flag == 3) {
            int k;
            cout<<"请输入需要删除的元素"<<endl; 
            cin >> k;
            a.erase(k);
        }
        if (flag == 4) {
            cout<<"最小元素是";
            a.min();
        }
        if (flag == 5){
            cout<<"最大元素是";
            a.max();
        }
        if (flag == 6){
            cout<<"可能整理成功"<<endl;
            a.resize();
            //a.output();
        }
        if(flag==7){
            cout<<"查看各个操作的次数"<<endl;
            a.output();
        }
        
    }
     cout<<"谢谢您的使用                        "<<endl;
}



