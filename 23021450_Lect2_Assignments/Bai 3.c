#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int n) {
        data = n;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void add(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    int countTriplets() {

        if (!head || !head->next || !head->next->next) {
            return 0;
        }

        int count = 0;
        Node* current = head->next;

        while (current->next) {
            int sum = current->prev->data + current->data + current->next->data;

            if (sum == 0) {
                count++;
            }
            current = current->next;
        }
        return count;
    }
};
int main()
{
    int n;
    cin >> n;
    DoublyLinkedList x;

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        x.add(m);
    }

    cout << x.countTriplets();

    return 0;
}
