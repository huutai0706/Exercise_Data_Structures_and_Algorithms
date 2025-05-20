#include <iostream>
#include <vector>
#include <climits> 
using namespace std;

struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
};

/*------------------------------------------------*/
// Tạo node mới 
NODE* createNode(int data){
    NODE* newNode = new NODE;
    newNode->key = data;
    newNode->p_left = nullptr;
    newNode->p_right = nullptr;
    return newNode;
}

/*------------------------------------------------*/
// Them NODE
void Insert(NODE*& pRoot, int x){
    if(!pRoot) {
        pRoot = createNode(x);
        return;
    }
    if(x < pRoot->key) Insert(pRoot->p_left, x);
    if(x >= pRoot->key) Insert(pRoot->p_right, x);
}

/*------------------------------------------------*/
// Tim kiem NODE
NODE* Search(NODE* pRoot, int x) {
    if(!pRoot || pRoot->key == x) return pRoot;
    if(x < pRoot->key) return Search(pRoot->p_left, x);
    if(x >= pRoot->key) return Search(pRoot->p_right, x);
}

/*------------------------------------------------*/
// Tim NODE nho nhat
NODE* findMin(NODE* pRoot){
    while(pRoot && pRoot->p_left){
        pRoot = pRoot->p_left;
    }
    return pRoot;
}

// Xoa NODE
void Remove(NODE*& pRoot, int x){
    if(!pRoot) return;
    if(x < pRoot->key){
        Remove(pRoot->p_left, x);
    } else if(x > pRoot->key){
        Remove(pRoot->p_right, x);
    } else{
        if(!pRoot->p_left){
            NODE* tmp = pRoot;
            pRoot = pRoot->p_right;
            delete tmp;
        } else if(!pRoot->p_right){
            NODE* tmp = pRoot;
            pRoot = pRoot->p_left;
            delete tmp;            
        } else{
            NODE* minRight = findMin(pRoot->p_right);
            pRoot->key = minRight->key;
            Remove(pRoot->p_right, minRight->key);
        }
    }
}

/*------------------------------------------------*/
// Tao cay tu mang
NODE* createTree(int a[], int n){
    NODE* pRoot = nullptr;
    for(int i = 0 ; i < n ; i++){
        Insert(pRoot, a[i]);
    }
    return pRoot;
}

/*------------------------------------------------*/
// Xoa toan bo cay
void removeTree(NODE*& pRoot){
    if(!pRoot) return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}

/*------------------------------------------------*/
// Tinh chieu cao cay
int Height(NODE* pRoot){
    if (!pRoot) return -1;
    return 1 + max(Height(pRoot->p_left), Height(pRoot->p_right));   
}

/*------------------------------------------------*/
//Dem so node co gia tri nho hon x
int countLess(NODE* pRoot, int x){
    if (!pRoot) return 0;
    if (pRoot->key < x)
        return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
    else
        return countLess(pRoot->p_left, x);
}

/*------------------------------------------------*/
//Dem so node co gia tri lon hon x
int countGreater(NODE* pRoot, int x){
    if (!pRoot) return 0;
    if (pRoot->key > x)
        return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
    else
        return countGreater(pRoot->p_right, x);
}

/*------------------------------------------------*/
// Kiem tra co phai cay nhi phan tiem kiem khong
bool isBSTUtil(NODE* pRoot, int minVal, int maxVal){
    if (!pRoot) return true;
    if (pRoot->key < minVal || pRoot->key >= maxVal) return false;
    return isBSTUtil(pRoot->p_left, minVal, pRoot->key) &&
           isBSTUtil(pRoot->p_right, pRoot->key, maxVal);
}

bool isBST(NODE* pRoot){
    return isBSTUtil(pRoot, INT_MIN, INT_MAX);
}

/*------------------------------------------------*/
// Kiem tra cay co phai moi node co cay con la 2 hay khong
bool isFullBST(NODE* pRoot){
    if (!pRoot) return true;
    if ((pRoot->p_left && !pRoot->p_right) || (!pRoot->p_left && pRoot->p_right))
        return false;
    return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);  
}

