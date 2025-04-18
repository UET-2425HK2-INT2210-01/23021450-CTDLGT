//Bai 1:

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream infile("numbers.txt"); // Mở file để đọc
    if (!infile) { // Nếu không mở được file thì thông báo lỗi
        cerr << "Không thể mở file numbers.txt" << endl;
        return 1; // Kết thúc chương trình
    }

    int count = 0; 
    double temp;
    while (infile >> temp) { // Đọc từng số từ file
        count++; // Đếm số lượng số
    }
    
    infile.clear(); // Xóa trạng thái lỗi của file stream
    infile.seekg(0, ios::beg); // Đặt con trỏ đọc về đầu file

    double* numbers = new double[count]; // Cấp phát bộ nhớ cho mảng số thực
    for (int i = 0; i < count; i++) {
        infile >> numbers[i]; // Đọc từng số vào mảng
    }
    infile.close(); // Đóng file sau khi đọc xong

    for (int i = 0; i < count - 1; i++) { // Sắp xếp nổi bọt (Bubble Sort)
        for (int j = i + 1; j < count; j++) { 
            if (numbers[i] > numbers[j]) { // Nếu số ở vị trí i lớn hơn số ở vị trí j thì hoán đổi
                double tmp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = tmp;
            }
        }
    }

    ofstream outfile("numbers.sorted"); // Mở file để ghi
    if (!outfile) { // Nếu không mở được file thì thông báo lỗi
        cerr << "Không thể mở file numbers.sorted" << endl;
        delete[] numbers; // Giải phóng bộ nhớ đã cấp phát
        return 1; // Kết thúc chương trình
    }

    for (int i = 0; i < count; i++) {
        outfile << numbers[i]; // Ghi từng số vào file
        if (i != count - 1) // Nếu không phải số cuối cùng thì ghi dấu cách
            outfile << " "; 
    }
    outfile.close(); // Đóng file sau khi ghi xong

    delete[] numbers; // Giải phóng bộ nhớ đã cấp phát
    return 0;
}

// Bai 2:

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream infile("matrix.txt"); // Mở file để đọc
    if (!infile) { // Nếu không mở được file thì thông báo lỗi
        cerr << "Không thể mở file matrix.txt" << endl;
        return 1; // Kết thúc chương trình
    }

    int m, n;
    infile >> m >> n; // Đọc kích thước ma trận từ file

    // Cấp phát ma trận động (m hàng, n cột)
    int** matrix = new int*[m]; // Cấp phát mảng con cho từng hàng
    for (int i = 0; i < m; i++) { // Cấp phát mảng con cho từng cột
        matrix[i] = new int[n]; 
        for (int j = 0; j < n; j++) {
            infile >> matrix[i][j]; // Đọc từng phần tử của ma trận từ file
        }
    }
    infile.close(); // Đóng file sau khi đọc xong

    int finalTop = 0, finalLeft = 0, finalBottom = 0, finalRight = 0; // Chỉ số của các đỉnh của hình chữ nhật
    int maxSum = -1000000000; // Khởi tạo bằng một số rất nhỏ

    int* temp = new int[n]; // Mảng tạm để lưu trữ tổng cột

    for (int top = 0; top < m; top++) { // Duyệt từ hàng trên cùng
        for (int j = 0; j < n; j++) { // Khởi tạo lại mảng tạm cho mỗi hàng trên cùng
            temp[j] = 0; // Đặt lại giá trị của mảng tạm về 0
        }
        for (int bottom = top; bottom < m; bottom++) { // Duyệt từ hàng dưới cùng
            for (int j = 0; j < n; j++) {
                temp[j] += matrix[bottom][j]; // Cộng dồn giá trị của hàng dưới cùng vào mảng tạm
            }

            // Áp dụng thuật toán Kadane trên mảng tạm để tìm subarray có tổng lớn nhất
            int currentSum = 0;
            int localLeft = 0;
            for (int j = 0; j < n; j++) {
                currentSum += temp[j]; // Cộng dồn giá trị của mảng tạm
                if (currentSum > maxSum) { // Nếu tổng hiện tại lớn hơn tổng lớn nhất đã tìm thấy
                    maxSum = currentSum; // Cập nhật tổng lớn nhất
                    finalTop = top; // Cập nhật chỉ số hàng trên cùng
                    finalBottom = bottom; // Cập nhật chỉ số hàng dưới cùng
                    finalLeft = localLeft; // Cập nhật chỉ số cột bên trái
                    finalRight = j; // Cập nhật chỉ số cột bên phải
                }
                if (currentSum < 0) { // Nếu tổng hiện tại âm, reset và thiết lập vị trí mới
                    currentSum = 0; // Đặt lại tổng hiện tại về 0
                    localLeft = j + 1; // Cập nhật chỉ số cột bên trái cho subarray mới
                }
            }
        }
    }
    delete [] temp; // Giải phóng bộ nhớ mảng tạm

    for (int i = 0; i < m; i++) {
        delete [] matrix[i]; // Giải phóng bộ nhớ cho từng hàng của ma trận
    }
    delete [] matrix; // Giải phóng bộ nhớ cho mảng con của ma trận

    ofstream outfile("matrix.out"); // Mở file để ghi kết quả
    if (!outfile) { // Nếu không mở được file thì thông báo lỗi
        cerr << "Không thể mở file matrix.out" << endl;
        return 1; // Kết thúc chương trình
    }
    outfile << (finalTop + 1) << " " << (finalLeft + 1) << " " 
            << (finalBottom + 1) << " " << (finalRight + 1) << " " 
            << maxSum; // Ghi chỉ số hàng trên cùng, cột bên trái, hàng dưới cùng, cột bên phải và tổng lớn nhất vào file
    outfile.close(); // Đóng file sau khi ghi xong

    return 0; 
}

