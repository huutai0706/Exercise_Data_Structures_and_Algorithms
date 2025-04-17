#include <iostream>
#include <vector>
using namespace std;

//Ham nhap du lieu cho mang
void scanf_arr(vector<int>& a){
    int x, n;
    cin >> n;
    for(int i = 0 ; i < n; i++){
        cin >> x;
        a.push_back(x);
    }
    return;
}
//Ham in ra gia tri cua mang
void prinf_arr(vector<int> a){
    for(int i = 0 ; i < a.size(); i++){
        cout << a[i] <<" ";
    }
    return;
}
//Ham de quy tim kiem tuyen tinh
int linear_search(vector<int> a, int n, int k){
    //Neu n <= 0 thi dung lai tra ve gia tri -1
    if(n <= 0) {
        return -1;
    }
    //Neu a[n-1] == k thi tra ve gia tri n-1 vi tri n-1
    if(a[n-1] == k){
        return n-1;
    } 
    //Goi de quy ham tim kiem tuyen tinh
    return linear_search(a, n-1, k);
}

int main(){
    vector<int> a;
    scanf_arr(a);
    int k; cin >> k;
    // gan gia tri tra ve ham tim kiem cho index
    int index = linear_search(a, a.size(), k);
    //neu index khac -1 thi in ra vi tri tim thay neu khong in ra -1
    if(index != -1){
        cout << index << endl;
    } else{
        cout << -1 << endl;
    }
    return 0;
}