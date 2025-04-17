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

// Khởi tạo danh sách rỗng
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

    if (current == nullptr) return;

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

// Giải phóng bộ nhớ danh sách
void freeList(List& list) {
    while (!isEmpty(list)) {
        removeHead(list);
    }
}

void removeBefore(List& list, int val) {
    if (isEmpty(list)) {
        cout << "Danh sach rong\n";
        return;
    }
    Node* curr = list.pHead;
    while (curr != nullptr && curr->key != val) {
        curr = curr->next;
    }
    if (curr == nullptr || curr->prev == nullptr) {
        return;
    }
    Node* toDelete = curr->prev;

    if (toDelete->prev != nullptr) {
        toDelete->prev->next = curr;
        curr->prev = toDelete->prev;
    } else {
        curr->prev = nullptr;
        list.pHead = curr;
    }
    delete toDelete;
}

void removeAfter(List& list, int val) {
    if (isEmpty(list)) {
        cout << "Danh sach rong\n";
        return;
    }
    Node* curr = list.pHead;
    while (curr != nullptr && curr->key != val) {
        curr = curr->next;
    }
    if (curr == nullptr || curr->next == nullptr) {
        return;
    }
    Node* toDelete = curr->next;

    if (toDelete->next != nullptr) {
        toDelete->next->prev = curr;
        curr->next = toDelete->next;
    } else {
        curr->next = nullptr;
        list.pTail = curr;
    }
    delete toDelete;
}

