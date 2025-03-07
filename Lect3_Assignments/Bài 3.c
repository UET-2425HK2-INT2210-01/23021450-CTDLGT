#include <iostream>

using namespace std;

const int MAX = 1000;

class QueueArray {
private:
    int front, rear;
    int queue[MAX];

public:
    QueueArray() {
        front = rear = 0;
    }

    void enqueue(int element) {
        if (rear == MAX) {
            cout << "Queue Overflow\n";
            return;
        }
        queue[rear++] = element;
    }

    void dequeue() {
        if (front == rear) {
            cout << "Queue Underflow\n";
            return;
        }
        front++;
    }

    void display() {
        if (front == rear) {
            cout << "Queue Empty\n";
            return;
        }
        for (int i = front; i < rear; i++)
            cout << queue[i] << " ";
        cout << endl;
    }
};

int main() {
    QueueArray q;
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
enqueue(queue[], element):
    if rear < size:
        queue[rear] = element
        rear = rear + 1

dequeue(queue[]):
    if front < rear:
        front = front + 1
*/
