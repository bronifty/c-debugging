#include <iostream>
#include <string>

class Person {
public:
    Person(std::string name, int age) : name_(std::move(name)), age_(age) {}

    // Function that takes a reference parameter
    void incrementAge(int& yearsToAdd) {
        age_ += yearsToAdd;
        yearsToAdd = 0;  // This change will be visible to the caller
    }

    // Function that returns a reference
    std::string& getName() {
        return name_;  // Returns a reference to name_
    }

    void printDetails() const {
        std::cout << "Name: " << name_ << ", Age: " << age_ << std::endl;
    }

private:
    std::string name_;
    int age_;
};

int main() {
    Person person("Alice", 30);
    
    // Demonstrating pass by reference
    int years = 5;
    std::cout << "Before incrementAge: years = " << years << std::endl;
    person.incrementAge(years);
    std::cout << "After incrementAge: years = " << years << std::endl;
    person.printDetails();

    // Demonstrating returning a reference
    std::cout << "\nBefore modifying name: ";
    person.printDetails();
    
    person.getName() = "Alicia";  // Directly modifies the name_ member
    
    std::cout << "After modifying name: ";
    person.printDetails();

    return 0;
}