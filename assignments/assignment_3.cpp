#include <ios>
#include <iostream>
#include <limits>
#include <new>
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

void printMenu() {
    std::cout << "COMSC210 MUSIC PLAYER MENU" << std::endl;
    std::cout << "(a)dd song" << std::endl;
    std::cout << "(c)lear playlist" << std::endl;
    std::cout << "(p)rint playlist" << std::endl;
    std::cout << "(r)emove song" << std::endl;
    std::cout << "(s)earch playlist" << std::endl;
    std::cout << "(q)uit" << std::endl;
}

char getUserInput() {
    char userInput{};

    while (true) {
        std::cout << "\n: ";
        std::cin >> userInput;

        // check if input operation was successful
        if (std::cin.fail()) {
            std::cout << "Invalid input. Please select another menu item."
                      << std::endl;
            // clear the error flag
            std::cin.clear();
            // discard the rest of the line
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // go to the next loop iteration
            continue;
        }
        // check if the character is one of the valid menu options
        if (userInput == 'a' || userInput == 'c' || userInput == 'p' ||
            userInput == 'r' || userInput == 's' || userInput == 'q') {
            return userInput;
        } else {
            // the character was valid but is not one of the valid menu options
            std::cout << "Invalid input. Please select another menu item."
                      << std::endl;
            // still need to clear the buffer in case more than one char was
            // typed
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::string getSongTitle() {
    std::string songTitle{};
    std::cout << "Enter a song title: ";

    // ignore the left over '\n' in the input buffer from previous `cin >>`
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // read the entire line
    std::getline(std::cin, songTitle);

    return songTitle;
}

void handleErr(short err, std::string errMsg, std::string succMsg) {
    if (err == -1) {
        std::cout << errMsg << std::endl << std::endl;
    } else if (err == 0) {
        std::cout << succMsg << std::endl << std::endl;
    }
}

int main() {
    MyList list{};
    char userInput{};
    /*uiLoop(list);*/

    do {
        printMenu();
        userInput = getUserInput();

        // these tasks require a song title
        if (userInput == 'a' || userInput == 'r' || userInput == 's') {
            std::string songName{getSongTitle()};

            switch (userInput) {
                case 'a': {
                    short err = list.add(songName);
                    handleErr(err, "Memory allocation error!", "Song added.");
                    break;
                }
                case 'r': {
                    short err = list.remove(songName);
                    handleErr(err, "Song not found.", "Song removed.");
                    break;
                }

                case 's': {
                    short err = list.find(songName);
                    handleErr(err, "Song not found.", "Song found.");
                    break;
                }
            }
        } else {  // this tasks do not require a song title
            switch (userInput) {
                case 'c': {
                    list.clear();
                    std::cout << "Playlist cleared" << std::endl << std::endl;
                    break;
                }
                case 'p': {
                    std::cout << "\nCURRENT PLAYLIST:\n\n"
                              << list.print() << std::endl
                              << list.getSize() << " total songs." << std::endl
                              << std::endl;

                    break;
                }
                case 'q': {
                    // handled by loop condition
                    break;
                }
                default: {
                    // something went deeply wrong if we end up here, should
                    // be handled by getUserInput(), but good practice :-)
                    std::cout << "Invalid option" << std::endl;
                    break;
                }
            }
        }

    } while (userInput != 'q');

    std::cout << "goodbye!" << std::endl;

    return 0;
}
