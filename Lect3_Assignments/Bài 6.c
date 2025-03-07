#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

class StackLinkedList {
private:
    Node* top;

public:
    StackLinkedList() { top = nullptr; }

    void push(int value) {
        Node* temp = new Node{value, top};
        top = temp;
    }

    void pop() {
        if (!top) {
            cout << "Stack Underflow\n";
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    void display() {
        if (!top) {
            cout << "Stack Empty\n";
            return;
        }
        Node* temp = top;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    StackLinkedList s;
    s.push(10);
    s.push(20);
    s.push(30);

    s.display();

    s.pop();
    s.display();

    return 0;
}
/*
Mã giả:

push(stack, element):
    newNode = createNode(element)
    newNode.next = top
    top = newNode

pop(stack):
    if top is NULL:
        return "Stack Underflow"
    element = top.value
    top = top.next
    return element
*/
