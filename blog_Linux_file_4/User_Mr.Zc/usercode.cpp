#include <iostream>
#include "libmyc.h"
#include "MyString.h"

int main() {
    char myStr[] = "Hello Linux, Hello C++!";
    size_t len = MyStrlen(myStr); 
    std::cout << "String: " << myStr << ", Length: " << len << std::endl;

    MyFILE* fp = Fopen("zc_test.txt", "w");
    if (fp == NULL) {
        return -1;
    }

    const char* msg1 = "Buffer test without newline. ";
    Fwrite(fp, MyStrlen((char*)msg1), msg1);

    const char* msg2 = "Trigger line flush!\n";
    Fwrite(fp, MyStrlen((char*)msg2), msg2);

    const char* msg3 = "This line relies on Fclose to flush.";
    Fwrite(fp, MyStrlen((char*)msg3), msg3);

    Fclose(fp);

    return 0;
}
