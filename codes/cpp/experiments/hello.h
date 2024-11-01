#ifndef HELLO_H
#define HELLO_H

template<typename T>
class Hello {
public:
    Hello(T message);
    void sayHello();
private:
    T message_;
};

// For templates, we typically need to include the implementation in the header
// file or a separate .tpp file that's included at the end of the header.
// This is because templates need to be available at compile time.
template<typename T>
Hello<T>::Hello(T message) : message_(message) {}

template<typename T>
void Hello<T>::sayHello() {
    std::cout << "Hello, " << message_ << std::endl;
}

#endif