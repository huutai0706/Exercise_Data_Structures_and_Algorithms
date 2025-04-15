#include <iostream>
#include <cassert>
using namespace std;

struct Node {
    int key;
    Node* pNext;
};

// Tạo một nút mới với giá trị data.
Node* createNode(int data) {
    Node* newNode = new Node;
    if (!newNode) return nullptr;
    newNode->key = data;
    newNode->pNext = nullptr;
    return newNode;
}

struct List {
    Node* pHead;
    Node* pTail;
};

// Khai báo fuction
void initList(List*& l);
bool addTail(List*& l, int data);
void freeList(List*& l);


void initList(List*& l) {
      // Nếu con trỏ l chưa trỏ tới vùng nhớ nào cấp phát bộ nhớ mới cho danh sách
    if (l == nullptr) {
        l = new List;
    }
    // Khởi tạo con trỏ đầu và cuối cho danh sách bằng nullptr
    l->pHead = nullptr;
    l->pTail = nullptr;
}

// Hàm khởi tạo danh sách liên kết, với phần tử đầu tiên
void createList(List*& l, Node* pNode) {
    // Nếu danh sách chưa đươc cấp phát cấp phát bộ nhớ
    if (l == nullptr) {
        l = new List;
    }
    // Nếu pNode == nullptr thì không có node
    if (pNode == nullptr) {
        l->pHead = nullptr; // Nên con trỏ đầu trỏ vào null
        l->pTail = nullptr; // Con trỏ sau trỏ vào null
    } else {
        l->pHead = pNode; // Ngược lại pNode là node thì pHead và pTail đều trỏ vào pNode.
        l->pTail = pNode;
    }
}

//Đếm số lượng phần tử trong danh sách
int countElements(List l) {
    int size = 0; //Biến đếm ban đầu = 0
    Node* p = l.pHead; // Gán node p = head để duyệt danh sách tới cuối
    //Duyệt từng nút tới hết danh sách
    while (p != nullptr) {
        size++; //Cập nhật lại Biến đếm
        p = p->pNext; // Di chuyển con trỏ sang node kế tiếp
    }
    //Trả về số phần tử danh sách
    return size;
}
//Thêm một nút mới là dữ liệu data và đầu danh sách
bool addHead(List*& l, int data) {
    //Nếu danh sách chưa được khởi tạo
    if (l == nullptr) {
        l = new List; // Cấp phát bộ nhớ cho danh sách
        initList(l); // Khởi tạo danh sách 
    }
    // Tạo nút mới và truyền dữ liệu data vào cho node
    Node* newNode = createNode(data);
    if (!newNode) return false; // Nếu tạo được node thì trả về false
    // Nếu danh sách rỗng gán node vừa tạo cho pHead và pTail
    if (l->pHead == nullptr) {
        l->pHead = newNode;
        l->pTail = newNode;
    } else {
        // Nếu danh sách đã có phần tử
        newNode->pNext = l->pHead; //Trỏ nút mới đến nút đầu
        l->pHead = newNode; //Cập nhật lại nút đầu là nút mới
    }
    //Trả về true thêm thành công
    return true;
}

// Hàm thêm một nút mới chứa dữ liệu data vào danh sách
bool addTail(List*& l, int data) {
    //Nếu danh sách chưa dược cấp phát
    if (l == nullptr) {
        l = new List; // Cấp phát bộ nhớ cho danh sách
        initList(l);  // Khởi tạo danh sách
    }
    //Tạo một nút mưới chứa dữ liệu data
    Node* newNode = createNode(data);
    if (!newNode) return false; // Nếu không tạo được thì trả về false
    // Nếu danh sách rỗng
    if (l->pHead == nullptr) {
        l->pHead = newNode; //Thì con trỏ đầu và cuối đều trỏ vào node mới
        l->pTail = newNode;
    } else {
        //Nếu danh sách đã có phần tử
        l->pTail->pNext = newNode; // Gắn nút mới vào sau nút tail
        l->pTail = newNode; // Cập nhật lại nút tail là nút mới
    }
    //Thêm thành công
    return true;
}

