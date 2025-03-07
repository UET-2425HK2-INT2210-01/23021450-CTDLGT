//Cách 1:
#include <iostream>

using namespace std;

long long pow2_iterative(int n) {
    long long result = 1;
    for (int i = 0; i < n; ++i) {
        result *= 2;
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    cout << pow2_iterative(n);
    return 0;
}

/* Mã giả:
function pow2(n):
    result = 1
    for i = 1 to n:
        result = result * 2
    return result
*/
//Cách 2:
#include <iostream>

using namespace std;

long long pow2_recursive(int n) {
    if (n == 0) return 1;
    long long temp = pow2_recursive(n / 2);
    if (n % 2 == 0) return temp * temp;
    else return 2 * temp * temp;
}

int main() {
    int n;
    cin >> n;
    cout << pow2_recursive(n);
    return 0;
}
/*
Mã giả:
function pow2(n):
    if n == 0:
        return 1
    temp = pow2(n/2)
    if n mod 2 == 0:
        return temp * temp
    else:
        return 2 * temp * temp
*/
