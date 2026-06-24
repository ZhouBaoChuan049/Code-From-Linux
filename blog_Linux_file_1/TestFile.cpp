#include<iostream>
using namespace std;
#include<cstring>
const int MAX_SIZE = 100;
void FileTest01()
{
	//打开一个文件，然后构建一些字符串然后写入
	FILE* fd = fopen("test.txt","w");
	if(fd ==NULL) {perror("fopen");}
	char arr[MAX_SIZE] ={0};
	int cnt =5 ;
	while(cnt-- > 0)
		snprintf(arr+strlen(arr),sizeof(arr),"hellobit");
	fwrite(arr,sizeof(arr[0]),sizeof(arr)/sizeof(arr[0]),fd);
	fclose(fd);
}

void FileTest02(int _argc,char* _argv[])
{
const size_t MAX_SIZE = 128;
	if(_argc != 2)
	{
		cout<<"cat 打印文件内容必须是两个参数"<<endl;
		exit(1);
	}
	else 
	{
		FILE* fd = fopen(_argv[1],"r");
		if(fd == NULL)
			perror("fopen");
		while(1)
		{
			char buffer[MAX_SIZE] = {0};
			int n = fread(buffer , 1 , sizeof(buffer)-1,fd);
			if(n > 0)
			{
				buffer[n] = 0;
				fwrite(buffer,sizeof(buffer[0]),sizeof(buffer)/sizeof(buffer[0]),stdout);
			}
			if(feof(fd))
				break;
		}
		fclose(fd);
	}
	return ;
}


int main(int argc,char* argv[])
{	
	//FileTest01();
	FileTest02(argc,argv);
	return 0;
}

