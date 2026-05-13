#include<iostream>
using namespace std;
void Test01(int _argc,char* _argv[])
{
	for(int i =0 ;i < _argc ; i++)
	{
		cout<<_argv[i]<<endl;
	}
}
void Test02(int _argc,char* _argv[])
{
	//不同的功能是怎么通过命令行实现的
	if(_argc!=2)
		cout<<"输入错误!请重新输入"<<endl;
	else
	{
		string cmd = _argv[1];
        	if (cmd == "a")
            		cout << "执行一号功能" << endl;
        	if (cmd == "b")
            		cout << "执行二号功能" << endl;
        	if (cmd == "c")
            		cout << "执行三号功能" << endl;
	}
}
int main(int argc,char* argv[])
{
	//Test01(argc,argv);
	Test02(argc,argv);
	return 0;
}
