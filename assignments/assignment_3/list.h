#include <string>

class MyList {
   private:
    struct Node {
        std::string songTitle;
        Node* next;
    };

    Node* head = nullptr;

   public:
    ~MyList() {
        // free all allocated memory
        clear();
    }

    bool isEmpty() const {
        if (head == nullptr) {
            return true;
        }
        return false;
    }

    short add(const std::string& song) {
        Node* n = new (std::nothrow) Node;
        if (n == nullptr) {
            return -1;
        }
        n->songTitle = song;
        n->next = nullptr;

        if (isEmpty()) {
            head = n;
            return 0;
        }

        Node* curr{head};

        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = n;
        return 0;
    }

    short remove(const std::string& song) {
        Node* curr{head};
        Node* prev{nullptr};

        // iterate through list, until song is found
        // if found, curr will point to node to be removed
        while (curr != nullptr && curr->songTitle != song) {
            prev = curr;
            curr = curr->next;
        }
        // in the event that we find the song
        if (curr != nullptr) {
            // if the song to be removed is at the beginning of the list
            if (prev == nullptr) {
                // head should now point to the second item in the list
                head = head->next;
            } else {
                prev->next = curr->next;
            }
            // free the node to be deleted
            delete curr;

            return 0;
        } else {
            // in the event that the song is not found, return error code
            return -1;
        }
    }

    void clear() {
        Node* curr{nullptr};
        while (head != nullptr) {
            curr = head;
            head = head->next;
            delete curr;
        }
    }

    short find(const std::string& song) const {
        Node* curr{head};
        while (curr != nullptr) {
            if (curr->songTitle == song) {
                return 0;
            }
            curr = curr->next;
        }
        return -1;
    }

    unsigned short getSize() const {
        unsigned short size{0};
        Node* curr{head};
        while (curr != nullptr) {
            size++;
            curr = curr->next;
        }
        return size;
    }

    std::string print() const {
        Node* curr{head};
        std::string songList{};

        while (curr != nullptr) {
            songList.append(curr->songTitle + "\n");
            curr = curr->next;
        }

        return songList;
    }
};
