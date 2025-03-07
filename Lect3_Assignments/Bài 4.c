#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

class QueueLinkedList {
private:
    Node *front, *rear;

public:
    QueueLinkedList() {
        front = rear = nullptr;
    }

    void enqueue(int value) {
        Node* temp = new Node{value, nullptr};
        if (!rear) {
            front = rear = temp;
            return;
        }
        rear->next = temp;
        rear = temp;
    }

    void dequeue() {
        if (!front) {
            cout << "Queue Underflow\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
    }

    void display() {
        if (!front) {
            cout << "Queue Empty\n";
            return;
        }
        Node* temp = front;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    QueueLinkedList q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    q.display();

    q.dequeue();
    q.display();

    return 0;
}
/*
Mã giả:
enqueue(queue, element):
    newNode = createNode(element)
    if rear is NULL:
        front = rear = newNode
    else:
        rear.next = newNode
        rear = newNode

dequeue(queue):
    if front is NULL:
        return NULL
    temp = front
    front = front.next
    if front is NULL:
        rear = NULL
    return temp.element
*/

