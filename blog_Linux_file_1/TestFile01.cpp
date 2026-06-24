#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

//enum class OPTION : int {
//	FLAG_ONE = 1<<0,
//	FLAG_TWO = 1<<1,
//	FLAG_THREE = 1<<2
//};
enum OPTION {
    FLAG_ONE   = 1 << 0, 
    FLAG_TWO   = 1 << 1, 
    FLAG_THREE = 1 << 2  
};
//为什么这样不行？

void Func(int flag)
{
	if(flag & OPTION::FLAG_ONE)
		cout<<"function one";	
	if(flag & OPTION::FLAG_TWO)
		cout<<"function two";
	if(flag & OPTION::FLAG_THREE)
		cout<<"function three";
}

int main()
{
	Func(OPTION::FLAG_ONE);
	cout<<endl;
	Func(OPTION::FLAG_ONE|OPTION::FLAG_TWO);
	cout<<endl;
	Func(OPTION::FLAG_ONE|OPTION::FLAG_TWO|OPTION::FLAG_THREE);
	cout<<endl;
	return 0;
}


