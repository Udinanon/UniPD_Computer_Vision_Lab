#include <iostream>

int main(){
    auto result = (10 <=> 20) > 0;
    std::cout << "Hello World!" << std::endl;
    std::cout << result << std::endl;
    return 0;
}