#include <bits/stdc++.h>
using namespace std;
struct Node {
    int data;
    Node * next;

    Node() {
        data = 0;
        next = nullptr;
    }

    Node(int x) {
        data = x;
        next = nullptr;
    }
};

class LinkedList {

public:
    Node* head;
    LinkedList() {
        head = nullptr;
    }

    void append(int x) {
        Node* newNode  = new Node(x);
        Node* cur = head;
        if (cur == nullptr) {
            head = newNode;
        } else {
            while (cur->next) {
            cur = cur->next;
            }
            cur->next = newNode;
        }
    }

    void print() {
        Node *cur = head;
        while (cur) {
            cout << cur->data << " ";
            cur = cur->next;
        }
    }

    void search(int x) {
        Node* cur = head;
        int d = 0;
        int d1 = 0;
        while (cur) {
            d++;
            if (cur->data == x) {
                d1 = 1;
                cout << d;
                break;
            }
            cur = cur -> next;
        }

        if (d1 == 0) {
            cout << "NO";
        }
    }

    void reverse() {
        Node* cur = head;
        Node* prev = nullptr;
        Node* nextNode = nullptr;
        while (cur) {
            nextNode = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nextNode;
        }

        head = prev;
    }
};
int main()
{
    int n;
    cin >> n;
    LinkedList s;
    for (int i = 0; i < n; i++) {
        string x;
        cin >> x;
        if (x == "append") {
            int d;
            cin >> d;
            s.append(d);
        }
        if (x == "search") {
            int d;
            cin >> d;
            s.search(d);
        }
        if (x == "reverse") {
            s.reverse();
        }
    }
    s.print();
    return 0;
}
