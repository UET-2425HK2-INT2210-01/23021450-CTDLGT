// Bai 2:

#include <iostream>
using namespace std;

bool existSubset(int arr[], int n, int index, int target) { // Hàm kiểm tra xem có tồn tại một tập con nào có tổng bằng target không
    if (target == 0) // Nếu target bằng 0, tức là đã tìm thấy một tập con có tổng bằng target trả về true
        return true;
    if (index >= n) // Nếu đã duyệt hết mảng mà không tìm thấy tập con nào có tổng bằng target trả về false
        return false;

    if (existSubset(arr, n, index + 1, target - arr[index])) // Kiểm tra trường hợp chọn phần tử tại vị trí index và giảm target đi giá trị của phần tử đó
        return true; 
    
    return existSubset(arr, n, index + 1, target); // Kiểm tra trường hợp không chọn phần tử tại vị trí index
}

int main() {
    int n, X;
    cin >> n >> X; // Nhập số lượng sinh viên và tổng tuổi cần tìm
    
    int* arr = new int[n]; // Cấp phát mảng động để lưu danh sách tuổi của n sinh viên
    
    for (int i = 0; i < n; i++) {
        cin >> arr[i]; // Nhập tuổi của từng sinh viên
    }
    
    if (existSubset(arr, n, 0, X)) // Kiểm tra xem có tồn tại tập con nào có tổng bằng X không
        cout << "YES";
    else
        cout << "NO";
    
    delete[] arr;  // Giải phóng bộ nhớ cấp phát
    return 0;
}