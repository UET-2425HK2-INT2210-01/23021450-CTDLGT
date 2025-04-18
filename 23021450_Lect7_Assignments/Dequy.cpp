
//Bai 1: Tinh tong 1 + 2 + ... + n
#include <iostream>
using namespace std;

int sum(int n) {
    if (n == 0) return 0; // Neu n = 0 thi tong = 0
    if (n == 1) return 1; // Neu n = 1 thi tong = 1
    return n + sum(n - 1); // Tinh tong n + tong (1 + 2 + ... + n - 1)
}
int main () {
    int n;
    cin >> n;
    cout << sum(n) << endl; // In ra tong 1 + 2 + ... + n
}

// Bai 2: Tinh giai thua n!
#include <iostream>
using namespace std;
int factorial(int n) {
    if (n == 0 || n == 1) return 1; // Neu n = 0 hoac n = 1 thi giai thua = 1
    return n * factorial(n - 1); // Tinh giai thua n! = n * (n - 1)!
}
int main () {
    int n;
    cin >> n;
    cout << factorial(n) << endl; // In ra giai thua n!
}

// Bai 3: Tinh so Fibonacci F(n)
#include <iostream>
using namespace std;
int fibonacci(int n) {
    if (n == 0) return 0; // Neu n = 0 thi F(0) = 0
    if (n == 1) return 1; // Neu n = 1 thi F(1) = 1
    return fibonacci(n - 1) + fibonacci(n - 2); // Tinh F(n) = F(n - 1) + F(n - 2)
}
int main () {
    int n;
    cin >> n;
    cout << fibonacci(n) << endl; // In ra F(n)
}

// Bai 4: Tinh luy thua x^n
#include <iostream>
using namespace std;
double power(double x, int n) {
    if (n == 0) return 1; // Neu n = 0 thi x^0 = 1  
    if (n == 1) return x; // Neu n = 1 thi x^1 = x
    return x * power(x, n - 1); // Tinh x^n = x * x^(n - 1)
}
int main () {
    double x;
    int n;
    cin >> x >> n;
    cout << power(x, n) << endl; // In ra x^n
}

// Bai 5: Dem so chu so trong so nguyen n
#include <iostream>
using namespace std;
int countDigits(int n) {
    if (n == 0) return 1; // Neu n = 0 thi co 1 chu so
    if (n < 10) return 1; // Neu n < 10 thi co 1 chu so
    return 1 + countDigits(n / 10); // Tinh so chu so = 1 + so chu so cua n / 10
}
int main () {
    int n;
    cin >> n;
    cout << countDigits(n) << endl; // In ra so chu so trong n
}

// Bai 6: Tinh tong cac chu so trong so nguyen n
#include <iostream>
using namespace std;
int sumDigits(int n) {
    if (n == 0) return 0; // Neu n = 0 thi tong cac chu so = 0
    return n % 10 + sumDigits(n / 10); // Tinh tong cac chu so = chu so cuoi + tong cac chu so cua n / 10
}
int main () {
    int n;
    cin >> n;
    cout << sumDigits(n) << endl; // In ra tong cac chu so trong n
}

// Bai 7: Dao nguoc so nguyen n
#include <iostream>
using namespace std;
int reverseRec(int n, int rev) {
    if (n == 0) return rev; // Neu n = 0 thi tra ve rev
    return reverseRec(n / 10, rev * 10 + n % 10); // Tinh dao nguoc = 10 * rev + chu so cuoi
}
int main () {
    int n;
    cin >> n;
    cout << reverseRec(n, 0) << endl; // In ra so dao nguoc
    return 0;
}








