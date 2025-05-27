// Bài 1

#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m; // n là số công việc, m là số yêu cầu (cạnh) giữa các công việc.
    
    int* indegree = new int[n+1]; // mảng lưu bậc vào (indegree) của từng công việc.
    int** adj = new int*[n+1]; // danh sách kề của từng công việc
    int* adjSize = new int[n+1];  // mảng lưu kích thước danh sách kề của từng công việc

    for (int i = 1; i <= n; i++) { // Khởi tạo mảng indegree và danh sách kề cho từng công việc
        indegree[i] = 0; // bậc vào ban đầu là 0
        adjSize[i] = 0; // kích thước danh sách kề ban đầu là 0
        adj[i] = new int[m]; // cấp phát mảng động cho danh sách kề của công việc i
    }
    for (int i = 0; i < m; i++) { // Đọc m yêu cầu (cạnh) giữa các công việc
        int u, v; // u là công việc phải thực hiện trước v
        cin >> u >> v; // Đọc công việc u và v từ đầu vào
        indegree[v]++; // tăng bậc vào của công việc v vì có một công việc u phải thực hiện trước v
        adj[u][adjSize[u]++] = v; // thêm v vào danh sách kề của u và tăng kích thước danh sách kề của u
    }
    
    int* result = new int[n]; // mảng lưu kết quả sắp xếp topological
    int count = 0; // biến đếm số công việc đã được sắp xếp
    

    for (int k = 1; k <= n; k++) { // Lặp n lần để tìm n công việc theo thứ tự sắp xếp topological
        int job = -1; // Biến job để lưu công việc có indegree = 0
        for (int i = 1; i <= n; i++) { // Tìm công việc đầu tiên có indegree = 0
            if (indegree[i] == 0) { // Nếu tìm thấy công việc có indegree = 0
                job = i; // Lưu công việc này vào biến job
                indegree[i] = -1; // Đánh dấu công việc này đã được xử lý bằng cách gán indegree[i] = -1
                break; // Thoát vòng lặp vì chỉ cần tìm công việc đầu tiên có indegree = 0
            }
        }
        if (job == -1) { // Nếu không tìm thấy công việc nào có indegree = 0, tức là đã xử lý hết các công việc
            break; // Thoát vòng lặp vì không còn công việc nào để xử lý
        }
        result[count++] = job; // Lưu công việc vừa tìm thấy vào mảng kết quả và tăng biến đếm count
        
        for (int j = 0; j < adjSize[job]; j++) { // Duyệt qua danh sách kề của công việc job
            int nextJob = adj[job][j]; // nextJob là công việc tiếp theo cần xử lý sau job
            if (indegree[nextJob] > 0) { // Nếu nextJob vẫn còn bậc vào lớn hơn 0
                indegree[nextJob]--; // Giảm bậc vào của nextJob đi 1 vì đã xử lý xong job
            }
        }
    }
    
    for (int i = 0; i < count; i++) { // In ra kết quả sắp xếp topological
        cout << result[i]; // In công việc thứ i trong mảng kết quả
        if (i < count - 1) // Nếu không phải là công việc cuối cùng, in dấu cách
            cout << " "; 
    }
    cout << "\n"; 
    
    // Giải phóng bộ nhớ cấp phát động.
    delete [] result;
    for (int i = 1; i <= n; i++) {
        delete [] adj[i];
    }
    delete [] adj;
    delete [] adjSize;
    delete [] indegree;
    
    return 0;
}

// Bài 2

#include <iostream>
using namespace std;

struct Edge { // Cấu trúc để lưu thông tin về một cạnh
    int u, v, d; // u và v là hai đỉnh của cạnh, d là chi phí kết nối giữa chúng
};

int findSet(int x, int* parent) { // Hàm tìm đại diện của tập chứa x (có sử dụng kỹ thuật nén đường)
    if (parent[x] != x) // Nếu x không phải là đại diện của tập, ta tìm đại diện của nó
        parent[x] = findSet(parent[x], parent); // Đệ quy để tìm đại diện và nén đường
    return parent[x]; // Trả về đại diện của tập chứa x
}


