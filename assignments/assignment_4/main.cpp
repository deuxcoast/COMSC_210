#include "stack.h"
#include "queue.h"

#include <iostream>
#include <string>

int main() {
    std::string user_string;
    std::cout << "Enter a string: ";
    std::getline(std::cin, user_string);

    MyStack stack{};
    MyQueue queue{};

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
