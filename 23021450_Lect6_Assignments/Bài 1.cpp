 
/*  Cây ban đầu:
 
         2
        / \
       1   10
          /  \
         6    13
        / \     \
       3   8     20
          /
         7
    Cây sau khi chèn 14, 0, 35:
     
             2
            / \
           1   10
          /   /  \
         0   6    13
            / \     \
           3   8     20
              /      / \
             7     14   35

    Cây sau khi xóa 6, 13, 35:

            2
           / \
          1   10
         /   /  \
        0   7    20
           / \   / 
          3   8 14
*/
#include <iostream>
using namespace std;

// Định nghĩa cấu trúc node của BST
struct Node {
    int data;  // Giá trị của node
    Node* left;  // Con trỏ đến node con bên trái
    Node* right; // Con trỏ đến node con bên phải
};

// Tạo một node mới với giá trị cho trước
Node* createNode(int value) {
    Node* newNode = new Node(); // Cấp phát bộ nhớ cho node mới
    newNode->data = value; // Gán giá trị cho node
    newNode->left = newNode->right = nullptr; // Khởi tạo con trỏ trái và phải là nullptr
    return newNode; // Trả về con trỏ đến node mới
}

// Hàm chèn giá trị vào BST (đệ quy)
Node* insert(Node* root, int value) {
    if (root == nullptr) { // Nếu cây rỗng, tạo node mới
        return createNode(value);
    }
    if (value < root->data) { // Nếu giá trị nhỏ hơn node gốc, chèn vào bên trái
        root->left = insert(root->left, value);
    } else if (value > root->data) { // Nếu lớn hơn, chèn vào bên phải
        root->right = insert(root->right, value);
    }
    // Nếu value đã có trong cây thì không chèn thêm
    return root; // Trả về node gốc sau khi chèn
}

// Hàm tìm node có giá trị nhỏ nhất (dùng cho trường hợp xóa node có 2 con)
Node* findMin(Node* root) {
    while (root && root->left != nullptr) { // Tìm node nhỏ nhất trong cây con bên trái
        root = root->left; 
    }
    return root; // Trả về node nhỏ nhất
}

// Hàm xóa một node có giá trị cho trước khỏi BST
Node* deleteNode(Node* root, int value) {
    if (root == nullptr) // Nếu cây rỗng thì thoát
        return root; // Không tìm thấy

    if (value < root->data) { // Nếu giá trị cần xóa nhỏ hơn node hiện tại, tìm bên trái
        root->left = deleteNode(root->left, value); // Đệ quy tìm bên trái
    } else if (value > root->data) { // Nếu lớn hơn, tìm bên phải
        root->right = deleteNode(root->right, value); // Đệ quy tìm bên phải
    } else {
        // Tìm thấy node cần xóa
        // TH1: Node không có con hoặc chỉ có 1 con
        if (root->left == nullptr && root->right == nullptr) { //// Nếu không có con nào
            delete root; // Giải phóng bộ nhớ
            return nullptr; // Trả về nullptr để xóa node
        } else if (root->left == nullptr) { // Nếu không có con trái
            Node* temp = root->right; // Lưu con phải
            delete root; // Giải phóng bộ nhớ
            return temp; // Trả về con phải
        } else if (root->right == nullptr) { // Nếu không có con phải
            Node* temp = root->left; // Lưu con trái
            delete root; // Giải phóng bộ nhớ
            return temp; // Trả về con trái
        } else {
            // TH2: Node có 2 con. Tìm node nhỏ nhất ở nhánh phải
            Node* temp = findMin(root->right);
            root->data = temp->data;                // Thay thế giá trị
            root->right = deleteNode(root->right, temp->data); // Xóa node thay thế
        }
    }
    return root; // Trả về node gốc sau khi xóa
}

// Duyệt cây theo thứ tự giữa (inorder)
void inorder(Node* root) { 
    if (root == nullptr) return; // Nếu cây rỗng thì thoát
    inorder(root->left); // Duyệt cây con bên trái
    cout << root->data << " ";  // In giá trị của node hiện tại
    inorder(root->right); // Duyệt cây con bên phải
}

void preorder(Node* root) { // Duyệt cây theo thứ tự tiền tố (preorder)
    if (root == nullptr) return; // Nếu cây rỗng thì thoát
    cout << root->data << " "; // In giá trị của node hiện tại
    preorder(root->left); // Duyệt cây con bên trái
    preorder(root->right); // Duyệt cây con bên phải
}

void postorder(Node* root) { // Duyệt cây theo thứ tự hậu tố (postorder)
    if (root == nullptr) return; // Nếu cây rỗng thì thoát
    postorder(root->left); // Duyệt cây con bên trái
    postorder(root->right); // Duyệt cây con bên phải
    cout << root->data << " "; // In giá trị của node hiện tại
}
int main() {
    Node* root = nullptr;
    
    // 1. Tạo BST từ dãy: 2, 1, 10, 6, 3, 8, 7, 13, 20
    int initial[] = {2, 1, 10, 6, 3, 8, 7, 13, 20};
    for (int i = 0; i < 9; i++) { // Chèn từng giá trị vào BST
        root = insert(root, initial[i]); 
    }
    cout << "BST ban dau: " << endl;
    cout << "Duyet theo thu tu tien to (preorder): ";
    preorder(root); // In ra cây theo thứ tự tiền tố    
    cout << endl;
    cout << "Duyet theo thu tu trung to (inorder): ";
    inorder(root);  // In ra cây theo thứ tự trung tố
    cout << endl;
    cout << "Duyet theo thu tu hau to (postorder): ";
    postorder(root); // In ra cây theo thứ tự hậu tố    
    cout << endl;
    
    // 2. Chèn thêm các giá trị: 14, 0, 35
    int add[] = {14, 0, 35};
    for (int i = 0; i < 3; i++) {  // Chèn từng giá trị vào BST
        root = insert(root, add[i]); 
    }
    cout << "BST sau khi chen 14, 0, 35: " << endl;
    cout << "Duyet theo thu tu tien to (preorder): ";
    preorder(root); // In ra cây theo thứ tự tiền tố
    cout << endl;
    cout << "Duyet theo thu tu trung to (inorder): ";
    inorder(root);  // In ra cây theo thứ tự trung tố
    cout << endl;
    cout << "Duyet theo thu tu hau to (postorder): ";
    postorder(root); // In ra cây theo thứ tự hậu tố
    cout << endl;
    
    // 3. Xóa các giá trị: 6, 13, 35
    int remove[] = {6, 13, 35}; // Các giá trị cần xóa
    for (int i = 0; i < 3; i++) { // Xóa từng giá trị khỏi BST
        root = deleteNode(root, remove[i]); 
    }
    cout << "BST sau khi xoa 6, 13, 35: " << endl;
    cout << "Duyet theo thu tu tien to (preorder): ";
    preorder(root); // In ra cây theo thứ tự tiền tố
    cout << endl;
    cout << "Duyet theo thu tu trung to (inorder): ";
    inorder(root); // In ra cây theo thứ tự trung tố
    cout << endl;
    cout << "Duyet theo thu tu hau to (postorder): ";
    postorder(root); // In ra cây theo thứ tự hậu tố
    cout << endl;
    return 0;
}
