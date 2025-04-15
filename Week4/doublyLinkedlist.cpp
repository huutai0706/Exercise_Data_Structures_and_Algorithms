#include <iostream>
#include <cassert>
using namespace std;

struct Node {
    int key;
    Node* next;
    Node* prev;
};

struct List {
    Node* pHead;
    Node* pTail;
};

// 1. Tạo một nút mới với giá trị data
Node* createNode(int data) {
    Node* newNode = new Node;
    if (!newNode) return nullptr;
    newNode->key = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

// 2. Khởi tạo danh sách rỗng
void initList(List& list) {
    list.pHead = nullptr;
    list.pTail = nullptr;
}

// 3. Kiểm tra danh sách rỗng
bool isEmpty(const List& list) {
    return list.pHead == nullptr;
}

// 4. Thêm nút vào đầu danh sách
void insertHead(List& list, int data) {
    Node* newNode = createNode(data);
    if (!newNode) return;

    if (isEmpty(list)) {
        list.pHead = list.pTail = newNode;
    } else {
        newNode->next = list.pHead;
        list.pHead->prev = newNode;
        list.pHead = newNode;
    }
}

// 5. Thêm nút vào cuối danh sách
void insertTail(List& list, int data) {
    Node* newNode = createNode(data);
    if (!newNode) return;

    if (isEmpty(list)) {
        list.pHead = list.pTail = newNode;
    } else {
        list.pTail->next = newNode;
        newNode->prev = list.pTail;
        list.pTail = newNode;
    }
}

// 6. Xóa nút đầu tiên
void deleteHead(List& list) {
    if (isEmpty(list)) return;

    Node* temp = list.pHead;
    list.pHead = list.pHead->next;

    if (list.pHead == nullptr) {
        list.pTail = nullptr;
    } else {
        list.pHead->prev = nullptr;
    }

    delete temp;
}

// 7. Xóa nút cuối cùng
void deleteTail(List& list) {
    if (isEmpty(list)) return;

    Node* temp = list.pTail;
    list.pTail = list.pTail->prev;

    if (list.pTail == nullptr) {
        list.pHead = nullptr;
    } else {
        list.pTail->next = nullptr;
    }

    delete temp;
}

// 8. Xóa nút có giá trị key
void deleteKey(List& list, int key) {
    Node* current = list.pHead;

    while (current != nullptr && current->key != key) {
        current = current->next;
    }

    if (current == nullptr) return; // Không tìm thấy

    if (current == list.pHead) {
        deleteHead(list);
        return;
    }

    if (current == list.pTail) {
        deleteTail(list);
        return;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
}

// 9. Tìm kiếm nút có giá trị key
Node* searchKey(const List& list, int key) {
    Node* current = list.pHead;
    while (current != nullptr) {
        if (current->key == key) return current;
        current = current->next;
    }
    return nullptr;
}

// 10. Duyệt danh sách từ đầu đến cuối
void printListForward(const List& list) {
    if (isEmpty(list)) {
        cout << "Danh sach rong\n";
        return;
    }

    Node* current = list.pHead;
    while (current != nullptr) {
        cout << current->key << " ";
        current = current->next;
    }
    cout << endl;
}

// 11. Duyệt danh sách từ cuối về đầu
void printListBackward(const List& list) {
    if (isEmpty(list)) {
        cout << "Danh sach rong\n";
        return;
    }

    Node* current = list.pTail;
    while (current != nullptr) {
        cout << current->key << " ";
        current = current->prev;
    }
    cout << endl;
}

// 12. Giải phóng bộ nhớ danh sách
void freeList(List& list) {
    while (!isEmpty(list)) {
        deleteHead(list);
    }
}

// Hàm main để thử nghiệm
int main() {
    List list;
    initList(list);

    // Tạo danh sách mẫu: 5 -> 10 -> 15 -> 20
    insertTail(list, 5);
    insertTail(list, 10);
    insertTail(list, 15);
    insertTail(list, 20);

    cout << "Danh sach tu dau den cuoi: ";
    printListForward(list); // Output: 5 10 15 20

    cout << "Danh sach tu cuoi ve dau: ";
    printListBackward(list); // Output: 20 15 10 5

    // Thêm 0 vào đầu
    insertHead(list, 0);
    cout << "Sau khi them 0 vao dau: ";
    printListForward(list); // Output: 0 5 10 15 20

    // Xóa phần tử 10
    deleteKey(list, 10);
    cout << "Sau khi xoa 10: ";
    printListForward(list); // Output: 0 5 15 20

    // Tìm kiếm phần tử 15
    Node* found = searchKey(list, 15);
    if (found) {
        cout << "Tim thay phan tu co gia tri 15\n";
    } else {
        cout << "Khong tim thay phan tu co gia tri 15\n";
    }

    // Giải phóng danh sách
    freeList(list);
    cout << "Sau khi giai phong: ";
    printListForward(list); // Output: Danh sach rong

    return 0;
}