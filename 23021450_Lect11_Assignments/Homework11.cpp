#include <iostream>
using namespace std;

struct Edge { // cấu trúc lưu trữ cạnh
    int u, v, w; // u: đỉnh đầu, v: đỉnh cuối, w: trọng số
};

int main() {
    int n, m, s, e; // n: số lượng thành phố, m: số lượng đường, s: thành phố bắt đầu, e: thành phố kết thúc
    const int INF = 1000000000; // giá trị vô cực
    cin >> n >> m >> s >> e; // Nhập số lượng thành phố, số lượng đường, thành phố bắt đầu và thành phố kết thúc
    
    Edge* edges = new Edge[m]; // cấp phát động m cạnh
    for (int i = 0; i < m; i++) { // Nhập thông tin các cạnh
        cin >> edges[i].u >> edges[i].v >> edges[i].w; // u: đỉnh đầu, v: đỉnh cuối, w: trọng số
    }
    
    int* dist = new int[n+1]; // mảng lưu trữ khoảng cách từ đỉnh s đến các đỉnh khác
    int* pred = new int[n+1]; // mảng lưu trữ đỉnh trước đó trên đường đi ngắn nhất
    for (int i = 1; i <= n; i++) { // Khởi tạo khoảng cách và đỉnh trước đó
        dist[i] = INF; // gán khoảng cách từ s đến các đỉnh khác là vô cực
        pred[i] = -1; // gán đỉnh trước đó là -1 (không có đỉnh trước đó)
    }
    dist[s] = 0; // khoảng cách từ s đến chính nó là 0
     
    for (int i = 1; i <= n - 1; i++) { // thuật toán Bellman-Ford
        for (int j = 0; j < m; j++) { // lặp lại m lần
            int u = edges[j].u; // đỉnh đầu
            int v = edges[j].v; // đỉnh cuối
            int w = edges[j].w; // trọng số
            if (dist[u] != INF && dist[u] + w < dist[v]) { // nếu có đường đi từ u đến v
                dist[v] = dist[u] + w; // cập nhật khoảng cách từ s đến v
                pred[v] = u; // cập nhật đỉnh trước đó của v là u
            }
        }
    }
    
    int* path = new int[n]; // mảng lưu trữ đường đi từ s đến e
    int cnt = 0; // biến đếm số lượng đỉnh trong đường đi
    if (dist[e] != INF) { // nếu có đường đi từ s đến e
        int cur = e; // bắt đầu từ đỉnh e
        while (cur != -1) { // lặp lại cho đến khi không còn đỉnh trước đó
            path[cnt++] = cur; // lưu trữ đỉnh hiện tại vào mảng path
            if (cur == s) break; // nếu đỉnh hiện tại là s thì dừng lại
            cur = pred[cur]; // cập nhật đỉnh hiện tại là đỉnh trước đó
        }
    }
    

    int** fw = new int*[n]; // ma trận lưu trữ khoảng cách giữa các cặp đỉnh
    for (int i = 0; i < n; i++) { // cấp phát động n hàng
        fw[i] = new int[n]; // cấp phát động n cột
        for (int j = 0; j < n; j++) { // khởi tạo ma trận
            if (i == j) // nếu là đường chéo chính
                fw[i][j] = 0; // khoảng cách từ đỉnh i đến chính nó là 0
            else // nếu không phải là đường chéo chính
                fw[i][j] = INF; // khoảng cách từ đỉnh i đến j là vô cực
        }
    }
    

    for (int i = 0; i < m; i++) { // Nhập thông tin các cạnh vào ma trận
        int u = edges[i].u, v = edges[i].v, w = edges[i].w; // u: đỉnh đầu, v: đỉnh cuối, w: trọng số
        if (w < fw[u-1][v-1]) // nếu trọng số nhỏ hơn khoảng cách hiện tại
            fw[u-1][v-1] = w; // cập nhật khoảng cách từ u đến v
    }
    
    for (int k = 0; k < n; k++) { // thuật toán Floyd-Warshall
        for (int i = 0; i < n; i++) { // lặp qua tất cả các đỉnh
            for (int j = 0; j < n; j++) { // lặp qua tất cả các đỉnh
                if (fw[i][k] < INF && fw[k][j] < INF && fw[i][k] + fw[k][j] < fw[i][j]) { // nếu có đường đi từ i đến k và k đến j
                    fw[i][j] = fw[i][k] + fw[k][j]; // cập nhật khoảng cách từ i đến j
                }
            }
        }
    }
    

    if (dist[e] == INF) { // nếu không có đường đi từ s đến e
        cout << "INF" << "\n"; // xuất "INF"
        cout << "\n"; // không có đường đi
    } else { // nếu có đường đi từ s đến e
        cout << dist[e] << "\n"; // xuất khoảng cách từ s đến e
        for (int i = cnt - 1; i >= 0; i--) { // xuất đường đi từ s đến e
            cout << path[i]; // xuất đỉnh hiện tại
            if (i > 0) // nếu không phải là đỉnh cuối cùng
                cout << " "; // xuất khoảng trắng
        }
        cout << "\n"; // xuống dòng
    }
    

    for (int i = 0; i < n; i++) { // xuất ma trận khoảng cách
        for (int j = 0; j < n; j++) { // lặp qua tất cả các đỉnh
            if (fw[i][j] == INF) // nếu khoảng cách là vô cực
                cout << "INF"; // xuất "INF"
            else // nếu không phải là vô cực
                cout << fw[i][j]; // xuất khoảng cách
            if (j != n - 1) // nếu không phải là cột cuối cùng
                cout << " "; // xuất khoảng trắng
        }
        cout << "\n"; // xuống dòng
    }
    
    // Giải phóng bộ nhớ cấp phát động.
    delete [] edges;
    delete [] dist;
    delete [] pred;
    delete [] path;
    for (int i = 0; i < n; i++) {
        delete [] fw[i];
    }
    delete [] fw;
    
    return 0;
}