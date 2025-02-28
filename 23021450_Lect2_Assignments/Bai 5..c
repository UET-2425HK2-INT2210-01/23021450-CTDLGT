#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int n) {
        data = n;
        next = nullptr;
    }
};

class Stack {
public:
    Node* head;

    Stack () {
        head = nullptr;
    }

    void push(int x) {
        Node* newNode = new Node(x);
        newNode->next = head;
        head = newNode;
    }

    void pop() {
        if (!head) {
            return;
        } else {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void printStack() {
        vector<int> a;
        Node* temp = head;
        while (temp) {
            a.push_back(temp->data);
            temp = temp->next;
        }

        for (int i = a.size() - 1; i >= 0; i--) {
            cout << a[i] << " ";
        }
    }
};

int main()
{
    int n;
    cin >> n;
    cin.ignore();

    Stack s;
    for (int i = 0; i < n; i++) {
        string x;
        cin >> x;

        if (x == "push") {
            int d;
            cin >> d;
            s.push(d);
        } else if (x == "pop") {
            s.pop();
        }
    }

    s.printStack();

    return 0;
}
