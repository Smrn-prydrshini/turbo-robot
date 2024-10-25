#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;

public:
    DoublyLinkedList() : head(nullptr) {}

    void insertEnd(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }

    void insertBeginning(int value) {
        Node* newNode = new Node(value);
        if (head) {
            newNode->next = head;
            head->prev = newNode;
        }
        head = newNode;
    }

    void insertBefore(int target, int value) {
        if (!head) return;
        Node* temp = head;
        while (temp && temp->data != target) {
            temp = temp->next;
        }
        if (!temp) {
            cout << "Target not found.\n";
            return;
        }
        Node* newNode = new Node(value);
        newNode->next = temp;
        newNode->prev = temp->prev;
        if (temp->prev) {
            temp->prev->next = newNode;
        } else {
            head = newNode;
        }
        temp->prev = newNode;
    }

    void insertAfter(int target, int value) {
        Node* temp = head;
        while (temp && temp->data != target) {
            temp = temp->next;
        }
        if (!temp) {
            cout << "Target not found.\n";
            return;
        }
        Node* newNode = new Node(value);
        newNode->prev = temp;
        newNode->next = temp->next;
        if (temp->next) {
            temp->next->prev = newNode;
        }
        temp->next = newNode;
    }

    void deleteEnd() {
        if (!head) return;
        Node* temp = head;
        if (!temp->next) {
            delete head;
            head = nullptr;
            return;
        }
        while (temp->next) {
            temp = temp->next;
        }
        temp->prev->next = nullptr;
        delete temp;
    }

    void deleteBeginning() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        delete temp;
    }

    void deleteBefore(int target) {
        if (!head || !head->next) return;
        Node* temp = head->next;
        while (temp && temp->data != target) {
            temp = temp->next;
        }
        if (!temp || !temp->prev) {
            cout << "No node found before target.\n";
            return;
        }
        Node* toDelete = temp->prev;
        if (toDelete->prev) {
            toDelete->prev->next = temp;
            temp->prev = toDelete->prev;
        } else {
            head = temp;
            temp->prev = nullptr;
        }
        delete toDelete;
    }

    void deleteAfter(int target) {
        Node* temp = head;
        while (temp && temp->data != target) {
            temp = temp->next;
        }
        if (!temp || !temp->next) {
            cout << "No node found after target.\n";
            return;
        }
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        if (toDelete->next) {
            toDelete->next->prev = temp;
        }
        delete toDelete;
    }

    void printList() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    int getLength() const {
        int length = 0;
        Node* temp = head;
        while (temp) {
            length++;
            temp = temp->next;
        }
        return length;
    }

    ~DoublyLinkedList() {
        while (head) {
            deleteBeginning();
        }
    }
};

int main() {
    DoublyLinkedList list;
    int choice, value, target;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert at End\n";
        cout << "2. Insert at Beginning\n";
        cout << "3. Insert Before\n";
        cout << "4. Insert After\n";
        cout << "5. Delete from End\n";
        cout << "6. Delete from Beginning\n";
        cout << "7. Delete Before\n";
        cout << "8. Delete After\n";
        cout << "9. Print List\n";
        cout << "10. Get Length\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert at end: ";
                cin >> value;
                list.insertEnd(value);
                break;
            case 2:
                cout << "Enter value to insert at beginning: ";
                cin >> value;
                list.insertBeginning(value);
                break;
            case 3:
                cout << "Enter target value to insert before: ";
                cin >> target;
                cout << "Enter value to insert: ";
                cin >> value;
                list.insertBefore(target, value);
                break;
            case 4:
                cout << "Enter target value to insert after: ";
                cin >> target;
                cout << "Enter value to insert: ";
                cin >> value;
                list.insertAfter(target, value);
                break;
            case 5:
                list.deleteEnd();
                cout << "Deleted node from end.\n";
                break;
            case 6:
                list.deleteBeginning();
                cout << "Deleted node from beginning.\n";
                break;
            case 7:
                cout << "Enter target value to delete before: ";
                cin >> target;
                list.deleteBefore(target);
                break;
            case 8:
                cout << "Enter target value to delete after: ";
                cin >> target;
                list.deleteAfter(target);
                break;
            case 9:
                cout << "List: ";
                list.printList();
                break;
            case 10:
                cout << "Length of the list: " << list.getLength() << endl;
                break;
            case 11:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
