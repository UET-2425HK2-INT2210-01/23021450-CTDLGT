// Bai 3:
#include <iostream>
using namespace std;

int main() {
    int n, X;
    cin >> n >> X; // Nhập số lượng đồ vật và sức chứa tối đa của ba lô
    
    int* weight = new int[n]; // Cấp phát mảng động để lưu trọng lượng của n đồ vật
    int* value  = new int[n]; // Cấp phát mảng động để lưu giá trị của n đồ vật
    
    for (int i = 0; i < n; i++) {
        cin >> weight[i] >> value[i]; // Nhập trọng lượng và giá trị của từng đồ vật
    }
    
    int* dp = new int[X + 1]; // Khởi tạo mảng dp để lưu trữ giá trị lớn nhất có thể đạt được với sức chứa từ 0 đến X
    for (int j = 0; j <= X; j++) { // Khởi tạo tất cả giá trị trong dp bằng 0
        dp[j] = 0; 
    }

    for (int i = 0; i < n; i++) { // Duyệt từng đồ vật
        for (int j = X; j >= weight[i]; j--) { // Duyệt từ sức chứa tối đa X đến trọng lượng của đồ vật hiện tại
            if (dp[j - weight[i]] + value[i] > dp[j]) // Cập nhật giá trị lớn nhất có thể đạt được với sức chứa j
                dp[j] = dp[j - weight[i]] + value[i]; 
        }
    }
    
    cout << dp[X]; // In ra giá trị lớn nhất có thể đạt được với sức chứa tối đa X
    
    // Giải phóng bộ nhớ cấp phát
    delete[] weight;
    delete[] value;
    delete[] dp;
    
    return 0;
}