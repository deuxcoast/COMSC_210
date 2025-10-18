#include <new>

class MyStack {
   private:
    struct Node {
        char c;
        Node* next;
    };

    Node* top;

   public:
    // initializes top to nullptr
    MyStack() { top = nullptr; }
    ~MyStack() {
        // free all allocated memory
        Node* curr{nullptr};
        while (top != nullptr) {
            curr = top;
            top = top->next;
            delete curr;
        }
    }

    short push(char a) {
        Node* n = new (std::nothrow) Node;
        if (n == nullptr) {
            return -1;
        }
        n->c = a;
        n->next = nullptr;

        n->next = top;
        top = n;

        return 0;
    }

    short pop() {
        if (top != nullptr) {
            Node* p = top;
            top = top->next;
            delete p;

            return 0;
        }
        return -1;
    }

    char peek() {
        if (top != nullptr) {
            return top->c;
        }
        return '\0';
    }
};
