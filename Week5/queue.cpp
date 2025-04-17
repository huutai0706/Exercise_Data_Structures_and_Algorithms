#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Node {
    int key;
    Node* pNext;
};

struct Queue {
    Node* Head;
    Node* Tail;
};

Queue* initializeQueue() {
    Queue* q = new Queue;
    q->Head = nullptr;
    q->Tail = nullptr;
    return q;
}

// Thêm vào cuối
void enqueue(Queue& q, int key) {
    Node* newNode = nullptr;
    newNode->key = key;
    newNode->pNext = nullptr;
    if(q.Head == nullptr){
        q.Head = newNode;
        q.Tail = newNode;
        return;
    }
    q.Tail->pNext = newNode;
    q.Tail = newNode;
}

// Lấy ra đầu 
int dequeue(Queue& q) {
    Node* tmp = q.Head;
    if(q.Head == nullptr){
        delete tmp;
        return -1;
    }
    q.Head = q.Head->pNext;
    int val = tmp->key;
    delete tmp;
}

bool isEmpty(Queue q){
    return q.Head == nullptr;
}

// 
int size(Queue q){
    int count = 0;
    Node* tmp = q.Head;
    while(tmp != nullptr){
        tmp = tmp->pNext;
        count++;
    }
    return count;
}

//
void printQueue(Queue q, ofstream& out) {

}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    Queue* q = nullptr;

    input.close();
    output.close();
    return 0;
}
