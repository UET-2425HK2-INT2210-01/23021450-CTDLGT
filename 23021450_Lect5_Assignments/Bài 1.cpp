#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* firstChild;
    Node* nextSibling;
};

// Hàm tạo node mới với giá trị data
Node* createNode(int data) {
    Node* node = new Node;
    node->data = data;
    node->firstChild = NULL;
    node->nextSibling = NULL;
    return node;
}

// Hàm thêm con cho node cha
void addChild(Node* parent, Node* child) {
    // Nếu node cha chưa có con: gán là con đầu tiên
    if (parent->firstChild == NULL) {
        parent->firstChild = child;
    } else { //Ngược lại duyệt hết tất cả các con -> thêm vào làm con ở cuối
        Node* temp = parent->firstChild;
        while (temp->nextSibling != NULL) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
}
// Hàm tính chiều cao của cây.
int treeHeight(Node* root) {
    // Nếu gốc rỗng thì in ra -1
    if (root == NULL)
        return -1;
    int maxChildHeight = -1;
    // Duyệt qua danh sách con
    for (Node* child = root->firstChild; child != NULL; child = child->nextSibling) {
        int h = treeHeight(child);
        // Nếu chiều cao của con lớn hơn chiều cao lớn nhất: gán chiều cao lớn nhất bằng chiều cao của con
        if (h > maxChildHeight)
            maxChildHeight = h;
    }
    // Trả về giá trị chiều cao lớn nhất + 1
    return maxChildHeight + 1;
}

// Duyệt trước (Preorder): Ghi nút hiện tại -> duyệt các con
void preorder(Node* root) {
    if (root == NULL)
        return;
    cout << root->data << " ";
    for (Node* child = root->firstChild; child != NULL; child = child->nextSibling) {
        preorder(child);
    }
}

// Duyệt sau (Postorder): Duyệt các con -> ghi nút hiện tại
void postorder(Node* root) {
    if (root == NULL)
        return;
    for (Node* child = root->firstChild; child != NULL; child = child->nextSibling) {
        postorder(child);
    }
    cout << root->data << " ";
}

// Duyệt giữa (Inorder) áp dụng cho cây nhị phân
void inorder(Node* root) {
    if (root == NULL)
        return;
    // Đếm số con của nút hiện tại
    int count = 0;
    Node* left = NULL;
    Node* right = NULL;
    if (root->firstChild != NULL) {
        left = root->firstChild;
        count++;
        if (left->nextSibling != NULL) {
            right = left->nextSibling;
            count++;
        }
    }
    // Nếu nút có 0 con: in nút đó
    if (count == 0) {
        cout << root->data << " ";
    } else if (count == 1) {             // Nếu có 1 con: duyệt con trái -> in nút hiện tại
        inorder(left);
        cout << root->data << " ";
    } else if (count == 2) {          // Nếu có 2 con: duyệt con trái -> in nút hiện tại -> duyệt con phải
        inorder(left);
        cout << root->data << " ";
        inorder(right);
    }
}
// Hàm kiểm tra xem cây có phải là cây nhị phân không
bool isBinary(Node* root) {
    if (root == NULL)
        return true;
    int count = 0;
    for (Node* child = root->firstChild; child != NULL; child = child->nextSibling) {
        count++;
    }
    if (count > 2)
        return false;
    for (Node* child = root->firstChild; child != NULL; child = child->nextSibling) {
        if (!isBinary(child))
            return false;
    }
    return true;
}

int main(){
    int N, M;
    cin >> N >> M;

    // Tạo mảng các node (đánh số từ 1 đến N)
    Node** nodes = new Node*[N + 1];
    for (int i = 1; i <= N; i++) {
        nodes[i] = createNode(i);
    }

    // Tạo mảng hasParent đánh dấu xem một node có là con của node khác hay không
    bool* hasParent = new bool[N + 1];
    for (int i = 1; i <= N; i++) {
        hasParent[i] = false;         //Ban đầu đánh dấu tất cả giá trị đều là false
    }

    // Xây dựng cây từ M cạnh nhập vào (u là cha của v)
    for (int i = 0; i < M; i++){
        int u, v;
        cin >> u >> v;
        addChild(nodes[u], nodes[v]);
        hasParent[v] = true;
    }

    // Tìm nút gốc (node không có cha)
    Node* root = NULL;
    for (int i = 1; i <= N; i++){
        if (!hasParent[i]){
            root = nodes[i];
            break;
        }
    }

    // Tính chiều cao của cây
    int height = treeHeight(root);
    cout << height << "\n";

    // Duyệt cây theo thứ tự Preorder
    preorder(root);
    cout << "\n";

    // Duyệt cây theo thứ tự Postorder
    postorder(root);
    cout << "\n";

    // Nếu cây là cây nhị phân thì duyệt theo Inorder, nếu không thì in "NOT BINARY TREE"
    if (isBinary(root)) {
        inorder(root);
        cout << "\n";
    } else {
        cout << "NOT BINARY TREE" << "\n";
    }

    // Giải phóng bộ nhớ
    delete[] nodes;
    delete[] hasParent;

    return 0;
}