// Bai 3:

#include <iostream>
using namespace std;

int gcd(int x, int y) { // Tính ước số chung lớn nhất của x và y
    if (y == 0) // Nếu y = 0 thì ước số chung lớn nhất là x
        return x; // Nếu x = 0 thì ước số chung lớn nhất là y
    return gcd(y, x % y); // Gọi đệ quy với y và x % y
}

int main() {
    int X, Y;
    cin >> X >> Y; // Nhập vào hai số nguyên dương X và Y
    cout << gcd(X, Y) << endl; // In ra ước số chung lớn nhất của X và Y
    return 0;
}

// Bai 4:

#include <iostream>
#include <string>
using namespace std;

void generateBinary(string prefix, int n) { // Hàm đệ quy để tạo chuỗi nhị phân
    if (n == 0) { // Nếu n = 0 thì in ra chuỗi hiện tại
        cout << prefix << endl;
        return; // Kết thúc đệ quy
    }

    generateBinary(prefix + "0", n - 1); // Gọi đệ quy với thêm "0" vào chuỗi hiện tại
    generateBinary(prefix + "1", n - 1); // Gọi đệ quy với thêm "1" vào chuỗi hiện tại
    // Khi n > 0, gọi đệ quy hai lần: một lần với "0" và một lần với "1"
}

int main() {
    int n;
    cin >> n; // Nhập số n từ bàn phím
    generateBinary("", n); // Gọi hàm đệ quy với chuỗi rỗng và n
    return 0;
}

// Bai 5:

#include <iostream>
#include <string>
using namespace std;

void permute(string &s, int l, int r) { // Hàm đệ quy để tạo hoán vị
    if (l == r) { // Nếu l = r thì in ra chuỗi hiện tại
        cout << s << endl; 
        return; // Kết thúc đệ quy
    }
    for (int i = l; i <= r; i++) { // Duyệt từ l đến r
        swap(s[l], s[i]);       // Hoán vị ký tự tại vị trí l với i
        permute(s, l + 1, r);     // Đệ quy tạo hoán vị ở phần tử tiếp theo
        swap(s[l], s[i]);       // Quay lại trạng thái ban đầu
    }
}

int main() {
    int n;
    cin >> n; // Nhập số n từ bàn phím

    string s = ""; // Khởi tạo chuỗi rỗng
    for (int i = 1; i <= n; i++) {
        s.push_back('0' + i); // Thêm ký tự từ '1' đến 'n' vào chuỗi
    }

    permute(s, 0, s.size() - 1); // Gọi hàm đệ quy để tạo hoán vị
    return 0;
}