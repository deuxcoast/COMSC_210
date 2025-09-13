#include <iostream>
#include <string>

class MyStack {
   private:
    char* list;
    short top;
    unsigned short max;

   public:
    MyStack(unsigned short s) : list{new char[s]}, top{-1}, max{s} {}

    ~MyStack() { delete[] list; }

    short push(char a) {
        if (top < (max - 1)) {
            top = top + 1;
            list[top] = a;
            return 0;
        }

        return -1;
    }

    short pop() {
        if (top > -1) {
            top = top - 1;
            return 0;
        }
        return -1;
    }

    char peek() const {
        if (top > -1) {
            return list[top];
        }
        return '\0';
    }
};

class MyQueue {
   private:
    char* list;
    unsigned short front;
    unsigned short back;
    unsigned short max;

   public:
    MyQueue(unsigned short s) : list{new char[s]}, front{0}, back{0}, max{s} {}

    ~MyQueue() { delete[] list; }

    short enqueue(char a) {
        if (front != (back + 1) % max) {
            list[back] = a;
            back = (back + 1) % max;
            return 0;
        }
        return -1;
    }

    short dequeue() {
        if (front != back) {
            front = (front + 1) % max;
            return 0;
        }
        return -1;
    }

    char first() const {
        if (front != back) {
            return list[front];
        }
        return '\0';
    }
};

int main() {
    std::string user_string;
    std::cout << "Enter a string: ";
    std::getline(std::cin, user_string);

    MyStack stack{static_cast<unsigned short>(user_string.size())};

    // we will always have an empty element in the queue, so the size should
    // account for that
    MyQueue queue{static_cast<unsigned short>(user_string.size() + 1)};

    for (size_t i{0}; i < user_string.size(); i++) {
        stack.push(user_string.at(i));
        queue.enqueue(user_string.at(i));
    }

    std::cout << "\n\nQueue contents: ";

    while (queue.first() != '\0') {
        std::cout << queue.first();
        queue.dequeue();
    }

    std::cout << "\n\nStack contents: ";

    while (stack.peek() != '\0') {
        std::cout << stack.peek();
        stack.pop();
    }

    std::cout << "\n\nGoodbye!";

    return 0;
}
