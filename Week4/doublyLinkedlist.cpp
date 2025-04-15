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

// Tạo một nút mới với giá trị data
Node* createNode(int data) {
    Node* newNode = new Node;
    if (!newNode) return nullptr;
    newNode->key = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

//Khởi tạo danh sách rỗng
void initList(List& list) {
    list.pHead = nullptr;
    list.pTail = nullptr;
}

// Kiểm tra danh sách rỗng
bool isEmpty(const List& list) {
    return list.pHead == nullptr;
}

// Thêm nút vào đầu danh sách
void createHead(List& list, int data) {
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

// Thêm nút vào cuối danh sách
void createTail(List& list, int data) {
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

// Xóa nút đầu tiên
void removeHead(List& list) {
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

// Xóa nút cuối cùng
void removeTail(List& list) {
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

// Xóa nút có giá trị key
void removeKey(List& list, int key) {
    Node* current = list.pHead;

    while (current != nullptr && current->key != key) {
        current = current->next;
    }

    if (current == nullptr) return; // Không tìm thấy

    if (current == list.pHead) {
        removeHead(list);
        return;
    }

    if (current == list.pTail) {
        removeTail(list);
        return;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
}

// Tìm kiếm nút có giá trị key
Node* searchKey(const List& list, int key) {
    Node* current = list.pHead;
    while (current != nullptr) {
        if (current->key == key) return current;
        current = current->next;
    }
    return nullptr;
}

// Duyệt danh sách từ đầu đến cuối
void printListHeadtoTail(const List& list) {
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

// Duyệt danh sách từ cuối về đầu
void printListTailtoHead(const List& list) {
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

// Giải phóng bộ nhớ danh sách
void freeList(List& list) {
    while (!isEmpty(list)) {
        removeHead(list);
    }
}

void removeBefore(List& list, int val){
    if(isEmpty(list)){
        cout <<"Danh sach rong\n";
        return;
    }
    Node* curr = list.pHead;
    while(curr != nullptr && curr->key == val){
        curr = curr->next;
    }
    if(curr == nullptr || curr ->prev == nullptr){
        return;
    }
    Node* toDelete = curr->prev;

    if(toDelete->prev != nullptr){
        toDelete->prev->next = curr;
        curr->prev = toDelete->prev;
    } else{
        curr->prev = nullptr;
        list.pHead = curr;
    }
    delete toDelete;
    return;
}

void removeAfter(List& l, int val){
    if(isEmpty(l)){
        cout <<"Danh sach rong\n";
        return;
    }
    Node* curr = l.pHead;   
    while(curr != nullptr && curr->key != val){
        curr = curr->next;
    }
    if(curr == nullptr || curr->next == nullptr){
        return;
    }
    Node* toDelete = curr->next;
    
    if(toDelete->next != nullptr){
        toDelete->next->prev = curr;
        curr->next = toDelete->next;
    } else {
        curr->next = nullptr;
        l.pTail = curr;
    }
    delete toDelete;
    return;
}
 // Thêm nút tại vị trí pos
void addPos(List& l, int data, int val){
    if(isEmpty(l)){
        cout <<"Danh sach rong\n";
        return;
    }
    Node* curr = l.pHead;
    while(curr != nullptr && curr->key != val){
        curr = curr->next;
    }
    if(curr == nullptr){
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = curr->next;
    newNode->prev = curr;
    
    if(curr->next != nullptr){
        curr->next->prev = newNode;
    } else {
        l.pTail = newNode;
    }
    curr->next = newNode;
}

// Xóa nút tại vị trí pos
void removePos(List& l, int pos){
    if(isEmpty(l)){
        cout <<"Danh sach rong\n";
        return;
    }
    Node* curr = l.pHead;
    for(int i = 0; i < pos && curr != nullptr; i++){
        curr = curr->next;
    }
    if(curr == nullptr){
        return;
    }
    if(curr->prev != nullptr){
        curr->prev->next = curr->next;
    } else {
        l.pHead = curr->next;
    }
    if(curr->next != nullptr){
        curr->next->prev = curr->prev;
    } else {
        l.pTail = curr->prev;
    }
    delete curr;
}

//Thêm data trước node có giá trị val
void addBefore(List& l, int data, int val){
    if(isEmpty(l)){
        cout <<"Danh sach rong\n";
        return;
    }
    Node* curr = l.pHead;
    while(curr != nullptr && curr->key != val){
        curr = curr->next;
    }
    if(curr == nullptr){
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = curr;
    newNode->prev = curr->prev;   
    if(curr->prev != nullptr){
        curr->prev->next = newNode;
    } else {
        l.pHead = newNode;
    }
    curr->prev = newNode;
}

//Thêm data sau node có giá trị val
void addAfter(List& l, int data, int val){
    if(isEmpty(l)){
        cout <<"Danh sach rong\n";
        return;
    }
    Node* curr = l.pHead;
    while(curr != nullptr && curr->key != val){
        curr = curr->next;
    }
    if(curr == nullptr){
        return;
    }
    Node* newNode = createNode(data);
    newNode->prev = curr;
    newNode->next = curr->next;   
    if(curr->next != nullptr){
        curr->next->prev = newNode;
    } else {
        l.pTail = newNode;
    }
    curr->next = newNode;
}

// Đếm số lượng nút trong danh sách
int countElements(const List& list) {
    int size = 0;
    Node* current = list.pHead;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}

// Xóa phần tử trùng
void removeDuplicates(List& list) {
    if (isEmpty(list)) return;
    Node* current = list.pHead;
    while (current != nullptr) {
        Node* runner = current->next;
        while (runner != nullptr) {
            if (runner->key == current->key) {
                Node* toDelete = runner;
                runner = runner->next;
                removeKey(list, toDelete->key);
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

// Xóa tất cả phần tử có giá trị key
void removeElements(List& list, int key) {
    if (isEmpty(list)) return;
    Node* current = list.pHead;
    while (current != nullptr) {
        if (current->key == key) {
            Node* toDelete = current;
            current = current->next;
            removeKey(list, toDelete->key);
        } else {
            current = current->next;
        }
    }
}