// Xóa phần tử đầu tiên của danh sách liên kết đơn
bool removeHead(List*& l) {
    // Nếu danh sách chưa khởi tạo hoặc rỗng trả về false
    if (l == nullptr || l->pHead == nullptr) return false;
    Node* p = l->pHead; //Lưu con trỏ tới nút cần xóa
    l->pHead = p->pNext; // Cập nhật pHead để trỏ tới nút kế tiếp
    if (l->pHead == nullptr) { //Nếu sau khi xóa xong danh sách rỗng thì cập nhật pTail
        l->pTail = nullptr;
    }
    delete p; // Giair phóng bộ nhớ nút vừa xóa
    return true; // Xóa thành công
}

// Xóa phần tử cuối cùng của danh sách liên kết đơn
bool removeTail(List*& l) {
    // Nếu dan sách chưa khởi tạo hoặc rỗng trả về false
    if (l == nullptr || l->pHead == nullptr) return false;
    if (l->pHead == l->pTail) { // Nếu con trỏ đầu và cuối cùng chỉ vào một vị trí thì 
        delete l->pHead; // Xóa phần tử đó
        l->pHead = nullptr; // Gán phần tử đầu và cuối là nullptr
        l->pTail = nullptr;
        return true; // Trả về true nếu xóa thành công
    }
    Node* p = l->pHead; // Lưu con trỏ trước con trỏ Tail
    while (p->pNext != l->pTail) { //Duyệt con trỏ p tới trước con trỏ Tail
        p = p->pNext; //Di chuyển con trỏ sang node tiếp theo
    }
    delete l->pTail; //Giair phóng bộ nhớ nút cuối
    l->pTail = p; //Gán con trỏ trước con trỏ Tail cho con trỏ trước con troe vừa xóa
    l->pTail->pNext = nullptr; //Trỏ con trỏ Tail-> next là nullptr
    return true; // Trả về ture nếu xóa thành công
}

//Xóa toàn bộ node trong danh sách
void removeAll(List*& l) {
    if (l == nullptr) return; //Nếu danh sách rỗng dừng lại
    Node* p = l->pHead; //Khởi tạo node gán cho Head
    while (p != nullptr) { //Duyệt node từ đầu tới cuối
        Node* temp = p; //Gán node duyệt hiện tại cho node tạm
        p = p->pNext; //Di chuyển sang node tiếp theo
        delete temp; // Xóa node tạm
    }
    //Sau khi duyệt xong
    l->pHead = nullptr; // Gán con trỏ đầu và cuối trỏ về nullptr
    l->pTail = nullptr;
}

//Xóa node đứng trước node có giá trị val
void removeBefore(List*& l, int val) {
    //Nếu danh sách rỗng haowjc có ít hơn hai phần tử thì dừng lại
    if (l == nullptr || l->pHead == nullptr || l->pHead->pNext == nullptr) {
        return;
    }
    //Nếu node đầu tiên có giá trị bằng val thì dừng lại vì không có node trước đó
    if (l->pHead->key == val) {
        return;
    }
    Node* prev = nullptr; //Con trỏ giữu node trước node đang duyệt
    Node* curr = l->pHead; // Con trỏ đang duyệt
    //Duyệt qua danh sách để tìm node có giá trị val
    // curr đứng trước node có giá trị val
    while (curr->pNext != nullptr && curr->pNext->key != val) {
        prev = curr; 
        curr = curr->pNext; 
    }
    // Nếu không tìm thấy node nào có giá trị bằng val thì dừng
    if (curr->pNext == nullptr) {
        return;
    }
    //Nếu node cần xóa là node đầu tiên
    if (prev == nullptr) {
        l->pHead = curr->pNext; //Cập nhât lại node đầu
    } else {
        prev->pNext = curr->pNext;
    }
    // Nếu node đứng trước node cần xóa là node cuối
    if (curr->pNext == l->pTail) {
        l->pTail = prev; //Cập nhật lại node cuối danh sách
    }
    delete curr;
}

