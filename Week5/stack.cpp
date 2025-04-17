#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct Stack {
    NODE* top;
};

Stack* initializeStack() {
    Stack* s = new Stack;
    s->top = nullptr;
    return s;
}

void push(Stack*& s, int key) {
    NODE* newNode = new NODE;
    newNode->key = key;
    newNode->p_next = s->top;
    s->top = newNode;
}

int pop(Stack*& s) {
    if (s->top == nullptr) return -1;
    NODE* temp = s->top;
    int val = temp->key;
    s->top = s->top->p_next;
    delete temp;
    return val;
}

bool isEmpty(Stack* s) {
    return s->top == nullptr;
}

int size(Stack s){
    int count = 0;
    NODE* tmp = s.top;
    while(tmp != nullptr){
        count++;
        tmp = tmp->p_next;
    }
    return count;
}

void printStack(Stack* s, ofstream& out) {
    if (isEmpty(s)) {
        out << "EMPTY";
        return;
    }
    NODE* tmp = s->top;
    while(tmp != nullptr){
        out << tmp->key <<" ";
        tmp = tmp->p_next;
    }
}

void freeStack(Stack* s) {
    while (!isEmpty(s)){
        pop(s);
    }       
    delete s;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    vector<string> ss;
    string temp;
    while (in >> temp) {
        ss.push_back(temp);
    }
    Stack* s = nullptr;
    for (int i = 0; i < ss.size(); ++i) {
        if (ss[i] == "init") {
            s = initializeStack();
            printStack(s, out);
        } else if (ss[i] == "push") {
            if (s != nullptr && i + 1 < ss.size()) {
                push(s, stoi(ss[++i]));
                printStack(s, out);
            }
        } else if (ss[i] == "pop") {
            if (s != nullptr) {
                pop(s);
                printStack(s, out);
            }
        }
        out <<"\n";
    }
    freeStack(s);
    in.close();
    out.close();
    return 0;
}

