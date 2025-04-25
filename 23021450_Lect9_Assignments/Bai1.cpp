// Bai 1:

#include <iostream>
using namespace std;

void quickSort(double arr[], int left, int right) { // Hàm sắp xếp nhanh
    int i = left, j = right; // chỉ số trái và phải
    double pivot = arr[(left + right) / 2]; // chọn pivot ở giữa mảng

    while (i <= j) { // vòng lặp cho đến khi chỉ số trái lớn hơn chỉ số phải
        while (arr[i] < pivot) // tăng chỉ số trái nếu phần tử nhỏ hơn pivot
            i++;
        while (arr[j] > pivot) // giảm chỉ số phải nếu phần tử lớn hơn pivot
            j--;
        if (i <= j) { // hoán đổi hai phần tử nếu chỉ số trái nhỏ hơn hoặc bằng chỉ số phải
            double temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++; // tăng chỉ số trái
            j--; // giảm chỉ số phải
        }
    }
    if (left < j) // đệ quy sắp xếp nửa trái mảng
        quickSort(arr, left, j);
    if (i < right) // đệ quy sắp xếp nửa phải mảng
        quickSort(arr, i, right);
}

int main() {
    int n;
    cin >> n;
    double* arr = new double[n];  // cấp phát mảng động

    for (int i = 0; i < n; i++) {
        cin >> arr[i]; // nhập các phần tử vào mảng
    }

    quickSort(arr, 0, n - 1); // sắp xếp mảng bằng hàm quickSort

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " "; // in các phần tử đã sắp xếp
    }

    delete[] arr;  // giải phóng bộ nhớ cấp phát
    return 0;
}
