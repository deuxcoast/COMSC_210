#include <new>
class MyQueue {
   private:
    struct Node {
        char c;
        Node* next;
    };

    Node* front;
    Node* back;

   public:
    // initializes front and back to nullptr
    MyQueue() {
        front = nullptr;
        back = nullptr;
    }
    ~MyQueue() {
        // free all allocated memory
        Node* curr{nullptr};
        while (front != nullptr) {
            curr = front;
            front = front->next;
            delete curr;
        }
    }

    short enqueue(char a) {
        Node* n = new (std::nothrow) Node;
        if (n == nullptr) {
            return -1;
        }
        n->c = a;
        n->next = nullptr;

        // if the queue is empty make front and back point to n
        if (front == nullptr) {
            front = n;
            back = n;
            return 0;
        } else {
            // otherwise put n at the back
            back->next = n;
            back = n;
            return 0;
        }
    }

    short dequeue() {
        if (front != nullptr) {
            Node* p = front;
            front = front->next;
            delete p;

            // if the list is now empty, update back ptr
            if (front == nullptr) {
                back = nullptr;
            }
            return 0;
        }
        return -1;
    }

    char first() {
        if (front != nullptr) {
            return front->c;
        }
        return '\0';
    }
};
