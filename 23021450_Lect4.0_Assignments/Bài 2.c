#include <iostream>
#include <string>
using namespace std;

struct Node {
    int value;
    int priority;
    Node* next;
    Node* prev;
    Node(int v, int p) {
        value = v;
        priority = p;
        next = nullptr;
        prev = nullptr;
    }
};

class PriorityQueue {
private:
    Node* head;
    Node* tail;
public:
    PriorityQueue() {
        head = nullptr;
        tail = nullptr;
    }

    void enqueue(int value, int priority) {
        Node* newNode = new Node(value, priority);
        if (head == nullptr) {
            head = tail = newNode;
            return;
        }
        if (priority > head->priority) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next != nullptr && current->next->priority >= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != nullptr) {
            current->next->prev = newNode;
        } else {
            tail = newNode;
        }
        current->next = newNode;
    }

    void dequeue() {
        if (head == nullptr)
            return;
        Node* temp = head;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
        else
            tail = nullptr;
        delete temp;
    }

    void printQueue() {
        Node* current = head;
        while (current != nullptr) {
            cout << "(" << current->value << ", " << current->priority << "); ";
            current = current->next;
        }
    }
};

int main(){
    int n;
    cin >> n;
    PriorityQueue queue;
    string op;
    for (int i = 0; i < n; i++){
        cin >> op;
        if (op == "enqueue"){
            int x, p;
            cin >> x >> p;
            queue.enqueue(x, p);
        } else if (op == "dequeue"){
            queue.dequeue();
        }
    }
    queue.printQueue();
    return 0;
}
