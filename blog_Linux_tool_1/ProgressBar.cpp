#include"ProgressBar.h"

int main()
{
	char arr[NUM];
	memset(arr, 0, sizeof(arr));
	const int DownLoad = 1024;//需要下载的数量
	const double Speed = 1.00;//固定网速
	int current = 0;//当前下载的数量
	while (current <= DownLoad )
	{
		progress(arr,current,DownLoad);//调用进度条，传递当前下载数量和整个安装包的大小
		current++;
		Sleep(1);
	}
	cout << endl;
	cout << "DownLoad Complate!" << endl;
	return 0;
}