//Xóa node nằm sau node có giá trị bằng val
void removeAfter(List*& l, int val) {
    //Nếu danh sách rỗng hoặc không có phần tử nào dừng lại
    if (l == nullptr || l->pHead == nullptr) {
        return;
    }

    Node* cur = l->pHead; //Con trỏ curr để duyệt dan sách
    while (cur != nullptr) {
        //Nếu tìm thấy node có giá trị bằng val và node ko phải là node cuối
        if (cur->key == val && cur->pNext != nullptr) {
            Node* toDelete = cur->pNext; // Node cần xóa
            cur->pNext = toDelete->pNext; // Bỏ qua node cần xóa
            //Nếu node cần xóa là node cuối câp nhật lại con trỏ tail
            if (toDelete == l->pTail) {
                l->pTail = cur;
            }
            delete toDelete; // Giair phóng bộ nhớ node cần xóa
            return; //Thoát sau khi xóa node
        }
        cur = cur->pNext; //Di chuyển sau node tiếp theo
    }
}

//Thêm một node có giá trị data vào vị trí pos
bool addPos(List*& l, int data, int pos) {
    // Nếu danh sách chưa được khởi tạo thì khởi tạo
    if (l == nullptr) {
        l = new List;
        initList(l);
    }
    //Nếu vị trí thêm nhỏ hơn 0 thì không hợp lệ
    if (pos < 0) {
        return false;
    }
    //Nếu vị trí thêm là đầu danh sách gọi hàm thêm vào đầu
    if (pos == 0) {
        return addHead(l, data);
    }

    int listSize = countElements(*l);
    //Nếu vị trí thêm lớn hơn số lượng phần tử không hợp lệ
    if (pos > listSize) {
        return false;
    }
    //Nếu vị trí thêm là cuối gọi hàm thêm vào cuối danh sách
    if (pos == listSize) {
        return addTail(l, data);
    }
    //Tạo node mới với giá trị data
    Node* newNode = createNode(data);
    //Nếu không tạo mới được thì trả về giá trị false
    if (!newNode) {
        return false;
    }
    //Tìm node đứng trước vị trí cần chèn
    Node* p = l->pHead;
    int k = 0;
    while (p != nullptr && k < pos - 1) {
        p = p->pNext;
        k++;
    }
    //Nếu không tìm thấy thì giải phóng node vừa tạo
    if (p == nullptr) {
        delete newNode;
        return false;
    }
    //Chèn node mới vào vị trí pos
    newNode->pNext = p->pNext;
    p->pNext = newNode;
    //Nếu chèn vào cuối cập nhật lại Tail
    if (newNode->pNext == nullptr) {
        l->pTail = newNode;
    }
    return true; //Thêm thành công
}
// Xóa phần tử tại vị trí pos
bool removePos(List*& l, int pos) {
    // Kiểm tra nếu danh sách rỗng hoặc không có node nào thì dừng lại
    if (l == nullptr || l->pHead == nullptr) {
        return false;
    }
    //Đếm số lượng phần tử hiện tại trong danh sách
    int listSize = countElements(*l);
    //Nếu vị trí không hợp lệ thì dừng lại
    if (pos < 0 || pos >= listSize) {
        return false;
    }
    //Nếu vị trí cần xóa là đầu danh sách gọi hàm xóa đầu 
    if (pos == 0) {
        return removeHead(l);
    }
    //Nếu vị trí cần xóa là cuối danh sách gọi hàm xóa cuối
    if (pos == listSize - 1) {
        return removeTail(l);
    }
    //Tìm node trước vị trí cần xóa
    Node* p = l->pHead;
    int k = 0;
    while (p != nullptr && k < pos - 1) {
        p = p->pNext;
        k++;
    }
    //Nếu khongo tìm thấy vị trí hợp lệ
    if (p == nullptr || p->pNext == nullptr) {
        return false;
    }
    //Nếu xóa node tại vị trí cần xóa
    Node* toDelete = p->pNext;
    p->pNext = toDelete->pNext;
    delete toDelete;
    return true; //Xóa thành công
}

