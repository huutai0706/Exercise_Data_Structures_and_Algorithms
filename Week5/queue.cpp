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

//
Queue* initializeQueue() {
    Queue* q = new Queue;
    q->Head = nullptr;
    q->Tail = nullptr;
    return q;
}

// Thêm vào cuối
void enqueue(Queue& q, int key) {
    Node* newNode = new Node;
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
    return val;
}

//
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
    if (isEmpty(q)) {
        out << "EMPTY";
        return;
    }
    Node* tmp = q.Head;
    while(tmp != nullptr){
        out << tmp->key <<" ";
        tmp = tmp->pNext;
    }
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    vector<string> ss;
    string temp;
    while (input >> temp) {
        ss.push_back(temp);
    }
    Queue* q = nullptr;
    for (int i = 0; i < ss.size(); ++i) {
        if (ss[i] == "init") {
            q = initializeQueue();
            printQueue(*q, output);
        } else if (ss[i] == "enqueue") {
            if (q != nullptr && i + 1 < ss.size()) {
                enqueue(*q, stoi(ss[++i]));
                printQueue(*q, output);
            }
        } else if (ss[i] == "dequeue") {
            if (q != nullptr) {
                dequeue(*q);
                printQueue(*q, output);
            }
        }
        output <<"\n";
    }
    input.close();
    output.close();
    return 0;
}
