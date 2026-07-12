#include"string.h"
size_t MyStrlen(char* str)
{
	int count = 0;
	for(int i =0;str[i];i++)
		count++;
	return count;
}


