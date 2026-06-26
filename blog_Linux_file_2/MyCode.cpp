#include"MyGlibc.h"
void func()
{
	MyFILE* mf = Fopen("Test.txt","w");
	char* msg = "aabbccddeeffgg";
	Fwrite(mf,strlen(msg),msg);
	Fflush(mf);
	Fclose(mf);
}
int main()
{
	func();
	return 0;
}

