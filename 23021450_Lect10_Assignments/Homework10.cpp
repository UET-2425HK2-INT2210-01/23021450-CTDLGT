//Bài 1:

#include <iostream>
using namespace std;

int find(int* parent, int x) { // Hàm tìm gốc của x
    if (parent[x] != x) // Nếu x khác với gốc của nó
        parent[x] = find(parent, parent[x]); // Thay thế x bằng gốc của nó
    return parent[x]; // Trả về gốc của x
}

void unionSets(int* parent, int x, int y) { // Hàm hợp nhất 2 tập
    int rootX = find(parent, x); // Tìm gốc của x
    int rootY = find(parent, y); // Tìm gốc của y
    if (rootX != rootY) // Nếu x và y thuộc 2 tập khác nhau
        parent[rootY] = rootX; // Thay thế gốc của y bằng gốc của x
}

int main() {
    int n, m;
    cin >> n >> m; // Nhập số lượng thành viên và số lượng mối quan hệ

    int* parent = new int[n + 1]; // Khai báo mảng lưu trữ các gốc của các thành viên
    for (int i = 1; i <= n; i++) { // Lặp qua các thành viên
        parent[i] = i; // Mỗi thành viên là gốc của tập riêng
    }

    for (int i = 0; i < m; i++) { // Lặp qua các mối quan hệ
        int x, y; // Nhập 2 thành viên
        cin >> x >> y; // Nhập 2 thành viên
        unionSets(parent, x, y); // Hợp nhất 2 tập
    }

    int components = 0; // Số lượng các tập
    for (int i = 1; i <= n; i++) { // Lặp qua các thành viên
        if (find(parent, i) == i) // Nếu thành viên i là gốc của tập
            components++; // Tăng số lượng các tập
    }

    cout << components; // In số lượng các tập
    delete[] parent; // Xóa mảng
    return 0;
}

//Bài 2:

#include <iostream>
using namespace std;

struct Edge { // Khai báo cấu trúc lưu trữ thông tin của cạnh
    int v; // Điểm kết thúc
    int next; // Cạnh kế tiếp
};

int main() {
    int n, m, X, Y;
    cin >> n >> m >> X >> Y; // Nhập số lượng đỉnh, số lượng cạnh, 2 đỉnh

    int* head = new int[n + 1]; // Khai báo mảng lưu trữ đầu của các cạnh
    for (int i = 0; i <= n; i++) { // Lặp qua các đỉnh
        head[i] = -1; // Đặt đầu của mỗi đỉnh là -1
    }

    Edge* edges = new Edge[m]; // Khai báo mảng lưu trữ thông tin của các cạnh
    for (int i = 0; i < m; i++) { // Lặp qua các cạnh
        int u, v; // Nhập 2 đỉnh
        cin >> u >> v; // Nhập 2 đỉnh
        edges[i].v = v; // Lưu trữ điểm kết thúc của cạnh
        edges[i].next = head[u]; // Lưu trữ cạnh kế tiếp
        head[u] = i; // Đặt đầu của cạnh là i
    }

    int* dist = new int[n + 1]; // Khai báo mảng lưu trữ khoảng cách từ X đến các đỉnh
    for (int i = 0; i <= n; i++) { // Lặp qua các đỉnh
        dist[i] = -1; // Đặt khoảng cách từ X đến các đỉnh là -1
    }

    int* queueArray = new int[n + 1]; // Khai báo mảng lưu trữ các đỉnh trong hàng đợi
    int front = 0, rear = 0; // Khai báo các biến lưu trữ đầu và cuối của hàng đợi
    queueArray[rear++] = X; // Thêm X vào hàng đợi
    dist[X] = 0; // Đặt khoảng cách từ X đến X là 0

    while (front < rear) { // Lặp cho đến khi hàng đợi rỗng
        int u = queueArray[front++]; // Lấy đỉnh đầu tiên trong hàng đợi
        if (u == Y) // Nếu đỉnh u là Y
            break; // Dừng lặp
        for (int i = head[u]; i != -1; i = edges[i].next) { // Lặp qua các cạnh của u
            int v = edges[i].v; // Lấy điểm kết thúc của cạnh
            if (dist[v] == -1) { // Nếu khoảng cách từ X đến v chưa được tính
                dist[v] = dist[u] + 1; // Đặt khoảng cách từ X đến v là khoảng cách từ X đến u + 1
                queueArray[rear++] = v; // Thêm v vào hàng đợi
            }
        }
    }

    cout << dist[Y]; // In khoảng cách từ X đến Y

    // Giải phóng bộ nhớ
    delete[] head;
    delete[] edges;
    delete[] dist;
    delete[] queueArray;

    return 0;
}