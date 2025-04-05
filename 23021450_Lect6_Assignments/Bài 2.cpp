/*
Cây ban đầu:

                 20
               /    \
             13      8
            /  \    / \
          10   3   2   7
         /  \
        1    6

Cây sau khi chèn 14, 0, 35:

                 35
               /    \
             14      20
            /  \    /  \
          10   13  8    7
         / \   / \
        1  6  3  0
            /
           2

Cây sau khi xóa 6, 13, 35:

           20
          /   \
        14     8
       /  \   / \
     10   3  0   7
    / \
   1   2
*/



#include <iostream>
using namespace std;

// Cấu trúc node cho max-heap
struct HeapNode { 
    int data; // giá trị của node
    HeapNode *left, *right, *parent; // con trái, con phải, cha
    
    HeapNode(int val) { //khởi tạo node với giá trị val 
        data = val; 
        left = right = parent = nullptr; 
    }

    HeapNode () { //khởi tạo node không có giá trị
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

// Bubble-up: nếu node có giá trị lớn hơn parent, đổi chỗ
void bubbleUp(HeapNode *node) {
    while (node->parent && node->data > node->parent->data) { // kiểm tra nếu node có cha và giá trị lớn hơn cha
        swap(node->data, node->parent->data); // hoán đổi giá trị
        node = node->parent; // cập nhật node thành cha của nó
    }
}

// Bubble-down: sau khi thay đổi giá trị, đổi chỗ với con lớn nhất nếu cần
void bubbleDown(HeapNode *node) {
    while (true) { // lặp cho đến khi không còn cần đổi chỗ
        HeapNode *largest = node; // giả định node là lớn nhất
        if (node->left && node->left->data > largest->data) // so sánh với con trái
            largest = node->left; // nếu con trái lớn hơn node thì cập nhật largest
        if (node->right && node->right->data > largest->data) // so sánh với con phải
            largest = node->right; // nếu con phải lớn hơn largest thì cập nhật largest
        if (largest == node) // // nếu largest không thay đổi thì không cần đổi chỗ nữa
            break;
        swap(node->data, largest->data); // hoán đổi giá trị giữa node và largest
        node = largest; // cập nhật node thành largest để tiếp tục kiểm tra
    }
}

// Tìm vị trí chèn mới theo thứ tự level-order (dùng mảng tĩnh làm queue)
HeapNode* findInsertPos(HeapNode *root, bool &isLeft) {
    HeapNode* queue[100]; // mảng tĩnh để lưu các node trong queue
    int front = 0, rear = 0; // chỉ số đầu và cuối của queue
    queue[rear++] = root; // thêm node gốc vào queue
    while (front < rear) { // lặp cho đến khi queue rỗng
        HeapNode* cur = queue[front++]; // lấy node đầu tiên trong queue
        if (!cur->left) { // nếu node không có con trái thì vị trí chèn là con trái
            isLeft = true; // cập nhật isLeft thành true
            return cur; // trả về node hiện tại
        }
        if (!cur->right) { // nếu node không có con phải thì vị trí chèn là con phải
            isLeft = false; // cập nhật isLeft thành false
            return cur; // trả về node hiện tại 
        }
        queue[rear++] = cur->left; // thêm con trái vào queue
        queue[rear++] = cur->right; // thêm con phải vào queue
    }
    return nullptr; // không xảy ra
}

// Hàm chèn một giá trị vào max-heap
HeapNode* insertHeap(HeapNode *root, int value) {
    if (!root) // nếu cây rỗng thì tạo node mới và trả về
        return new HeapNode(value);
    
    bool isLeft; // biến để xác định vị trí chèn (trái hay phải)
    HeapNode* parent = findInsertPos(root, isLeft); // tìm vị trí chèn mới
    HeapNode* newNode = new HeapNode(value); // tạo node mới với giá trị value
    newNode->parent = parent; // cập nhật cha cho node mới
    if (isLeft) // nếu vị trí chèn là con trái thì gán con trái của parent là node mới
        parent->left = newNode;
    else
        parent->right = newNode; // nếu vị trí chèn là con phải thì gán con phải của parent là node mới
    
    bubbleUp(newNode); // gọi hàm bubbleUp để đảm bảo max-heap property
    return root; // trả về gốc của max-heap
}

// Tìm node lá cuối cùng theo thứ tự level-order
HeapNode* findLastNode(HeapNode *root) {
    HeapNode* queue[100]; // mảng tĩnh để lưu các node trong queue
    int front = 0, rear = 0; // chỉ số đầu và cuối của queue
    HeapNode* last = nullptr; // biến để lưu node lá cuối cùng
    queue[rear++] = root; // thêm node gốc vào queue
    while (front < rear) { // lặp cho đến khi queue rỗng
        last = queue[front++]; // lấy node đầu tiên trong queue
        if (last->left) // nếu node có con trái thì thêm con trái vào queue
            queue[rear++] = last->left; 
        if (last->right) // nếu node có con phải thì thêm con phải vào queue
            queue[rear++] = last->right;
    }
    return last; // trả về node lá cuối cùng
}

// Xóa phần tử lớn nhất (node gốc) của max-heap
HeapNode* deleteRoot(HeapNode* root) {
    if (!root) // nếu cây rỗng thì không làm gì cả
        return nullptr;
    
    // Tìm node lá cuối cùng
    HeapNode* last = findLastNode(root); // gọi hàm tìm node lá cuối cùng
    
    // Nếu chỉ có một node
    if (last == root) { // nếu node lá cuối cùng là gốc thì xóa gốc và trả về nullptr
        delete root;
        return nullptr;
    }
    
    // Thay giá trị gốc bằng giá trị của node lá cuối
    root->data = last->data;
    
    // Loại bỏ node lá cuối ra khỏi cây
    HeapNode* par = last->parent; // lưu cha của node lá cuối
    if (par->left == last) // nếu node lá cuối là con trái của cha thì gán con trái của cha là nullptr
        par->left = nullptr;
    else
        par->right = nullptr; // nếu node lá cuối là con phải của cha thì gán con phải của cha là nullptr
    delete last; // xóa node lá cuối
    
    bubbleDown(root); // gọi hàm bubbleDown để đảm bảo max-heap property
    return root; // trả về gốc của max-heap
}

// In cây theo thứ tự level-order
void printLevelOrder(HeapNode *root) {
    if (!root) // nếu cây rỗng thì không làm gì cả
        return;
    HeapNode* queue[100]; // mảng tĩnh để lưu các node trong queue
    int front = 0, rear = 0; // chỉ số đầu và cuối của queue
    queue[rear++] = root; // thêm node gốc vào queue
    while (front < rear) { // lặp cho đến khi queue rỗng
        HeapNode* cur = queue[front++]; // lấy node đầu tiên trong queue
        cout << cur->data << " "; // in giá trị của node hiện tại
        if (cur->left) // nếu node có con trái thì thêm con trái vào queue
            queue[rear++] = cur->left;
        if (cur->right)
            queue[rear++] = cur->right; // nếu node có con phải thì thêm con phải vào queue
    }
    cout << endl;
}

int main() {
    HeapNode* root = nullptr; // khởi tạo cây rỗng
    
    // 1. Tạo max-heap từ dãy: 2, 1, 10, 6, 3, 8, 7, 13, 20
    int initial[] = {2, 1, 10, 6, 3, 8, 7, 13, 20};
    for (int i = 0; i < 9; i++) {
        root = insertHeap(root, initial[i]); // chèn từng giá trị vào max-heap
    }
    cout << "Heap sau khi khoi tao: ";
    printLevelOrder(root);
    
    // 2. Chèn thêm các giá trị: 14, 0, 35
    int add[] = {14, 0, 35}; // mảng chứa các giá trị cần chèn
    for (int i = 0; i < 3; i++) {
        root = insertHeap(root, add[i]); // chèn từng giá trị vào max-heap
    }
    cout << "Heap sau khi chen 14, 0, 35: ";
    printLevelOrder(root);
    
    // 3. Xóa gốc (phần tử lớn nhất) 3 lần
    for (int i = 0; i < 3; i++) {
        root = deleteRoot(root); // xóa gốc của max-heap
        cout << "Heap sau khi xoa goc: ";
        printLevelOrder(root); 
    }
    
    return 0;
}
