#include <ios>
#include <iostream>
#include <limits>
#include <string>
class MyPQueue {
   private:
    struct Node {
        std::string name;
        unsigned short pri;
        Node* next;
    };

    Node* head;

   public:
    MyPQueue() { head = nullptr; }
    ~MyPQueue() { clear(); }

    short enqueue(std::string name, unsigned short pri) {
        // create a new node for the patient
        Node* patient = new (std::nothrow) Node;
        if (patient == nullptr) {
            return -1;  // memory allocation failed
        }
        patient->name = name;
        patient->pri = pri;
        patient->next = nullptr;

        // if the list is empty put this patient at the front
        if (head == nullptr) {
            head = patient;
            return 0;
        }

        // traverse the list and add them according to their priority
        Node* curr = head;
        Node* prev = nullptr;
        while (curr != nullptr && pri < curr->pri) {
            prev = curr;
            curr = curr->next;
        }
        if (prev == nullptr) {
            patient->next = head;
            head = patient;
        } else {
            patient->next = curr;
            prev->next = patient;
        }
        return 0;
    }

    std::string dequeue() {
        if (head == nullptr) {
            return "";
        }

        Node* nodeToDelete = head;
        std::string name = head->name;
        head = head->next;

        delete nodeToDelete;

        return name;
    }

    short update(std::string name, unsigned short pri) {
        // simplest method is to delete the old patient in the list
        // and enqueue them with their updated priority
        // this ensures the patient is sorted correctly
        Node* curr = head;
        Node* prev = nullptr;

        while (curr != nullptr && curr->name != name) {
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) {
            return -1;
        }
        if (prev == nullptr) {
            head = curr->next;
        } else {
            prev->next = curr->next;
        }

        delete curr;

        enqueue(name, pri);

        return 0;
    }

    std::string print() const {
        Node* curr = head;
        std::string patientList = "";

        while (curr != nullptr) {
            patientList.append(curr->name + "\t\t" + std::to_string(curr->pri) +
                               "\n");
            curr = curr->next;
        }

        return patientList;
    }

    void clear() {
        while (head != nullptr) {
            Node* nodeToDelete = head;
            head = head->next;
            delete nodeToDelete;
        }
    }
};

void displayMenu() {
    std::cout << "\nCOMSC210 TRIAGE SYSTEM\n";
    std::cout << "(a)dd patient\n";
    std::cout << "(c)lear patients\n";
    std::cout << "(l)ist patients\n";
    std::cout << "(n)ext patient\n";
    std::cout << "(u)pdate patient\n";
    std::cout << "(q)uit\n\n";
    std::cout << "Choice [aclnuq]: ";
}

int main() {
    MyPQueue pq;
    char choice;
    std::string patientName;
    unsigned short priority;

    do {
        displayMenu();
        std::cin >> choice;
        // Clear the input buffer to handle mixed cin and getline usage

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 'a':
            case 'A':
                std::cout << "Enter patient's name: ";
                std::getline(std::cin, patientName);

                std::cout << "Enter priority: ";
                std::cin >> priority;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');

                if (pq.enqueue(patientName, priority) == 0) {
                    std::cout << "'" << patientName
                              << "' added successfully.\n";
                } else {
                    std::cout
                        << "Error: Could not add patient. Memory allocation "
                           "failed.\n";
                }
                break;

            case 'c':
            case 'C': {
                pq.clear();
                std::cout << "Patient list cleared.\n";
                break;
            }

            case 'l':
            case 'L': {
                std::string listContents = pq.print();
                if (listContents.empty()) {
                    std::cout << "The patient list is currently empty.\n";
                } else {
                    std::cout << "\nPATIENT\t\t\tPR\n";
                    std::cout << listContents;
                }
                break;
            }

            case 'n':
            case 'N': {
                std::string name = pq.dequeue();
                if (name == "") {
                    std::cout << "Patient List is empty.\n";
                } else {
                    std::cout << "Next patient: " << name << std::endl;
                }
                break;
            }
            case 'u':
            case 'U': {
                std::cout << "Enter patient's name: ";
                std::getline(std::cin, patientName);

                std::cout << "Enter updated priority: ";
                std::cin >> priority;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');
                short err = pq.update(patientName, priority);
                if (err != -1) {
                    std::cout << "Patient updated.\n";
                } else {
                    std::cout << "Could not find patient.\n";
                }
                break;
            }

            case 'q':
            case 'Q': {
                std::cout << "Goodbye!\n";
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 'q' && choice != 'Q');

    return 0;
}
