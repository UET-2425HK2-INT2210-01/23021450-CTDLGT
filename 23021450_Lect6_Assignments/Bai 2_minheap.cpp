/*
Cây ban đầu:

           1
         /   \
        2     7
       / \   / \
      6   3 10  8
     / \
   13  20

Cây sau khi chèn 14, 0, 35:

         0
       /     \
      1          7
     /  \       / \
    6    2     10  8
   / \  / \   /
 13 20 14  3 35


Cây sau khi xóa 2, 1, 0:

         3
      /     \
     6       7
    / \     / \
   13 14   10  8
  /
 20
*/







#include <iostream>
using namespace std;

// Cấu trúc node cho min-heap
struct HeapNode {
    int data;                 // Giá trị của node
    HeapNode *left, *right;   // Con trái, con phải
    HeapNode *parent;         // Con trỏ tới node cha

    // Hàm khởi tạo node với giá trị cho trước
    HeapNode(int val) {
        data = val;
        left = right = parent = nullptr;
    }
    
    // Hàm khởi tạo mặc định
    HeapNode() {
        data = 0;
        left = right = parent = nullptr;
    }
};

// Hàm hoán đổi hai giá trị
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Bubble-up cho min-heap: nếu node có giá trị nhỏ hơn cha, đổi chỗ
void bubbleUpMin(HeapNode *node) {
    while (node->parent && node->data < node->parent->data) { // Kiểm tra nếu node có cha và giá trị nhỏ hơn cha
        swap(node->data, node->parent->data); // Hoán đổi giá trị
        node = node->parent; // Cập nhật node thành cha của nó
    }
}

// Bubble-down cho min-heap: sau khi thay đổi giá trị, đổi chỗ với con có giá trị nhỏ nhất nếu cần
void bubbleDownMin(HeapNode *node) {
    while (true) { // Lặp cho đến khi không còn cần đổi chỗ
        HeapNode *smallest = node; // Giả định node là nhỏ nhất
        if (node->left && node->left->data < smallest->data) // So sánh với con trái
            smallest = node->left; // Nếu con trái nhỏ hơn node thì cập nhật smallest
        if (node->right && node->right->data < smallest->data) // So sánh với con phải
            smallest = node->right; // Nếu con phải nhỏ hơn smallest thì cập nhật smallest
        if (smallest == node) // Nếu smallest không thay đổi thì không cần đổi chỗ nữa
            break;
        swap(node->data, smallest->data); // Hoán đổi giá trị giữa node và smallest
        node = smallest; // Cập nhật node thành smallest để tiếp tục kiểm tra
    }
}

// Tìm vị trí chèn mới theo thứ tự level-order (sử dụng mảng tĩnh làm queue)
HeapNode* findInsertPos(HeapNode *root, bool &isLeft) {
    HeapNode* queue[100]; // Mảng tĩnh để lưu các node trong queue
    int front = 0, rear = 0; // Chỉ số đầu và cuối của queue
    queue[rear++] = root; // Thêm node gốc vào queue
    
    while (front < rear) { // Lặp cho đến khi queue rỗng
        HeapNode* cur = queue[front++]; // Lấy node đầu tiên trong queue
        if (!cur->left) { // Nếu không có con trái, chèn vào bên trái
            isLeft = true; // Cập nhật isLeft thành true
            return cur; // Trả về node hiện tại
        }
        if (!cur->right) {     // Nếu không có con phải, chèn vào bên phải
            isLeft = false; // Cập nhật isLeft thành false
            return cur; // Trả về node hiện tại
        }
        // Nếu node đã có đầy đủ 2 con, đẩy cả 2 vào queue
        queue[rear++] = cur->left; // Thêm con trái vào queue 
        queue[rear++] = cur->right; // Thêm con phải vào queue
    }
    return nullptr; // Trường hợp không xảy ra
}

// Hàm chèn một giá trị vào min-heap
HeapNode* insertMinHeap(HeapNode *root, int value) {
    if (!root) // Nếu cây rỗng thì tạo node mới và trả về
        return new HeapNode(value); 
    
    bool isLeft; // Biến để xác định vị trí chèn (trái hay phải)
    HeapNode* parent = findInsertPos(root, isLeft); // Tìm vị trí chèn mới
    HeapNode* newNode = new HeapNode(value); // Tạo node mới với giá trị value
    newNode->parent = parent; // Cập nhật cha cho node mới
    
    if (isLeft) // Nếu vị trí chèn là con trái thì gán con trái của parent là node mới
        parent->left = newNode; 
    else
        parent->right = newNode; // Nếu vị trí chèn là con phải thì gán con phải của parent là node mới
    
    bubbleUpMin(newNode); // Điều chỉnh vị trí cho đúng min-heap
    return root;
}

