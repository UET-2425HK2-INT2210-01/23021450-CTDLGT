#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isValid(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{')
            st.push(c);
        else {
            if (st.empty())
                return false;
            char top = st.top();
            st.pop();
            if (c == ')' && top != '(')
                return false;
            if (c == ']' && top != '[')
                return false;
            if (c == '}' && top != '{')
                return false;
        }
    }
    return st.empty();
}

int main(){
    string s;
    cin >> s;
    cout << (isValid(s) ? "Valid" : "Invalid");
    return 0;
}
