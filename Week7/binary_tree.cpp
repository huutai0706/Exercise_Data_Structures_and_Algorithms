#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
};

// Tạo node mới 
NODE* createNode(int data){
    NODE* newNode = new NODE;
    newNode->key = data;
    newNode->p_left = nullptr;
    newNode->p_right = nullptr;
    return newNode;
}
/*------------------------------------------------*/
void in_order(vector<int>& tree, NODE* pRoot){
    if(pRoot == nullptr) return;
    in_order(tree, pRoot->p_left);
    tree.push_back(pRoot->key);
    in_order(tree, pRoot->p_right);
}

// Duyệt trung tự
vector<int> LNR(NODE* pRoot){
    vector<int> tree;
    in_order(tree, pRoot);
    return tree;
}
/*------------------------------------------------*/
void pre_order(vector<int>& tree, NODE* pRoot){
    if(pRoot == nullptr) return;
    tree.push_back(pRoot->key);
    pre_order(tree, pRoot->p_left);
    pre_order(tree, pRoot->p_right);
}

// Duyệt tiền tự
vector<int> NLR(NODE* pRoot){
    vector<int> tree;
    pre_order(tree, pRoot);
    return tree;
}
/*------------------------------------------------*/
void post_order(vector<int>& tree, NODE* pRoot){
    if(pRoot == nullptr) return;
    post_order(tree, pRoot->p_left);
    post_order(tree, pRoot->p_right);
    tree.push_back(pRoot->key);
}


// Duyệt hậu tự
vector<int> LRN(NODE* pRoot){
    vector<int> tree;
    post_order(tree, pRoot);
    return tree;
}
/*------------------------------------------------*/

// Duyệt theo tầng 
vector<vector<int>> LevelOrder(NODE* pRoot){
    vector<vector<int>> result;
    if (!pRoot) return result;

    queue<NODE*> q;
    q.push(pRoot);

    while (!q.empty()) {
        int size = q.size();
        vector<int> level;

        for (int i = 0; i < size; ++i) {
            NODE* current = q.front(); q.pop();
            level.push_back(current->key);
            if (current->p_left) q.push(current->p_left);
            if (current->p_right) q.push(current->p_right);
        }

        result.push_back(level);
    }

    return result;
}
/*------------------------------------------------*/
// Đếm số Node 
int countNode(NODE* pRoot){
    if(!pRoot) return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}
/*------------------------------------------------*/
// Tổng gía trị các node 
int sumNode(NODE* pRoot){
    if(!pRoot) return 0;
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}
/*------------------------------------------------*/
int findHeight(NODE* pRoot){
    if(!pRoot) return -1;
    return 1 + max(findHeight(pRoot->p_left), findHeight(pRoot->p_right));
}

// Chiều cao node cho trước trả về -1 nếu không tìm thấy 
int heightNode(NODE* pRoot, int value){
    if(!pRoot) return -1;
    if (pRoot->key == value) return findHeight(pRoot);
    int left = heightNode(pRoot->p_left, value);
    if(left != -1) return left;
    return heightNode(pRoot->p_right, value);
}
/*------------------------------------------------*/
int LevelTree(NODE* pRoot, NODE* p, int level){
    if (!pRoot) return -1;
    if (pRoot == p) return level;
    int left = LevelTree(pRoot->p_left, p, level + 1);
    if (left != -1) return left;
    return LevelTree(pRoot->p_right, p, level + 1);
}

// Tầng của node cho trước 
int Level(NODE* pRoot, NODE* p){
    return LevelTree(pRoot, p, 0);
}
/*------------------------------------------------*/
// Đếm số node lá 
int countLeaf(NODE * pRoot){
    if(!pRoot) return 0;
    if(!pRoot->p_left && !pRoot->p_right) return 1;
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}
/*------------------------------------------------*/
