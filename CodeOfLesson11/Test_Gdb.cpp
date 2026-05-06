#include <iostream>

int func(int a, int b) {
    int result = 0;
    int flag = 1;
    
    for (int i = 0; i < 5; ++i) {
        int step_sum = a + b + i;
        result += step_sum;
    }
    
    result *= flag;
    return result;
}

int main() {
    int x = 10;
    int y = 20;

    int final_result = func(x, y);

    std::cout << "The final result is: " << final_result << std::endl;

    return 0;
}