// Tìm node lá cuối cùng theo thứ tự level-order
HeapNode* findLastNode(HeapNode *root) {
    HeapNode* queue[100]; // Mảng tĩnh để lưu các node trong queue
    int front = 0, rear = 0; // Chỉ số đầu và cuối của queue
    HeapNode* last = nullptr; // Biến để lưu node lá cuối cùng
    queue[rear++] = root; // Thêm node gốc vào queue
    
    while (front < rear) { // Lặp cho đến khi queue rỗng
        last = queue[front++]; // Lấy node đầu tiên trong queue
        if (last->left) // Nếu node có con trái thì thêm con trái vào queue
            queue[rear++] = last->left; 
        if (last->right) // Nếu node có con phải thì thêm con phải vào queue
            queue[rear++] = last->right;
    }
    return last; // Trả về node lá cuối cùng
}

// Xóa node gốc (phần tử nhỏ nhất) của min-heap
HeapNode* deleteMinRoot(HeapNode* root) {
    if (!root) // Nếu cây rỗng thì không làm gì cả
        return nullptr;
    
    HeapNode* last = findLastNode(root); // Tìm node lá cuối cùng
    
    // Nếu chỉ có một node trong heap
    if (last == root) {
        delete root;
        return nullptr;
    }
    
    // Thay giá trị của node gốc bằng giá trị của node lá cuối
    root->data = last->data;
    
    // Loại bỏ node lá cuối khỏi cây
    HeapNode* par = last->parent;
    if (par->left == last) // Nếu node lá cuối là con trái của cha
        par->left = nullptr;
    else
        par->right = nullptr; // Nếu node lá cuối là con phải của cha
    
    delete last; // Giải phóng bộ nhớ cho node lá cuối
    
    bubbleDownMin(root); // Điều chỉnh lại min-heap
    return root; // Trả về gốc của min-heap
}

// Hàm in cây theo thứ tự level-order (dùng mảng tĩnh làm queue)
void printLevelOrder(HeapNode *root) {
    if (!root) // Nếu cây rỗng thì không làm gì cả
        return;
    
    HeapNode* queue[100]; // Mảng tĩnh để lưu các node trong queue
    int front = 0, rear = 0; // Chỉ số đầu và cuối của queue
    queue[rear++] = root; // Thêm node gốc vào queue
    
    while (front < rear) { // Lặp cho đến khi queue rỗng
        HeapNode* cur = queue[front++]; // Lấy node đầu tiên trong queue
        cout << cur->data << " "; // In giá trị của node hiện tại
        if (cur->left) // Nếu node có con trái thì thêm con trái vào queue
            queue[rear++] = cur->left;
        if (cur->right) // Nếu node có con phải thì thêm con phải vào queue
            queue[rear++] = cur->right;
    }
    cout << endl; // In dòng mới sau khi in xong cây
}

int main() {
    HeapNode* minRoot = nullptr;
    
    // Dữ liệu ban đầu
    int initial[] = {2, 1, 10, 6, 3, 8, 7, 13, 20}; // Dãy số ban đầu
    int n = sizeof(initial) / sizeof(initial[0]); // Tính số lượng phần tử trong dãy
    
    // Tạo min-heap từ dãy ban đầu
    for (int i = 0; i < n; i++) { // Lặp qua từng phần tử trong dãy
        minRoot = insertMinHeap(minRoot, initial[i]); // Chèn từng phần tử vào min-heap
    }
    cout << "Min-Heap sau khi khoi tao: ";
    printLevelOrder(minRoot);
    
    // Chèn thêm các giá trị: 14, 0, 35
    int add[] = {14, 0, 35}; // Mảng chứa các giá trị cần chèn
    int m = sizeof(add) / sizeof(add[0]); // Tính số lượng phần tử trong mảng add
    for (int i = 0; i < m; i++) { // Lặp qua từng phần tử trong mảng add
        minRoot = insertMinHeap(minRoot, add[i]); // Chèn từng phần tử vào min-heap
    }
    cout << "Min-Heap sau khi chen 14, 0, 35: ";
    printLevelOrder(minRoot);
    
    // Xóa gốc (phần tử nhỏ nhất) 3 lần
    for (int i = 0; i < 3; i++) { // Lặp 3 lần để xóa gốc
        minRoot = deleteMinRoot(minRoot); // Xóa gốc của min-heap
        cout << "Min-Heap sau khi xoa goc: "; 
        printLevelOrder(minRoot); // In cây sau khi xóa gốc
    }
    
    return 0;
}