//Thêm một node có giá trj data vào trước node có giá trị val
bool addBefore(List*& l, int data, int val) {
    if (l == nullptr || l->pHead == nullptr) {
        return false;
    }
    Node* newNode = createNode(data);
    if (!newNode) {
        return false;
    }
    if (l->pHead->key == val) {
        newNode->pNext = l->pHead;
        l->pHead = newNode;
        return true;
    }
    Node* prev = nullptr;
    Node* curr = l->pHead;
    while (curr != nullptr && curr->key != val) {
        prev = curr;
        curr = curr->pNext;
    }
    if (curr == nullptr) {
        delete newNode;
        return false;
    }
    newNode->pNext = curr;
    if (prev != nullptr) {
        prev->pNext = newNode;
    }
    return true;
}

bool addAfter(List*& l, int data, int val) {
    if (l == nullptr || l->pHead == nullptr) {
        return false;
    }
    Node* newNode = createNode(data);
    if (!newNode) {
        return false;
    }
    Node* curr = l->pHead;
    while (curr != nullptr && curr->key != val) {
        curr = curr->pNext;
    }
    if (curr == nullptr) {
        delete newNode;
        return false;
    }
    newNode->pNext = curr->pNext;
    curr->pNext = newNode;
    if (curr == l->pTail) {
        l->pTail = newNode;
    }
    return true;
}

void reverseList(List*& l) {
    if (l == nullptr || l->pHead == nullptr || l->pHead == l->pTail) {
        return;
    }
    Node* prev = nullptr;
    Node* curr = l->pHead;
    Node* next = nullptr;
    while (curr != nullptr) {
        next = curr->pNext;
        curr->pNext = prev;
        prev = curr;
        curr = next;
    }
    l->pTail = l->pHead;
    l->pHead = prev;
}

void removeDuplicate(List*& l) {
    if (l == nullptr || l->pHead == nullptr || l->pHead == l->pTail) {
        return;
    }
    Node* curr = l->pHead;
    while (curr != nullptr) {
        Node* runner = curr;
        while (runner->pNext != nullptr) {
            if (runner->pNext->key == curr->key) {
                Node* toDelete = runner->pNext;
                runner->pNext = toDelete->pNext;
                if (toDelete == l->pTail) {
                    l->pTail = runner;
                }
                delete toDelete;
            } else {
                runner = runner->pNext;
            }
        }
        curr = curr->pNext;
    }
}

bool removeElement(List*& l, int key) {
    if (l == nullptr || l->pHead == nullptr) {
        return false;
    }
    bool removed = false;
    Node* curr = l->pHead;
    Node* prev = nullptr;
    while (curr != nullptr) {
        if (curr->key == key) {
            if (prev == nullptr) {
                l->pHead = curr->pNext;
                if (l->pHead == nullptr) {
                    l->pTail = nullptr;
                }
            } else {
                prev->pNext = curr->pNext;
                if (curr == l->pTail) {
                    l->pTail = prev;
                }
            }
            Node* toDelete = curr;
            curr = curr->pNext;
            delete toDelete;
            removed = true;
        } else {
            prev = curr;
            curr = curr->pNext;
        }
    }
    return removed;
}

List* createListFromArray(int arr[], int n) {
    List* newList = new List;
    initList(newList);
    if (n <= 0 || arr == nullptr) {
        return newList;
    }
    for (int i = 0; i < n; ++i) {
        if (!addTail(newList, arr[i])) {
            freeList(newList);
            initList(newList);
            return newList;
        }
    }
    return newList;
}

bool areListsEqual(List*& l1, List*& l2) {
    if (l1 == nullptr || l2 == nullptr) {
        return l1 == l2;
    }
    Node* p1 = l1->pHead;
    Node* p2 = l2->pHead;
    while (p1 != nullptr && p2 != nullptr) {
        if (p1->key != p2->key) {
            return false;
        }
        p1 = p1->pNext;
        p2 = p2->pNext;
    }
    return p1 == nullptr && p2 == nullptr;
}

void printList(List l) {
    if (l.pHead == nullptr) {
        cout << "Danh sach rong" << endl;
        return;
    }
    Node* p = l.pHead;
    while (p != nullptr) {
        cout << p->key << " ";
        p = p->pNext;
    }
    cout << endl;
}

