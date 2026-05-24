#include <iostream>
#include <unistd.h>
void func01()
{
//状态测试：暂停，运行，后台运行
    while (true) {
        std::cout << "我是一个进程。我的pid是: " << getpid() << std::endl;
        sleep(1);
    }
}
void func02()
{
//状态测试：阻塞
	int num =0;
	std::cin>> num ;
}
int main() 
{
	//func01();
	func02();

    return 0;
}
