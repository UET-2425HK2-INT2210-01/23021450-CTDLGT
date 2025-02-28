#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList() : head(nullptr) {}


    bool insertAtPosition(int p, int x) {
		Node* newNode = new Node(x);

        if (p == 0) {
            newNode->next = head;
            head = newNode;
            return true;
        }


        Node* prev = head;
        int currentIndex = 0;
        while (prev != nullptr && currentIndex < p - 1) {
            prev = prev->next;
            currentIndex++;
        }

        if (prev == nullptr) {
            delete newNode;
            return false;
        }

        newNode->next = prev->next;
        prev->next = newNode;
        return true;
    }

    bool deleteAtPosition(int p) {

        if (head == nullptr || p < 0) {
            return false;
        }

        if (p == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        Node* prev = head;
        int currentIndex = 0;
        while (prev != nullptr && currentIndex < p - 1) {
            prev = prev->next;
            currentIndex++;
        }
        if (prev == nullptr || prev->next == nullptr) {
            return false;
        }
        Node* nodeToDelete = prev->next;
        prev->next = nodeToDelete->next;
        delete nodeToDelete;
        return true;
    }


    void printList() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }
};


int main() {
    LinkedList list;
	int n;
	cin>> n;
   for (int i =0; i<n;i++) {

        string cmd;
        cin >> cmd;

        if (cmd == "insert") {
            int p, x;
            cin >> p >> x;
            bool ok = list.insertAtPosition(p, x);

        }
        else if (cmd == "delete") {
            int p;
            cin >> p;
            bool ok = list.deleteAtPosition(p);
		}

	}

    list.printList();
	system("pause");
}
