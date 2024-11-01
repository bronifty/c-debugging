#include <iostream>
#include "hello.h"

int main() {
    Hello<std::string> h("yes hello this is dog");
    h.sayHello();  // Outputs: Hello, World
    
    Hello<int> h2(42);
    h2.sayHello();  // Outputs: Hello, 42
    
    return 0;
}