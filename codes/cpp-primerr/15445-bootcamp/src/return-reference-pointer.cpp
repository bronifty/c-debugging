#include <iostream>
#include <string>

class Person {
public:
    Person(std::string name, int age) : name_(std::move(name)), age_(age) {}

    Person& returnReference() {
        std::cout << "Returning *this (reference)\n";
        return *this;
    }

    Person* returnPointer() {
        std::cout << "Returning this (pointer)\n";
        return this;
    }

    void printDetails() const {
        std::cout << "Name: " << name_ << ", Age: " << age_ << std::endl;
    }

private:
    std::string name_;
    int age_;
};

int main() {
    Person alice("Alice", 30);

    std::cout << "Original Alice:\n";
    alice.printDetails();

    std::cout << "\nUsing returnReference():\n";
    Person& aliceRef = alice.returnReference();
    std::cout << "Address of alice: " << &alice << std::endl;
    std::cout << "Address of aliceRef: " << &aliceRef << std::endl;

    std::cout << "\nUsing returnPointer():\n";
    Person* alicePtr = alice.returnPointer();
    std::cout << "Address of alice: " << &alice << std::endl;
    std::cout << "Value of alicePtr (address it points to): " << alicePtr << std::endl;
    std::cout << "Address of alicePtr itself: " << &alicePtr << std::endl;

    return 0;
}