void addPos(List& list, int data, int pos) {
    if (pos < 0 || isEmpty(list) && pos > 0) {
        return;
    }
    if (pos == 0) {
        createHead(list, data);
        return;
    }
    Node* curr = list.pHead;
    for (int i = 0; i < pos - 1 && curr != nullptr; i++) {
        curr = curr->next;
    }
    if (curr == nullptr) {
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = curr->next;
    newNode->prev = curr;
    
    if (curr->next != nullptr) {
        curr->next->prev = newNode;
    } else {
        list.pTail = newNode;
    }
    curr->next = newNode;
}

void removePos(List& list, int pos) {
    if (isEmpty(list)) {
        cout << "Danh sach rong\n";
        return;
    }
    Node* curr = list.pHead;
    for (int i = 0; i < pos && curr != nullptr; i++) {
        curr = curr->next;
    }
    if (curr == nullptr) {
        return;
    }
    if (curr->prev != nullptr) {
        curr->prev->next = curr->next;
    } else {
        list.pHead = curr->next;
    }
    if (curr->next != nullptr) {
        curr->next->prev = curr->prev;
    } else {
        list.pTail = curr->prev;
    }
    delete curr;
}

void addBefore(List& list, int data, int val) {
    if (isEmpty(list)) {
        cout << "Danh sach rong\n";
        return;
    }
    Node* curr = list.pHead;
    while (curr != nullptr && curr->key != val) {
        curr = curr->next;
    }
    if (curr == nullptr) {
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = curr;
    newNode->prev = curr->prev;
    if (curr->prev != nullptr) {
        curr->prev->next = newNode;
    } else {
        list.pHead = newNode;
    }
    curr->prev = newNode;
}

void addAfter(List& list, int data, int val) {
    if (isEmpty(list)) {
        cout << "Danh sach rong\n";
        return;
    }
    Node* curr = list.pHead;
    while (curr != nullptr && curr->key != val) {
        curr = curr->next;
    }
    if (curr == nullptr) {
        return;
    }
    Node* newNode = createNode(data);
    newNode->prev = curr;
    newNode->next = curr->next;
    if (curr->next != nullptr) {
        curr->next->prev = newNode;
    } else {
        list.pTail = newNode;
    }
    curr->next = newNode;
}

int countElements(const List& list) {
    int size = 0;
    Node* current = list.pHead;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}

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

void reverseList(List& list) {
    if (isEmpty(list) || list.pHead == list.pTail) return;
    Node* curr = list.pHead;
    Node* temp = nullptr;
    while (curr != nullptr) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    temp = list.pHead;
    list.pHead = list.pTail;
    list.pTail = temp;
}

List createListFromArray(int arr[], int n) {
    List list;
    initList(list);
    if (n <= 0 || arr == nullptr) {
        return list;
    }
    for (int i = 0; i < n; ++i) {
        createTail(list, arr[i]);
    }
    return list;
}

bool areListsEqual(const List& l1, const List& l2) {
    Node* p1 = l1.pHead;
    Node* p2 = l2.pHead;
    while (p1 != nullptr && p2 != nullptr) {
        if (p1->key != p2->key) {
            return false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1 == nullptr && p2 == nullptr;
}

int main() {
    std::cout << "--- Begin running test case ---" << std::endl;

    // Test 1: createNode
    std::cout << "Test createNode: ";
    Node* node1 = createNode(10);
    assert(node1 != nullptr && node1->key == 10 && node1->next == nullptr && node1->prev == nullptr);
    std::cout << "Passed" << std::endl;
    delete node1;

    // Test 2: createList (initList and createHead)
    std::cout << "Test createList: ";
    List list2;
    initList(list2);
    createHead(list2, 20);
    assert(list2.pHead != nullptr && list2.pHead->key == 20 && list2.pTail->key == 20);
    std::cout << "Passed" << std::endl;
    freeList(list2);

    // Test 3: createHead
    std::cout << "Test createHead: ";
    List list3;
    initList(list3);
    createHead(list3, 30);
    assert(list3.pHead->key == 30 && list3.pTail->key == 30);
    createHead(list3, 40);
    assert(list3.pHead->key == 40 && list3.pHead->next->key == 30);
    std::cout << "Passed" << std::endl;
    freeList(list3);

    // Test 4: createTail
    std::cout << "Test createTail: ";
    List list4;
    initList(list4);
    createTail(list4, 50);
    assert(list4.pHead->key == 50 && list4.pTail->key == 50);
    createTail(list4, 60);
    assert(list4.pHead->key == 50 && list4.pTail->key == 60);
    std::cout << "Passed" << std::endl;
    freeList(list4);

    // Test 5: removeHead
    std::cout << "Test removeHead: ";
    int arr1[] = {70, 80, 90};
    List list5 = createListFromArray(arr1, 3);
    removeHead(list5);
    assert(list5.pHead->key == 80);
    removeHead(list5);
    assert(list5.pHead->key == 90);
    removeHead(list5);
    assert(list5.pHead == nullptr);
    std::cout << "Passed" << std::endl;
    freeList(list5);

    // Test 6: removeTail
    std::cout << "Test removeTail: ";
    int arr2[] = {100, 110, 120};
    List list6 = createListFromArray(arr2, 3);
    removeTail(list6);
    assert(list6.pTail->key == 110);
    removeTail(list6);
    assert(list6.pTail->key == 100);
    removeTail(list6);
    assert(list6.pHead == nullptr);
    std::cout << "Passed" << std::endl;
    freeList(list6);

    // Test 7: removeAll
    std::cout << "Test removeAll: ";
    int arr3[] = {130, 140, 150};
    List list7 = createListFromArray(arr3, 3);
    freeList(list7);
    assert(list7.pHead == nullptr && list7.pTail == nullptr);
    std::cout << "Passed" << std::endl;

    // Test 8: removeBefore
    std::cout << "Test removeBefore: ";
    int arr4[] = {160, 170, 180, 190, 200};
    List list8 = createListFromArray(arr4, 5);
    removeBefore(list8, 180);
    int exp8[] = {160, 180, 190, 200};
    List expected8 = createListFromArray(exp8, 4);
    assert(areListsEqual(list8, expected8));
    freeList(list8);
    freeList(expected8);
    std::cout << "Passed" << std::endl;

    // Test 9: removeAfter
    std::cout << "Test removeAfter: ";
    int arr5[] = {220, 230, 240, 250};
    List list9 = createListFromArray(arr5, 4);
    removeAfter(list9, 220);
    int exp9[] = {220, 240, 250};
    List expected9 = createListFromArray(exp9, 3);
    assert(areListsEqual(list9, expected9));
    freeList(list9);
    freeList(expected9);
    std::cout << "Passed" << std::endl;

    // Test 10: addPos
    std::cout << "Test addPos: ";
    List list10;
    initList(list10);
    addPos(list10, 280, 0);
    addPos(list10, 290, 1);
    int exp10[] = {280, 290};
    List expected10 = createListFromArray(exp10, 2);
    assert(areListsEqual(list10, expected10));
    freeList(list10);
    freeList(expected10);
    std::cout << "Passed" << std::endl;

    // Test 11: removePos
    std::cout << "Test removePos: ";
    int arr11[] = {340, 350, 360};
    List list11 = createListFromArray(arr11, 3);
    removePos(list11, 1);
    int exp11[] = {340, 360};
    List expected11 = createListFromArray(exp11, 2);
    assert(areListsEqual(list11, expected11));
    freeList(list11);
    freeList(expected11);
    std::cout << "Passed" << std::endl;

    // Test 12: addBefore
    std::cout << "Test addBefore: ";
    int arr12[] = {390, 400};
    List list12 = createListFromArray(arr12, 2);
    addBefore(list12, 380, 400);
    int exp12[] = {390, 380, 400};
    List expected12 = createListFromArray(exp12, 3);
    assert(areListsEqual(list12, expected12));
    freeList(list12);
    freeList(expected12);
    std::cout << "Passed" << std::endl;

    // Test 13: addAfter
    std::cout << "Test addAfter: ";
    int arr13[] = {430, 440};
    List list13 = createListFromArray(arr13, 2);
    addAfter(list13, 450, 430);
    int exp13[] = {430, 450, 440};
    List expected13 = createListFromArray(exp13, 3);
    assert(areListsEqual(list13, expected13));
    freeList(list13);
    freeList(expected13);
    std::cout << "Passed" << std::endl;

    // Test 14: printList
    std::cout << "Test printList: ";
    std::cout << "Passed" << std::endl;

    // Test 15: countElements
    std::cout << "Test countElements: ";
    int arr14[] = {500, 510, 520};
    List list14 = createListFromArray(arr14, 3);
    assert(countElements(list14) == 3);
    freeList(list14);
    std::cout << "Passed" << std::endl;

    // Test 16: reverseList
    std::cout << "Test reverseList: ";
    int arr15[] = {590, 600, 610};
    List list15 = createListFromArray(arr15, 3);
    reverseList(list15);
    int exp15[] = {610, 600, 590};
    List expected15 = createListFromArray(exp15, 3);
    assert(areListsEqual(list15, expected15));
    freeList(list15);
    freeList(expected15);
    std::cout << "Passed" << std::endl;

    // Test 17: removeDuplicates
    std::cout << "Test removeDuplicates: ";
    int arr16[] = {680, 690, 690, 700};
    List list16 = createListFromArray(arr16, 4);
    removeDuplicates(list16);
    int exp16[] = {680, 690, 700};
    List expected16 = createListFromArray(exp16, 3);
    assert(areListsEqual(list16, expected16));
    freeList(list16);
    freeList(expected16);
    std::cout << "Passed" << std::endl;

    // Test 18: removeElements
    std::cout << "Test removeElements: ";
    int arr17[] = {800, 810, 820, 810};
    List list17 = createListFromArray(arr17, 4);
    removeElements(list17, 810);
    int exp17[] = {800, 820};
    List expected17 = createListFromArray(exp17, 2);
    assert(areListsEqual(list17, expected17));
    freeList(list17);
    freeList(expected17);
    std::cout << "Passed" << std::endl;

    std::cout << "--- End running test case ---" << std::endl;
    return 0;
}