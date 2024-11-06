#include <functional>
#include <iostream>

class Button {
    std::function<void()> onClick_;
public:
    template<typename F>
    void setHandler(F&& handler) {
        onClick_ = std::forward<F>(handler);
    }

    // Simulate button click
    void click() {
        if (onClick_) {
            onClick_();
        }
    }
};

int main() {
    // Create button
    Button btn;

    // Set up click handler with counter
    int count = 0;
    btn.setHandler([count]() mutable { 
        count++;  
        std::cout << "Clicked " << count << " times\n";
    });

    // Simulate some clicks
    btn.click();  // Outputs: Clicked 1 times
    btn.click();  // Outputs: Clicked 2 times
    btn.click();  // Outputs: Clicked 3 times

    // Create another button with different behavior
    Button btn2;
    std::string message = "Hello";
    btn2.setHandler([message]() { 
        std::cout << "Button says: " << message << "\n";
    });

    // Mix clicks between buttons
    btn.click();   // Outputs: Clicked 4 times
    btn2.click();  // Outputs: Button says: Hello
    btn.click();   // Outputs: Clicked 5 times

    return 0;
} 