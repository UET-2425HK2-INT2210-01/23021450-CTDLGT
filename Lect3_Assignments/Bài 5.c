#include <iostream>

using namespace std;

const int MAX = 1000;

class StackArray {
private:
    int top;
    int stack[MAX];

public:
    StackArray() { top = -1; }

    void push(int value) {
        if (top >= MAX - 1) {
            cout << "Stack Overflow\n";
            return;
        }
        stack[++top] = value;
    }

    void pop() {
        if (top < 0) {
            cout << "Stack Underflow\n";
            return;
        }
        top--;
    }

    void display() {
        if (top < 0) {
            cout << "Stack Empty\n";
            return;
        }
        for (int i = top; i >= 0; --i)
            cout << stack[i] << " ";
        cout << endl;
    }
};

int main() {
    StackArray s;
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
    stack[top] = element
    top = top + 1

pop(stack):
    element = stack[top]
    top = top - 1
    return element
*/
