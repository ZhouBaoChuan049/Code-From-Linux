#include"ProgressBar.h"

void progress(char* arr,int cur, int load)
{
	//我们首先要知道，我们的下载进行占比，确定出：我们要在哪里加一个#
	const int cnt = (cur*100 / load);
	char pointer[5] = "|-/\\";
	printf("[%-100s][%d%%][%c]\r", arr, cnt,pointer[cnt%5]);
	arr[cnt] = BAR;
}
