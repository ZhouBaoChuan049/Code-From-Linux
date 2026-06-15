#include<iostream>
using namespace std;
int main(){
	extern char** environ;
	for(int i =0;environ[i];i++)
		cout<<environ[i];
	return 0;
}

