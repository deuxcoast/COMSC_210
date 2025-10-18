#include <iostream>
#include <string>
#include <new>
#include <limits>
#include <sstream>

using namespace std;

class MyDLL {
   private:
    struct Node {
        string songTitle;
        Node* next;
        Node* prev;
    };

    Node* head;
    Node* tail;
    Node* cur;

   public:
    MyDLL();
    ~MyDLL();

    bool isEmpty();
    short add(string song);
    short remove(string song);
    void clear();
    short find(string song);
    unsigned short getSize();
    string print();
    string forward();
    string backward();
};

MyDLL::MyDLL() {
    head = nullptr;
    tail = nullptr;
    cur = nullptr;
}

MyDLL::~MyDLL() {
    clear();
}

bool MyDLL::isEmpty() {
    return head == nullptr;
}

short MyDLL::add(string song) {
    Node* newNode = new (std::nothrow) Node;
    if (newNode == nullptr) {
        return -1;  // Memory allocation failed
    }

    // Initialize the new node's data
    newNode->songTitle = song;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (isEmpty()) {
        // If the list is empty, the new node is head, tail, and current
        head = newNode;
        tail = newNode;
        cur = newNode;
    } else {
        // Otherwise, link the new node after the current tail
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    return 0;
}

short MyDLL::remove(string song) {
    Node* p = head;
    Node* q = nullptr;

    // Search for the node to remove
    while (p != nullptr && p->songTitle != song) {
        q = p;
        p = p->next;
    }

    // If p is nullptr, the song was not found
    if (p == nullptr) {
        return -1;
    }

    // Update 'cur' pointer BEFORE deleting the node
    if (cur == p) {
        cur = p->next;
        // If 'cur' becomes null (we removed the tail), wrap around to the head
        if (cur == nullptr) {
            cur = head;
        }
    }

    if (q == nullptr) {  // Removing the head node
        head = p->next;
    } else {  // Removing a middle or tail node
        q->next = p->next;
    }

    if (p->next == nullptr) {  // Removing the tail node
        tail = q;
    } else {  // Removing head or middle node
        p->next->prev = q;
    }

    delete p;  // Free the memory of the removed node

    // If the list is now empty after deletion, ensure cur is nullptr
    if (head == nullptr) {
        cur = nullptr;
    }

    return 0;  // Success
}

void MyDLL::clear() {
    while (tail != nullptr) {
        Node* nodeToDelete = tail;
        tail = tail->prev;
        delete nodeToDelete;
    }
    // Ensure all pointers are reset
    head = nullptr;
    cur = nullptr;
}

short MyDLL::find(string song) {
    Node* p = tail;  // Start search from the tail
    while (p != nullptr) {
        if (p->songTitle == song) {
            return 0;  // Found
        }
        p = p->prev;
    }
    return -1;  // Not found
}

unsigned short MyDLL::getSize() {
    unsigned short count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

string MyDLL::print() {
    if (isEmpty()) {
        return "";
    }

    stringstream ss;
    Node* temp = head;
    while (temp != nullptr) {
        ss << temp->songTitle;
        if (temp == cur) {
            ss << " (NOW PLAYING)";
        }
        ss << endl;
        temp = temp->next;
    }
    return ss.str();
}

string MyDLL::forward() {
    if (isEmpty() || cur == nullptr) {
        return "";
    }

    cur = cur->next;
    if (cur == nullptr) {  // Was at the tail, wrap around to head
        cur = head;
    }

    return cur->songTitle;
}

string MyDLL::backward() {
    if (isEmpty() || cur == nullptr) {
        return "";
    }

    cur = cur->prev;
    if (cur == nullptr) {  // Was at the head, wrap around to tail
        cur = tail;
    }

    return cur->songTitle;
}

void displayMenu() {
    cout << "\nCOMSC210 MUSIC PLAYER MENU\n";
    cout << "(a)dd song\n";
    cout << "(b)ackward\n";
    cout << "(c)lear playlist\n";
    cout << "(f)orward\n";
    cout << "(p)rint playlist\n";
    cout << "(r)emove song\n";
    cout << "(s)earch play list\n";
    cout << "(q)uit\n\n";
    cout << ": ";
}

int main() {
    MyDLL playlist;
    char choice;
    string songTitle;

    do {
        displayMenu();
        cin >> choice;
        // Clear the input buffer to handle mixed cin and getline usage
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 'a':
            case 'A':
                cout << "Enter song title to add: ";
                getline(cin, songTitle);
                if (playlist.add(songTitle) == 0) {
                    cout << "'" << songTitle << "' added successfully.\n";
                } else {
                    cout << "Error: Could not add song. Memory allocation "
                            "failed.\n";
                }
                break;

            case 'b':
            case 'B':
                if (playlist.isEmpty()) {
                    cout << "Playlist is empty. Cannot go backward.\n";
                } else {
                    songTitle = playlist.backward();
                    cout << "Now playing: '" << songTitle << "'\n";
                }
                break;

            case 'c':
            case 'C':
                playlist.clear();
                cout << "Playlist has been cleared.\n";
                break;

            case 'f':
            case 'F':
                if (playlist.isEmpty()) {
                    cout << "Playlist is empty. Cannot go forward.\n";
                } else {
                    songTitle = playlist.forward();
                    cout << "Moved forward. Now playing: '" << songTitle
                         << "'\n";
                }
                break;

            case 'p':
            case 'P': {
                string listContents = playlist.print();
                if (listContents.empty()) {
                    cout << "The playlist is currently empty.\n";
                } else {
                    cout << "\nCURRENT PLAYLIST:\n\n";
                    cout << listContents;
                }
                break;
            }

            case 'r':
            case 'R':
                if (playlist.isEmpty()) {
                    cout << "Playlist is empty. Nothing to remove.\n";
                } else {
                    cout << "Enter song title to remove: ";
                    getline(cin, songTitle);
                    if (playlist.remove(songTitle) == 0) {
                        cout << "'" << songTitle << "' was removed.\n";
                    } else {
                        cout << "'" << songTitle
                             << "' was not found in the playlist.\n";
                    }
                }
                break;

            case 's':
            case 'S':
                if (playlist.isEmpty()) {
                    cout << "Playlist is empty. Nothing to search for.\n";
                } else {
                    cout << "Enter song title to search for: ";
                    getline(cin, songTitle);
                    if (playlist.find(songTitle) == 0) {
                        cout << "Found it! '" << songTitle
                             << "' is in the playlist.\n";
                    } else {
                        cout << "Sorry, '" << songTitle << "' was not found.\n";
                    }
                }
                break;

            case 'q':
            case 'Q':
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != 'q' && choice != 'Q');

    return 0;
}
