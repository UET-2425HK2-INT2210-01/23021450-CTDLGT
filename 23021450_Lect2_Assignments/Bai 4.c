#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int n) {
        data = n;
        next = nullptr;
    }
};

class Queue {
public:
    Node* head;
    Node* tail;

    Queue () {
        head = tail = nullptr;
    }

    void enqueue(int x) {
        Node* newNode = new Node(x);

        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void dequeue() {
        if (!head) {
            return;
        } else {
            Node* temp = head;
            head = head->next;

            if (!head) {
                tail = nullptr;
            }
            delete temp;
        }
    }

    void printQueue() {
        Node* temp = head;
        while(temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};
int main()
{
    int n;
    cin >> n;
    cin.ignore();

    Queue q;
    for (int i = 0; i < n; i++) {
        string x;
        cin >> x;

        if (x == "enqueue") {
            int d;
            cin >> d;
            q.enqueue(d);
        } else if (x == "dequeue") {
            q.dequeue();
        }
    }

    q.printQueue();

    return 0;
}
