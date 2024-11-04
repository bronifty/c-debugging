#include <iostream>
#include <stack>
#include <string>

template <typename T>
class Queue {
private:
    std::stack<T> stack1;    // for enqueue
    std::stack<T> stack2;    // for dequeue
    
public:
    void enqueue(T value) {
        stack1.push(value);
    }
    
    T dequeue() {
        if (stack2.empty()) {
            // Transfer elements from stack1 to stack2
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        
        if (stack2.empty()) {
            throw std::runtime_error("Queue is empty");
        }
        
        T value = stack2.top();
        stack2.pop();
        return value;
    }
    
    bool empty() const {
        return stack1.empty() && stack2.empty();
    }
    
    size_t size() const {
        return stack1.size() + stack2.size();
    }
};

int main() {
    // Test with integers
    Queue<int> intQueue;
    std::cout << "Testing integer queue:\n";
    
    // Enqueue some numbers
    intQueue.enqueue(1);
    intQueue.enqueue(2);
    intQueue.enqueue(3);
    
    std::cout << "Queue size: " << intQueue.size() << "\n";
    
    // Dequeue and print
    while (!intQueue.empty()) {
        std::cout << "Dequeued: " << intQueue.dequeue() << "\n";
    }
    
    // Test with strings
    Queue<std::string> stringQueue;
    std::cout << "\nTesting string queue:\n";
    
    stringQueue.enqueue("First");
    stringQueue.enqueue("Second");
    stringQueue.enqueue("Third");
    
    std::cout << "Queue size: " << stringQueue.size() << "\n";
    
    // Mix operations
    std::cout << "Dequeued: " << stringQueue.dequeue() << "\n";
    stringQueue.enqueue("Fourth");
    
    // Dequeue remaining items
    while (!stringQueue.empty()) {
        std::cout << "Dequeued: " << stringQueue.dequeue() << "\n";
    }
    
    try {
        // This should throw an exception
        stringQueue.dequeue();
    } catch (const std::runtime_error& e) {
        std::cout << "\nCaught exception: " << e.what() << "\n";
    }
    
    return 0;
} 