void unionSet(int x, int y, int* parent) { // Hàm hợp nhất hai tập chứa x và y
    int px = findSet(x, parent); // Tìm đại diện của tập chứa x
    int py = findSet(y, parent); // Tìm đại diện của tập chứa y
    if (px < py) // Nếu đại diện của x nhỏ hơn đại diện của y, ta gán đại diện của y là px
        parent[py] = px;     
    else if (py < px) // Nếu đại diện của y nhỏ hơn đại diện của x, ta gán đại diện của x là py
        parent[px] = py;
}

int main() {
    int n, m; // n là số máy (đỉnh), m là số cạnh (kết nối giữa các máy)
    cin >> n >> m; 
    
    Edge* edges = new Edge[m]; // Cấp phát mảng động để lưu các cạnh
    for (int i = 0; i < m; i++) { // Đọc thông tin về từng cạnh
        cin >> edges[i].u >> edges[i].v >> edges[i].d; 
    }
    
    for (int i = 0; i < m - 1; i++) { // Sắp xếp các cạnh theo chi phí d bằng thuật toán sắp xếp chọn (selection sort)
        int minIndex = i; // Giả sử cạnh i là cạnh có chi phí nhỏ nhất
        for (int j = i + 1; j < m; j++) { // Duyệt qua các cạnh còn lại để tìm cạnh có chi phí nhỏ hơn
            if (edges[j].d < edges[minIndex].d) // Nếu tìm thấy cạnh có chi phí nhỏ hơn, cập nhật minIndex
                minIndex = j; // cập nhật chỉ số của cạnh có chi phí nhỏ nhất
        }
        if (minIndex != i) { // Nếu minIndex khác i, ta hoán đổi hai cạnh
            Edge temp = edges[i]; // Lưu cạnh i vào biến tạm
            edges[i] = edges[minIndex]; // Hoán đổi cạnh i với cạnh có chi phí nhỏ nhất
            edges[minIndex] = temp; // Gán cạnh có chi phí nhỏ nhất vào vị trí i
        }
    }
    
    int* parent = new int[n+1]; // Cấp phát mảng động để lưu đại diện của từng tập
    for (int i = 1; i <= n; i++) { // Khởi tạo mảng parent, mỗi đỉnh là đại diện của chính nó
        parent[i] = i; // parent[i] = i nghĩa là đỉnh i là đại diện của tập chứa nó
    }
    
    int totalCost = 0; // Biến lưu tổng chi phí kết nối của cây khung nhỏ nhất (MST)
    Edge* mstEdges = new Edge[n-1]; // Cấp phát mảng động để lưu các cạnh của MST
    int mstCount = 0; // Biến đếm số cạnh đã được thêm vào MST

    for (int i = 0; i < m; i++) { // Duyệt qua từng cạnh đã sắp xếp
        int setU = findSet(edges[i].u, parent); // Tìm đại diện của tập chứa đỉnh u
        int setV = findSet(edges[i].v, parent); // Tìm đại diện của tập chứa đỉnh v
        if (setU != setV) { // Nếu u và v không thuộc cùng một tập, ta có thể thêm cạnh này vào MST
            unionSet(setU, setV, parent); // Hợp nhất hai tập chứa u và v
            totalCost += edges[i].d; // Cộng chi phí của cạnh vào tổng chi phí kết nối
            mstEdges[mstCount++] = edges[i]; // Lưu cạnh vào mảng mstEdges và tăng biến đếm mstCount
            if (mstCount == n - 1) // Nếu đã đủ n-1 cạnh, ta đã tìm được MST
                break; 
        }
    }
    
    cout << totalCost << "\n"; // In ra tổng chi phí kết nối của MST
    for (int i = 0; i < mstCount; i++) { // In ra các cạnh của MST
        cout << mstEdges[i].u << " " << mstEdges[i].v << " " << mstEdges[i].d << "\n"; // In cạnh thứ i trong MST
    }
    
    // Giải phóng bộ nhớ
    delete [] edges;
    delete [] parent;
    delete [] mstEdges;
    
    return 0;
}