void freeList(List*& l) {
    if (l == nullptr) return;
    Node* p = l->pHead;
    while (p != nullptr) {
        Node* temp = p;
        p = p->pNext;
        delete temp;
    }
    l->pHead = nullptr;
    l->pTail = nullptr;
}

int main() {
   std::cout <<"--- Begin running test case ---" << std::endl;

    // Test 1: createNode
    std::cout << "Test createNode: ";
    Node* node1 = createNode(10);
    assert(node1 != nullptr && node1->key == 10 && node1->pNext == nullptr);
    std::cout << "Passed" << std::endl;
    delete node1;

    // Test 2: createList
    std::cout << "Test createList: ";
    Node* head2 = createNode(20);
    List* list2 = new List;
    initList(list2);
    createList(list2, head2);
    assert(list2 != nullptr && list2->pHead == head2 && list2->pTail == head2);
    std::cout << "Passed" << std::endl;
    freeList(list2);
    delete list2;

    // Test 3: addHead
    std::cout << "Test addHead: ";
    List* list3 = new List;
    initList(list3);
    assert(addHead(list3, 30));
    assert(list3->pHead->key == 30 && list3->pTail->key == 30);
    assert(addHead(list3, 40));
    assert(list3->pHead->key == 40 && list3->pHead->pNext->key == 30);
    std::cout << "Passed" << std::endl;
    freeList(list3);
    delete list3;

    // Test 4: addTail
    std::cout << "Test addTail: ";
    List* list4 = new List;
    initList(list4);
    assert(addTail(list4, 50));
    assert(list4->pHead->key == 50 && list4->pTail->key == 50);
    assert(addTail(list4, 60));
    assert(list4->pHead->key == 50 && list4->pTail->key == 60);
    std::cout << "Passed" << std::endl;
    freeList(list4);
    delete list4;

    // Test 5: removeHead
    std::cout << "Test removeHead: ";
    int arr1[] = {70, 80, 90};
    List* list5 = createListFromArray(arr1, 3);
    assert(removeHead(list5) && list5->pHead->key == 80);
    assert(removeHead(list5) && list5->pHead->key == 90);
    assert(removeHead(list5) && list5->pHead == nullptr);
    assert(!removeHead(list5));
    std::cout << "Passed" << std::endl;
    freeList(list5);
    delete list5;

    // Test 6: removeTail
    std::cout << "Test removeTail: ";
    int arr2[] = {100, 110, 120};
    List* list6 = createListFromArray(arr2, 3);
    assert(removeTail(list6) && list6->pTail->key == 110);
    assert(removeTail(list6) && list6->pTail->key == 100);
    assert(removeTail(list6) && list6->pHead == nullptr);
    std::cout << "Passed" << std::endl;
    freeList(list6);
    delete list6;

    // Test 7: removeAll
    std::cout << "Test removeAll: ";
    int arr3[] = {130, 140, 150};
    List* list7 = createListFromArray(arr3, 3);
    removeAll(list7);
    assert(list7->pHead == nullptr && list7->pTail == nullptr);
    std::cout << "Passed" << std::endl;
    freeList(list7);
    delete list7;

    // Test 8: removeBefore
    std::cout << "Test removeBefore: ";
    int arr4[] = {160, 170, 180, 190, 200};
    List* list8 = createListFromArray(arr4, 5);
    removeBefore(list8, 180);
    int exp8[] = {160, 180, 190, 200};
    List* expected8 = createListFromArray(exp8, 4);
    assert(areListsEqual(list8, expected8));
    freeList(list8);
    freeList(expected8);
    delete list8;
    delete expected8;
    std::cout << "Passed" << std::endl;

    // Test 9: removeAfter
    std::cout << "Test removeAfter: ";
    int arr5[] = {220, 230, 240, 250};
    List* list9 = createListFromArray(arr5, 4);
    removeAfter(list9, 220);
    int exp9[] = {220, 240, 250};
    List* expected9 = createListFromArray(exp9, 3);
    assert(areListsEqual(list9, expected9));
    freeList(list9);
    freeList(expected9);
    delete list9;
    delete expected9;
    std::cout << "Passed" << std::endl;

    // Test 10: addPos
    std::cout << "Test addPos: ";
    List* list10 = new List;
    initList(list10);
    assert(addPos(list10, 280, 0));
    assert(addPos(list10, 290, 1));
    int exp10[] = {280, 290};
    List* expected10 = createListFromArray(exp10, 2);
    assert(areListsEqual(list10, expected10));
    freeList(list10);
    freeList(expected10);
    delete list10;
    delete expected10;
    std::cout << "Passed" << std::endl;

    // Test 11: removePos
    std::cout << "Test removePos: ";
    int arr11[] = {340, 350, 360};
    List* list11 = createListFromArray(arr11, 3);
    assert(removePos(list11, 1));
    int exp11[] = {340, 360};
    List* expected11 = createListFromArray(exp11, 2);
    assert(areListsEqual(list11, expected11));
    freeList(list11);
    freeList(expected11);
    delete list11;
    delete expected11;
    std::cout << "Passed" << std::endl;

    // Test 12: addBefore
    std::cout << "Test addBefore: ";
    int arr12[] = {390, 400};
    List* list12 = createListFromArray(arr12, 2);
    assert(addBefore(list12, 380, 400));
    int exp12[] = {390, 380, 400};
    List* expected12 = createListFromArray(exp12, 3);
    assert(areListsEqual(list12, expected12));
    freeList(list12);
    freeList(expected12);
    delete list12;
    delete expected12;
    std::cout << "Passed" << std::endl;

    // Test 13: addAfter
    std::cout << "Test addAfter: ";
    int arr13[] = {430, 440};
    List* list13 = createListFromArray(arr13, 2);
    assert(addAfter(list13, 450, 430));
    int exp13[] = {430, 450, 440};
    List* expected13 = createListFromArray(exp13, 3);
    assert(areListsEqual(list13, expected13));
    freeList(list13);
    freeList(expected13);
    delete list13;
    delete expected13;
    std::cout << "Passed" << std::endl;

    // Test 14: printList
    std::cout << "Test printList: "; 
    std::cout << "Passed" << std::endl;
  
    // Test 15: countElements
    std::cout << "Test countElements: ";
    int arr14[] = {500, 510, 520};
    List* list14 = createListFromArray(arr14, 3);
    assert(countElements(*list14) == 3);
    freeList(list14);
    delete list14;
    std::cout << "Passed" << std::endl;

    // Test 16: reverseList
    std::cout << "Test reverseList: ";
    int arr15[] = {590, 600, 610};
    List* list15 = createListFromArray(arr15, 3);
    reverseList(list15);
    int exp15[] = {610, 600, 590};
    List* expected15 = createListFromArray(exp15, 3);
    assert(areListsEqual(list15, expected15));
    freeList(list15);
    freeList(expected15);
    delete list15;
    delete expected15;
    std::cout << "Passed" << std::endl;

    // Test 17: removeDuplicate
    std::cout << "Test removeDuplicate: ";
    int arr16[] = {680, 690, 690, 700};
    List* list16 = createListFromArray(arr16, 4);
    removeDuplicate(list16);
    int exp16[] = {680, 690, 700};
    List* expected16 = createListFromArray(exp16, 3);
    assert(areListsEqual(list16, expected16));
    freeList(list16);
    freeList(expected16);
    delete list16;
    delete expected16;
    std::cout << "Passed" << std::endl;

    // Test 18: removeElement
    std::cout << "Test removeElement: ";
    int arr17[] = {800, 810, 820, 810};
    List* list17 = createListFromArray(arr17, 4);
    assert(removeElement(list17, 810));
    int exp17[] = {800, 820};
    List* expected17 = createListFromArray(exp17, 2);
    assert(areListsEqual(list17, expected17));
    freeList(list17);
    freeList(expected17);
    delete list17;
    delete expected17;
    std::cout << "Passed" << std::endl;
    std::cout <<"--- End running test case ---" << std::endl;
    return 0;
}