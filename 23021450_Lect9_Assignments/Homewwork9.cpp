//Bài 1:

#include <iostream>
using namespace std;

void swap(double &a, double &b) { // Hàm hoán đổi hai phần tử
    double temp = a;
    a = b;
    b = temp;
}

struct Range { // Cấu trúc để lưu cặp chỉ số trái và phải
    int left;
    int right;
};

void quickSort(double arr[], int n) {
    Range* stack = new Range[n]; // Stack để lưu các phạm vi cần xử lý
    int top = -1; // Chỉ số của stack
    
    stack[++top] = {0, n-1}; // Đưa phạm vi toàn bộ mảng vào stack
    
    while (top >= 0) { // Trong khi stack không rỗng
        Range current = stack[top--]; // Lấy phạm vi trên cùng ra khỏi stack
        int left = current.left; // Chỉ số trái
        int right = current.right; // Chỉ số phải
        
        double pivot = arr[(left + right)/2]; // Chọn pivot là phần tử giữa mảng
        
        int i = left, j = right; // Chỉ số trái và phải
        while (i <= j) { // Vòng lặp cho đến khi chỉ số trái lớn hơn chỉ số phải
            while (arr[i] < pivot) i++; // Tăng chỉ số trái nếu phần tử nhỏ hơn pivot
            while (arr[j] > pivot) j--; // Giảm chỉ số phải nếu phần tử lớn hơn pivot
             
            if (i <= j) { // Hoán đổi hai phần tử nếu chỉ số trái nhỏ hơn hoặc bằng chỉ số phải
                swap(arr[i], arr[j]); 
                i++;
                j--;
            }
        }
        
        // Đưa các phạm vi con vào stack nếu cần
        if (j > left) { // Nếu còn phần tử bên trái của pivot
            stack[++top] = {left, j};
        }
        if (i < right) { // Nếu còn phần tử bên phải của pivot
            stack[++top] = {i, right};
        }
    }
    
    delete[] stack; // Giải phóng bộ nhớ stack
}

int main() {
    int n;
    cin >> n;
    double* arr = new double[n]; // Cấp phát mảng động
    
    for(int i = 0; i < n; i++) { // Nhập các phần tử vào mảng
        cin >> arr[i];
    }
    
    quickSort(arr, n); // Sắp xếp mảng bằng hàm quickSort
    
    for(int i = 0; i < n; i++) { // In các phần tử đã sắp xếp
        cout << arr[i];
        if(i < n-1) cout << " ";
    }
    
    delete[] arr; // Giải phóng bộ nhớ cấp phát
    return 0;
}

// Bài 2:
#include <iostream>
using namespace std;

bool checkSubsetSum(int arr[], int n, int X) { // Hàm kiểm tra xem có tồn tại một tập con nào có tổng bằng X không
    bool* dp = new bool[X + 1]; // Mảng dp để lưu trữ các giá trị true/false cho từng tổng từ 0 đến X
    
    for(int i = 0; i <= X; i++) { // Khởi tạo mảng dp với giá trị false
        dp[i] = false;
    }
    
    dp[0] = true; // Tổng 0 luôn có thể đạt được bằng cách không chọn phần tử nào
    
    for(int i = 0; i < n; i++) { // Duyệt qua từng phần tử trong mảng
        for(int j = X; j >= arr[i]; j--) { // Duyệt từ X đến giá trị của phần tử hiện tại
            if(dp[j - arr[i]] == true) { // Nếu tổng j - arr[i] có thể đạt được
                dp[j] = true; 
            }
        }
    }
    
    bool result = dp[X]; // Kết quả cuối cùng là xem tổng X có thể đạt được hay không
    
    delete[] dp; // Giải phóng bộ nhớ dp
    
    return result; // Trả về kết quả
}

int main() {
    int n, X;
    cin >> n >> X;
    
    int* arr = new int[n]; // Cấp phát mảng động để lưu danh sách tuổi của n sinh viên
    
    for(int i = 0; i < n; i++) { // Nhập tuổi của từng sinh viên
        cin >> arr[i];
    }
    
    if(checkSubsetSum(arr, n, X)) { // Kiểm tra xem có tồn tại tập con nào có tổng bằng X không
        cout << "YES";
    } else {
        cout << "NO";
    }
    
    delete[] arr; // Giải phóng bộ nhớ cấp phát
    return 0;
}

//Bài 3:

#include <iostream>
using namespace std;

int main() {
    int n, X;
    cin >> n >> X;  // Nhập số lượng đồ vật và trọng lượng tối đa
    
    int* weight = new int[n + 1]; // Cấp phát mảng động để lưu trọng lượng của n đồ vật
    int* value = new int[n + 1]; // Cấp phát mảng động để lưu giá trị của n đồ vật
    
    for(int i = 1; i <= n; i++) { // Nhập trọng lượng và giá trị của từng đồ vật
        cin >> weight[i] >> value[i];
    }
    
    int** dp = new int*[n + 1]; // Cấp phát mảng 2 chiều dp để lưu trữ giá trị lớn nhất có thể đạt được với sức chứa từ 0 đến X
    for(int i = 0; i <= n; i++) { // Cấp phát từng hàng của mảng 2 chiều
        dp[i] = new int[X + 1]; 
    }
    
    for(int j = 0; j <= X; j++) { // Khởi tạo tất cả giá trị trong dp bằng 0
        dp[0][j] = 0;
    }
    
    for(int i = 1; i <= n; i++) { // Duyệt từng đồ vật
        for(int j = 0; j <= X; j++) { // Duyệt từng trọng lượng từ 0 đến X
            if(weight[i] <= j) { // Nếu trọng lượng đồ vật thứ i nhỏ hơn hoặc bằng j
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i]] + value[i]); // Tính giá trị lớn nhất giữa việc không lấy đồ vật thứ i và việc lấy đồ vật thứ i
            } else {
                dp[i][j] = dp[i-1][j]; // Nếu trọng lượng đồ vật thứ i lớn hơn j, không thể lấy đồ vật thứ i
            }
        }
    }
    
    cout << dp[n][X]; // In giá trị lớn nhất có thể đạt được với sức chứa tối đa X
    
    for(int i = 0; i <= n; i++) { // Giải phóng bộ nhớ cấp phát cho từng hàng của mảng 2 chiều
        delete[] dp[i]; 
    }
    delete[] dp; // Giải phóng bộ nhớ cấp phát cho mảng 2 chiều
    delete[] weight; // Giải phóng bộ nhớ cấp phát cho mảng trọng lượng
    delete[] value; // Giải phóng bộ nhớ cấp phát cho mảng giá trị
    
    return 0;
}

