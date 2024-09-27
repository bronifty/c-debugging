#include <iostream>
#include <utility>

void process(int& x) { std::cout << "lvalue\n"; }
void process(int&& x) { std::cout << "rvalue\n"; }

template<typename T>
void perfect_forward(T&& x) {
    process(std::forward<T>(x));
}

template<typename T>
void imperfect_forward(T&& x) {
    process(x);  // Always treats x as an lvalue
}

int main() {
    int a = 5;
    
    perfect_forward(a);        // Prints: lvalue
    perfect_forward(10);       // Prints: rvalue
    
    imperfect_forward(a);      // Prints: lvalue
    imperfect_forward(10);     // Prints: lvalue (incorrect!)
}